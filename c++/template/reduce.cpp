#include <algorithm>
#include <iostream>
#include <vector>

template <class T>
class has_iterator {
private:
    template <class U>
    static constexpr bool check(typename U::iterator*)
        { return true; }

    template <class U>
    static constexpr bool check(...)
        { return false; }

public:
    static const bool value = check<T>(nullptr);
};

template <class InputIterator, class Func>
typename std::iterator_traits<InputIterator>::value_type reduce(Func f,
                                                                InputIterator first, InputIterator last,
                                                                typename std::iterator_traits<InputIterator>::value_type init_value) {
    return std::accumulate(first, last, init_value, f);}
template <class InputIterator, class Func>
typename std::iterator_traits<InputIterator>::value_type reduce(Func f,
                                                                InputIterator first, InputIterator last) {
    return std::accumulate(first, last, 0, f);}

template <class T>
T add(T& a, T& b){
    return a + b;
}

template <class T>
T mult(T& a, T& b){
    return a * b;
}

int main(){
    std::vector<int> v(10);
    std::iota(begin(v), end(v), 1);
    std::cout << reduce(add<int>, begin(v), end(v)) << std::endl;
    std::cout << reduce(mult<int>, begin(v), end(v), 1) << std::endl;

    return 0;
}
