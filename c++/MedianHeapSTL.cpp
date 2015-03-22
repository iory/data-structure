#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

template <class T>
class MedianHeap{
    typedef std::priority_queue<T, std::vector<T>, std::greater<T>> MinHeap;
    typedef std::priority_queue<T> MaxHeap;
private:
    MaxHeap *max_heap;
    MinHeap *min_heap;
public:
    MedianHeap(){
        max_heap = new MaxHeap();
        min_heap = new MinHeap();
    }

    ~MedianHeap(){
        delete max_heap;
        delete min_heap;
    }

    void push(T data){
        if(max_heap->size()==0){
            max_heap->push(data);
            return;
        }

        T maxHeap_top_val = max_heap->top();

        if(data < maxHeap_top_val){
            max_heap->pop();
            max_heap->push(data);
            std::swap(maxHeap_top_val, data);
        }

        if(min_heap->size()==0){
            min_heap->push(data);
            return;
        }

        T minHeap_top_val = min_heap->top();

        if(data > minHeap_top_val){
            min_heap->pop();
            min_heap->push(data);
            std::swap(data, minHeap_top_val);
        }

        if(max_heap->size() > min_heap->size())
            min_heap->push(data);
        else
            max_heap->push(data);
    }

    T top(){
        if((max_heap->size() + min_heap->size()) & 1)
            return max_heap->top();
        else
            return (max_heap->top() + min_heap->top())/2;
    }
};

int main(){
    typedef long long ll;
    MedianHeap<ll> mheap;

    ll input_value;
    while(std::cin >> input_value){
        mheap.push(input_value);
        std::cout << mheap.top() << std::endl;
    }
}
