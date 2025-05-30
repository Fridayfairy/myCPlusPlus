#include <cstring>
#include <iostream>

using namespace std;
class Person {
public:
  typedef enum { BOY = 0, GIRL } SexType;
  Person(char *n, int a, SexType s) {
    name = new char[strlen(n) + 1];
    strcpy(name, n);
    age = a;
    sex = s;
  }
  int get_age() const { return this->age; }
  /*
  这里使用了 this->age 来访问当前对象的 age 成员变量。
  this->age 和直接写 age 在这种情况下效果是相同的
  因为在成员函数中访问成员变量时，编译器会隐式地使用 this 指针。
  也就是说，return age; 的实际含义就是 return this->age;。
  显式地使用 this-> 有时可以提高代码的可读性。
  */
  Person &add_age(int a) {
    age += a; // 这里使用了 this->age 来访问当前对象的 age 成员变量。
    return *this;
  }
  ~Person() { delete[] name; }

private:
  char *name;
  int age;
  SexType sex;
};

int main() {
  Person p("zhangsan", 20, Person::BOY);
  cout << p.get_age() << endl;
  p.add_age(10).add_age(20).add_age(30);
  cout << p.get_age() << endl;
  return 0;
}
