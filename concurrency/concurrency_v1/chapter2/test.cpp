#include <iostream>

using namespace std;

/*
这是一个简单的函数对象（Functor）示例。通过定义 operator()，
使得 background_task 的对象可以像函数一样被调用。
std::thread 的构造函数可以接受任何可调用对象（
函数、函数指针、函数对象、Lambda 表达式）。
*/
class background_task {
public:
    void operator()(int i) const {
        cout << "ok: " << i << endl;
    }
};
int main() {
    background_task task;
    task(1);
}