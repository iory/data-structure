#include <queue>
#include <deque>
#include <iostream>
#include <iterator>

using namespace std;

template<typename T, typename Container=std::deque<T> >
class iterable_queue : public std::queue<T,Container>
{
public:
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;

    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }
    const_iterator begin() const { return this->c.begin(); }
    const_iterator end() const { return this->c.end(); }

    void print(){
        cout << "queue -> [";
        for(auto it = this->c.begin(),endit = this->c.end();it != endit;++it){
            cout << *it << ((it+1) == endit ? "]":", ");
        }
        cout << endl;
    }

    void clear(){
        while(!this->empty()){
            cout << "remove " << this->front() << endl;;
            this->pop();
        }
    }
};

int main(){
    iterable_queue<int> que;
    que.push(37);
    que.push(99);
    que.push(11);

    que.print();
    que.clear();

    return 0;
}
