#include <iostream>
using namespace std;
// C++ 中，如果在命名空间（包括全局命名空间）中声
// 明了一个非 const 的变量并且没
// 有使用 static 关键字，它默认具有外部链接（external linkage）
int count = 0; // 全局(::)的count

class A {
public:
  static int count; // 类A的count (A::count)
};
// 静态变量必须在此处定义
int A::count; // 定义并默认初始化为0 (对于内置类型)
int main() {
  ::count = 1;  // 设置全局的count为1
  cout << "before A::count:" << A::count << endl;
  A::count = 5; // 设置类A的count为2
  cout << A::count << endl;
  cout << ::count << endl;
  cout << "?? count:" << count << endl;
  int count=3; // 局部count
  count=4;     // 设置局部的count为4
  cout << "::count:" << ::count << endl;
  cout << "count:" << count << endl;
  return 0;
}
