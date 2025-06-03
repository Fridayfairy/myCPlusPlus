//
// Created by light on 19-12-28.
//

#include <iostream>

using namespace std;

template <int n> struct factorial {
  static_assert(n >= 0, "Arg must be non-negative");
  static const int value = n * factorial<n - 1>::value;
};
/*
template <int n>: 这声明了一个类模板。<int n> 是模板参数列表。这意味着你可以用一个整数值来实例化这个模板，例如 factorial<5>。在实例化时，编译器会用 5 替换模板定义中的所有 n。这里的 n 是一个非类型模板参数 (Non-type Template Parameter)，它是一个编译期常量。
struct factorial: 定义了一个结构体模板，名称是 factorial。
static_assert(n >= 0, "Arg must be non-negative");:
static_assert 是 C++11 引入的一个关键字，用于执行编译期断言。
它后面跟着一个布尔表达式 (n >= 0) 和一个字符串字面量 ("Arg must be non-negative")。
这个断言在编译时进行检查。如果 n >= 0 这个条件在模板实例化时为假（例如你尝试实例化 factorial<-5>），编译器会立即产生一个错误，并显示后面的字符串作为错误信息。这比运行时错误更早、更清晰。
static const int value = n * factorial<n - 1>::value;:
static const int value: 这声明了一个静态的、常量成员变量 value。static 意味着这个变量属于类本身，而不是类的某个具体对象；const 意味着它的值在编译时确定且不能修改。将其声明为 static const 并直接初始化（在类内部）是 C++11 以后允许的，尤其适合用于存储编译期常量。
= n * factorial<n - 1>::value;: 这是 value 的初始化表达式。它将当前的 n 乘以 factorial<n - 1>::value。注意这里的关键点：factorial<n - 1> 是对 factorial 模板的另一次实例化，其参数是 n - 1。这构成了模板的递归实例化。编译器为了计算 factorial<n>::value，必须先实例化并计算 factorial<n-1>::value，依此类推。::value 是访问 factorial<n - 1> 这个模板实例化类内部的静态成员 value。
*/
template <> struct factorial<0> { static const int value = 1; };

int main() {

  printf("%d\n", factorial<10>::value);
  return 0;
}
/*
template <>: 这表示这是一个模板特化，而不是一个通用的模板定义。后面的类声明为模板的某个特定参数提供了专门的定义。
struct factorial<0>: 这是对 factorial 模板在模板参数为 0 时的全特化版本。当编译器需要实例化 factorial<0> 时，它会优先选择这个特化版本，而不是上面那个通用的模板定义。
static const int value = 1;: 在这个特化版本中，value 被直接定义为 1。这是阶乘递归的终止条件（0! = 1）。当递归实例化链到达 factorial<0> 时，它会使用这个特化版本，找到 value 的确定值 1，从而允许上一层的实例化（factorial<1>）完成计算，然后是 factorial<2>，直到最初请求的 factorial<n>。
总结语法要点：
template <...>: 定义模板。
<类型 参数名> 或 <非类型 参数名>: 模板参数，可以是类型（如 typename T）或编译期常量（如 int n）。
template <>: 声明一个模板特化。
模板名<特化参数>: 指定特化是针对哪个具体参数值的。
static const 类型 成员名 = 表达式;: 定义一个编译期常量的静态成员变量。
模板名<参数>::静态成员名: 访问模板实例化类中的静态成员。
static_assert(条件, "消息");: 编译期断言。
这段代码通过这种语法结构，巧妙地将数学上的递归定义 n! = n * (n-1)! 和 0! = 1 映射到了 C++ 的模板实例化和特化上，实现了编译期计算。
*/