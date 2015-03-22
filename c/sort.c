#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void merge_sort(int v[],int n);
void _merge_sort(int v[],int left,int right);

void swap(int *a,int *b){
  if(*a == *b) return;
  *a ^= *b;
  *b ^= *a;
  *a ^= *b;
}

void* ecMalloc(unsigned int size){
  void* ptr = malloc(size);
  if(ptr==NULL){
    printf("Memory Error\n");
    exit(-1);
  }
  return ptr;
}

void insertion_sort(int v[],int n){
  int i,j,tmp;
  for(i=1;i<n;++i){
    tmp = v[i];
    if(v[i-1] > tmp){
      j = i;
      do{
	v[j] = v[j-1];
	--j;
      } while(j > 0 && v[j-1] > tmp);
      v[j] = tmp;
    }
  }
}

void bubble_sort(int v[],int n){
  int i,j,tmp;
  for(i=0;i<n;++i){
    for(j=i+1;j<n;++j){
      if(v[i] > v[j]){
	tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
      }
    }
  }
}


// Heap
typedef struct {
  int *array;
  int count;
  int capacity;
  int heap_type;
} Heap;

Heap *CreateHeap(int capacity,int heap_type){
  Heap *h = (Heap*)ecMalloc(sizeof(Heap));
  h->heap_type = heap_type;
  h->count = 0;
  h->capacity = capacity;
  h->array = (int*)ecMalloc(sizeof(int)*h->capacity);
  return h;
}

int Parent(Heap *h,int i){
  if(i<=0 || i>=h->count){
    return -1;
  }
  return (i-1)/2;
}

int LeftChild(Heap *h,int i){
  int left = 2 * i + 1;
  if(left >= h->count) return -1;
  return left;
}
int RightChild(Heap *h,int i){
  int right = 2 * i + 2;
  if(right >= h->count) return -1;
  return right;
}

int GetMaximum(Heap *h){
  if(h->count==0){
    return -1;
  }
  return h->array[0];
}

void PercolateDown(Heap *h,int i){
  int l,r,max,temp;
  l =LeftChild(h,i);
  r =RightChild(h,i);
  if(r==-1 && l==-1) return;
  if(l != -1 && h->array[l] > h->array[i])
    max = l;
  else
    max = i;
  if(r!=-1 && h->array[r] > h->array[max])
    max = r;
  if(max != i){
    swap(&h->array[i],&h->array[max]);
    /* temp = h->array[i]; */
    /* h->array[i] = h->array[max]; */
    /* h->array[i] = temp; */
    PercolateDown(h,max);
  }
}

int DeleteMax(Heap *h){
  int data;
  if(h->count == 0){
    return -1;
  }
  data = h->array[0];
  h->count--;
  PercolateDown(h,0);
  return data;
}

void ResizeHeap(Heap *h){
  int i;
  int *array_old = h->array;
  h->array = (int*)ecMalloc(sizeof(int) * h->capacity * 2);
  for(i = 0;i<h->capacity;++i){
    h->array[i] = array_old[i];
  }
  h->capacity *= 2;
  free(array_old);
  return;
}

void Insert(Heap *h,int data){
  int i;
  if(h->count==h->capacity)
    ResizeHeap(h);
  h->count++;
  i = h->count-1;
  while(i>0 && data > h->array[(i-1)/2]){
    h->array[i] = h->array[(i-1)/2];
    i = (i-1)/2;
  }
  h->array[i] = data;
}

void DestroyHeap(Heap *h){
  if(h==NULL)
    return;
  free(h->array);
  free(h);
  h = NULL;
}

void BuildHeap(Heap *h,int A[],int n){
  int i;
  if(h==NULL)
    return;
  while(n > h->capacity)
    ResizeHeap(h);
  for(i=0;i<n;++i)
    h->array[i] = A[i];

  h->count = n;
  for(i=(n-1)/2;i>=0;--i){
    PercolateDown(h,i);
  }
}

void HeapSort(int A[],int n){
  Heap *h = CreateHeap(n,1);
  int old_size,i;
  BuildHeap(h,A,n);
  old_size = h->count;
  for(i=n-1;i>0;--i){
    swap(&h->array[0],&h->array[h->count-1]);
    h->count--;
    PercolateDown(h,0);
  }
  for(i=0;i<n;++i){
    A[i] = h->array[i];
  }
  h->count = old_size;
}


// ↑ Heap


void random_shuffle(int v[],int n){
  int i,tmp;
  int a,b;
  for(i=0;i<100;++i){
    a = rand() % n;
    b = rand() % n;
    tmp = v[a];
    v[a] = v[b];
    v[b] = tmp;
  }
}

void print(int v[],int n){
  int i;
  for(i=0;i<n;++i){
    printf("%d ",v[i]);
  }
  printf("\n");
}



void merge_sort(int v[],int n){
  _merge_sort(v,0,n);
}

void _merge_sort(int v[],int left,int right){
  int i,j,k;
  int N = right - left;
  int mid;
  int *W;
  if(N <= 1)return;

  mid = N / 2 + left;
  _merge_sort(v,left,mid);
  _merge_sort(v,mid,right);

  W = (int*)ecMalloc(sizeof(int) * N);
  i = left;
  j = mid;
  k = 0;
  while(i != mid && j != right){
    if(v[i] > v[j]){
      W[k++] = v[j++];
    } else {
      W[k++] = v[i++];
    }
  }
  while(i!=mid) W[k++] = v[i++];
  while(j!=right) W[k++] = v[j++];

  k = 0;
  for(int i=left;i<right;++i){
    v[i] = W[k++];
  }
}


void _quick_sort(int v[],int left,int right){
  int i,j;
  int N = right - left;
  if(N < 1)return;

  int pivot = v[left + N / 2];
  i = left ;
  j = right - 1;
  while(1){
    while(v[i] < pivot)
      i++;
    while(pivot < v[j])
      j--;
    if(i >= j)break;
    swap(&v[i],&v[j]);
    i++;
    j--;
  }
  if(left < i - 1)
    _quick_sort(v,left,i);
  if(j + 1 < right)
    _quick_sort(v,j,right);
}

void quick_sort(int v[],int n){
  _quick_sort(v,0,n);
}

const char *sort_names[] = {"insertion_sort","bublle_sort","heap_sort","merge_sort","quick_sort"};

// 関数ポインタ
// 今回作成したsortを実行しやすいように関数ポインタの配列にメモす
void (*pf[])(int v[],int n) = {
  insertion_sort,
  bubble_sort,
  HeapSort,
  merge_sort,
  quick_sort,
};

const int SIZE = 30;
int v[SIZE];

// 関数ポインタを使用し,randomになった配列のsortを行う.
int main(void){
  int i;

  srand((unsigned)time(NULL));
  for(i=0;i<SIZE;++i)v[i] = i;

  for(i=0;i<5;++i){
    printf("%s\n",sort_names[i]);
    random_shuffle(v,SIZE);
    pf[i](v,SIZE);
    print(v,SIZE);
  }

  return 0;
}
