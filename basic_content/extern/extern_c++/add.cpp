#include <iostream>
using namespace std;
//C++调用C函数的例子: 引用C的头文件时，需要加`extern "C"`
extern "C" {
#include "add.h"
}
int main() {
  std::cout << add(2, 3) << std::endl;
  return 0;
}
