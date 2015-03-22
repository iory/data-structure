#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
#include <random>

using namespace std;

// iterator first-last間の要素を出力する
template <class Iterator>
void print(Iterator first,Iterator last){
  while(first != last){
    cout << *first++ << " ";
  }cout << endl;
}

template <class Iterator>
void merge_sort(Iterator first,Iterator last ){
  int N = last - first;
  if(N <=1 )return;
  Iterator mid = N / 2 + first;

  merge_sort(first,mid);
  merge_sort(mid,last);

  Iterator i = first;
  Iterator j = mid;
  vector<typename iterator_traits<Iterator>::value_type > tmp(N);
  Iterator it = tmp.begin();
  while(i != mid && j != last){
    if( *i > *j){
      *it++ = *j++;
    } else {
      *it++ = *i++;
    }
  }
  while(i != mid)*it++ = *i++;
  while(j != last)*it++ = *j++;
  Iterator p = tmp.begin();
  while(first != last){
    *first++ = *p++;
  }
}

template <class T>
void bubble_sort(vector<T> &v){
  int N = v.size();
  for(int i=0;i<N;++i){
    for(int j=i+1;j<N;++j){
      if(v[i] > v[j])swap(v[i],v[j]);
    }
  }
}

template <class T>
void insertion_sort(vector<T> &v){
  int N = v.size();
  for(int i=1;i<N;++i){
    int tmp = v[i];
    if(v[i-1] > tmp){
      int j = i;
      do{
	v[j] = v[j-1];
	--j;
      } while (j > 0 && v[j-1] > tmp);
      v[j] = tmp;
    }
  }
}

// Heap の実装
// heaptype == 0 : maxHeap
// heaptype == 1 : minHeap
template<class T>
class Heap{
private:
  int heapCapacitySize;
  int heapType;
  int cnt;
  vector<T> array;

  int leftChild(int i){
    int left = 2*i + 1;
    if(left>=cnt)
      return -1;
    return left;
  }

  int rightChild(int i){
    int right = (i+1)<<1;
    if(right>=cnt)
      return -1;
    return right;
  }

  void Heapify(int i){
    if(heapType==0)
      maxHeapify(i);
    else
      minHeapify(i);
  }

  void maxHeapify(int i){
    int max_point;
    int l = leftChild(i);
    int r = rightChild(i);
    if(l!=-1 && array[l] > array[i]){
      max_point = l;
    } else {
      max_point = i;
    }
    if(r!=-1 && array[r] > array[max_point]){
      max_point = r;
    }
    if(max_point != i){
      swap(array[i],array[max_point]);
      maxHeapify(max_point);
    }
  }

  void minHeapify(int i){
    int min_point;
    int l = leftChild(i);
    int r = rightChild(i);
    if(l!=-1 && array[l] < array[i])
      min_point = l;
    else
      min_point = i;
    if(r!=-1 && array[r] < array[min_point])
      min_point = r;

    if(min_point != i){
      swap(array[i],array[min_point]);
      minHeapify(min_point);
    }
  }

public:
  Heap():heapCapacitySize(100),heapType(0),cnt(0){}
  Heap(int _heapType):heapCapacitySize(100),heapType(_heapType),cnt(0){
    array.resize(100);
  }

  void Insert(T data){
    if(cnt == heapCapacitySize){
      heapCapacitySize <<= 1;
      array.resize(heapCapacitySize);
    }
    int i = cnt;
    cnt++;
    if(heapType==0){
      while(i>0 && data > array[(i-1)/2]){
	array[i] = array[(i-1)/2];
	i = (i-1)/2;
      }
      array[i] = data;
    } else {
      while(i > 0 && data < array[(i-1)/2]){
	array[i] = array[(i-1)/2];
	i = (i-1)/2;
      }
      array[i] = data;
    }

  }

  T Delete(){
    T data;
    if(cnt==0){
      return -1;
    }
    data = array[0];
    array[0] = array[cnt-1];
    cnt--;
    if(heapType==0)
      maxHeapify(0);
    else
      minHeapify(0);
    return data;
  }

  T pop(){
    if(heapCapacitySize>0){
      return array[0];
    } else {
     return -1;
    }
  }

  int size(){
    return cnt;
  }
};

template <class T>
void heap_sort(vector<T>& v){
  int N = v.size();
  Heap<T> *heap = new Heap<T>(0);
  for(int i=0;i<N;++i){
    heap->Insert(v[i]);
  }
  for(int i=N-1;i>=0;--i){
    v[i] = heap->Delete();
  }
  delete heap;
}

// STLを使用して,コンパクトに実装したmerge_sort
template <typename Iterator, typename Order>
void merge_sort(Iterator first,Iterator last,Order order){
  if(last - first > 1){
    Iterator mid = first + (last - first) / 2;
    merge_sort(first,mid,order);
    merge_sort(mid,last,order);
    std::inplace_merge(first,mid,last,order);
  }
}
template <typename Iterator>
void mergesort(Iterator first,Iterator last){
  merge_sort(first,last,std::less<typename std::iterator_traits<Iterator>::value_type>());
}

// randomized quicksort
// 乱択クイックソート
// クイックソートの最悪ケースを回避するべく,ランダムにpivotを選択し最悪計算量O(NlogN)を達成する
// random選択にはc++0xのrandomを使用
std::mt19937 engine;
template <typename Iterator>
void quick_sort(Iterator first,Iterator last){
  int N = last - first;
  if(N < 1)return;
  std::uniform_int_distribution<int> dist(0,N-1);

  int p = dist(engine);
  typename std::iterator_traits<Iterator>::value_type pivot = *(first + p);
  vector<typename std::iterator_traits<Iterator>::value_type> left,right;

  Iterator it = first;
  for(int i=0;i<N;++i,++it){
    if(i==p)continue;
    if(*it <= pivot){
      left.push_back(*it);
    } else {
      right.push_back(*it);
    }
  }

  quick_sort(left.begin(),left.end());
  quick_sort(right.begin(),right.end());

  Iterator lit = left.begin();
  Iterator rit = right.begin();
  while(lit != left.end()) *first++ = *lit++;
  *first++ = pivot;
  while(rit != right.end()) *first++ = *rit++;
}

// ランダムに配列を並び替えソートするプログラムである.
int main(){
  vector<int> v;
  for(int i=0;i<30;++i)v.push_back(i);

  cout << "mergesort:" << endl;
  random_shuffle(v.begin(),v.end());
  mergesort(v.begin(),v.end());
  print(v.begin(),v.end());

  cout << "merge_sort:" << endl;
  random_shuffle(v.begin(),v.end());
  merge_sort(v.begin(),v.end());
  print(v.begin(),v.end());

  cout << "insertion_sort:" << endl;
  random_shuffle(v.begin(),v.end());
  insertion_sort(v);
  print(v.begin(),v.end());

  cout << "bubble_sort:" << endl;
  random_shuffle(v.begin(),v.end());
  bubble_sort(v);
  print(v.begin(),v.end());


  cout << "heap_sort:" << endl;
  random_shuffle(v.begin(),v.end());
  heap_sort(v);
  print(v.begin(),v.end());

  cout << "quick_sort:" << endl;
  random_shuffle(v.begin(),v.end());
  quick_sort(v.begin(),v.end());
  print(v.begin(),v.end());

}
