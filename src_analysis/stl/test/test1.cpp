#include <iostream>
#include <cassert>
using namespace std;

class Empty{
public:
    void print() {
        std::cout<<"I am Empty class"<<std::endl;
    }
};

template<typename T>
bool isSame( T const& a, T const& b) {
    return &a == &b;
}

int main() {
    Empty a, b;
    assert( !isSame(a, b));

    Empty *p = new Empty;
    Empty *q = new Empty;
    assert( !isSame(p, q));

    delete p;
    delete q;

    return 0;
}