#include <iostream> // 包含标准输入输出流库，用于 cout

using namespace std; // 使用标准命名空间

struct stuff { // 定义一个名为 stuff 的结构体
  unsigned int field1 : 30; // 定义一个无符号整型位域，占用 30 位
  unsigned int : 2;       // 定义一个无符号整型匿名位域，占用 2 位（通常用于填充或强制对齐）
  unsigned int field2 : 4;       // 定义一个无符号整型位域，占用 4 位
  unsigned int : 0;       // 定义一个无符号整型零宽度位域（强制下一个位域 field3 对齐到下一个分配单元的边界）
  unsigned int field3 : 3;       // 定义一个无符号整型位域，占用 3 位
};

int main() {
  // 初始化一个 struct stuff 类型的对象 s
  // {1, 3, 5} 按照成员声明顺序依次初始化 field1, field2, field3
  // 注意：匿名位域和零宽度位域在初始化列表中不能直接赋值
  struct stuff s = {1, 3, 5};

  // 打印各个位域的值
  // 访问位域的方式和普通成员一样：对象名.位域名
  cout << s.field1 << endl; // 打印 field1 的值
  cout << s.field2 << endl; // 打印 field2 的值
  cout << s.field3 << endl; // 打印 field3 的值

  // 打印 struct stuff 对象的大小
  cout << sizeof(s) << endl; // 12

  return 0; // 程序正常退出
}