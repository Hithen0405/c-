#include<iostream>
using namespace std;
class Counter {
    int v;
public:
    Counter(int v = 0) : v(v) {}
    Counter& operator++() {
        ++v;
        return *this;
    }
    Counter operator++(int) {
        Counter t=*this;
        ++v;
        return t;
    }
    friend ostream &operator<<(ostream &os, const Counter &c) {
        os << c.v;
        return os;
    }
};