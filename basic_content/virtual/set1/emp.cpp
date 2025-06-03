#include <iostream>
using namespace std;

// 基类 Employee
class Employee {
public:
  // 虚函数：允许派生类重写，实现运行时多态
  virtual void raiseSalary() { cout << 0 << endl; }

  virtual void promote() { /* common promote code */
  }
};

// 派生类 Manager，继承自 Employee
class Manager : public Employee {
public: // 注意：尽管这里省略了 public，但成员函数默认是 private 的。为了外部访问，应该加上 public。
        // 假设这里是 public 的，为了代码可执行性。实际项目中应显式写出 public。
  // 重写基类的虚函数 raiseSalary
  virtual void raiseSalary() { cout << 100 << endl; }

  virtual void promote() { /* Manager specific promote */
  }
};

// 派生类 Engineer，继承自 Employee
class Engineer : public Employee {
public: // 同样假设这里是 public
  // 重写基类的虚函数 raiseSalary
  virtual void raiseSalary() { cout << 200 << endl; }

  virtual void promote() { /* Manager specific promote */
  }
};

// Similarly, there may be other types of employees
// We need a very simple function to increment salary of all employees
// Note that emp[] is an array of pointers and actual pointed objects can
// be any type of employees. This function should ideally be in a class
// like Organization, we have made it global to keep things simple
// 用于统一处理所有 Employee 类型的函数
void globalRaiseSalary(Employee *emp[], int n) {
  for (int i = 0; i < n; i++)
    // 32行：通过基类指针调用虚函数，实现运行时多态
    emp[i]->raiseSalary(); // Polymorphic Call: Calls raiseSalary()
                           // according to the actual object, not
                           // according to the type of pointer
}

int main() {
  // 37行：声明一个 Employee 指针数组并初始化
/*
由于 Manager 和 Engineer 都继承自 Employee，
C++ 允许从派生类指针（或引用）隐式转换为基类指针（或引用）。
这种转换是安全的，因为派生类对象包含了基类部分。
所以，这里的 Manager * 和 Engineer * 
指针被隐式提升 (upcast) 为 Employee * 类型，
并存储到 emp 数组中
new Type;: 在堆上分配 Type 类型的内存，并对该对象执行默认初始化 (default-initialization)。
new Type();: 在堆上分配 Type 类型的内存，并对该对象执行值初始化 (value-initialization)。
new Type(args...);: 在堆上分配 Type 类型的内存，并使用指定的参数 args... 调用 Type 对应的构造函数进行初始化。
new Manager() 显式地要求值初始化，这会调用 Manager 的默认构造函数。
new Engineer 要求默认初始化，这也会调用 Engineer 的默认构造函数。
*/
  Employee *emp[] = {new Manager(), new Engineer};
  // 38行：调用 globalRaiseSalary 函数
  globalRaiseSalary(emp, 2);

  // 重要的注意事项：代码使用了 new，但没有对应的 delete。这会导致内存泄漏。
  // 在实际代码中，需要遍历 emp 数组并 delete 每个元素指向的对象。
  // Employee *emp[] = {new Manager(), new Engineer};
  for (int i = 0; i < 2; ++i) {
      delete emp[i]; // 释放动态分配的内存
      emp[i] = nullptr; // 防止野指针
  }

  return 0;
}
/*



好的，我们来详细解析一下第 37 行 `Employee *emp[] = {new Manager(), new Engineer};` 中为什么 `new Engineer` 后面没有括号 `()`。

这涉及到 C++ 中使用 `new` 运算符创建对象的语法规则。`new` 运算符有几种不同的形式，用于在堆上分配内存并构造对象：

1.  **`new Type;`**: 在堆上分配 `Type` 类型的内存，并对该对象执行**默认初始化 (default-initialization)**。
2.  **`new Type();`**: 在堆上分配 `Type` 类型的内存，并对该对象执行**值初始化 (value-initialization)**。
3.  **`new Type(args...);`**: 在堆上分配 `Type` 类型的内存，并使用指定的参数 `args...` 调用 `Type` 对应的**构造函数**进行初始化。

现在来看 `Manager` 和 `Engineer` 这两个类。在你的代码中，它们都继承自 `Employee`，并且**没有显式定义任何构造函数**。

当一个类没有定义任何构造函数时，编译器会**隐式地声明**一个**默认构造函数**（如果符合条件的话，例如基类有默认构造函数）。在你的例子中，`Employee` 类有一个默认构造函数 `Employee() {}`，所以 `Manager` 和 `Engineer` 都会获得一个由编译器隐式声明的默认构造函数。

有了隐式声明的默认构造函数后，我们再来看 `new Manager()` 和 `new Engineer`：

*   **`new Manager()`**: 这使用了形式 `new Type()`。由于 `Manager` 有一个默认构造函数，`new Manager()` 会调用 `Manager` 的默认构造函数来初始化对象。
*   **`new Engineer`**: 这使用了形式 `new Type;`。由于 `Engineer` 有一个默认构造函数，`new Engineer` 会对 `Engineer` 对象执行默认初始化。对于类类型，默认初始化的行为就是调用其默认构造函数。

**结论：**

对于具有默认构造函数的类类型 `Type`，`new Type;` 和 `new Type();` 这两种语法都会导致调用该类的默认构造函数。它们的行为在这种情况下是**等价的**。

因此，在第 37 行中：

*   `new Manager()` 显式地要求值初始化，这会调用 `Manager` 的默认构造函数。
*   `new Engineer` 要求默认初始化，这也会调用 `Engineer` 的默认构造函数。

程序员选择在 `new Manager()` 后面加上括号 `()`，而在 `new Engineer` 后面省略括号，仅仅是一种语法选择，因为对于这些拥有默认构造函数的类来说，加不加括号的效果是一样的——都是调用默认构造函数来创建对象。

所以，`new Engineer` 后面没有括号是完全合法的，并且它和 `new Engineer()` 一样，都是在堆上创建一个 `Engineer` 对象并调用其默认构造函数。

代码解读：
基类 Employee: 定义了员工的通用行为，包括 raiseSalary() 和 promote()。这两个函数被声明为 virtual，表明它们是虚函数。虚函数是实现运行时多态的关键。当通过基类指针或引用调用虚函数时，实际执行的是对象所属派生类中该函数的版本（如果派生类重写了该函数）。
派生类 Manager 和 Engineer: 这两个类继承自 Employee，并重写了 raiseSalary() 和 promote() 虚函数。注意，即使派生类中没有显式使用 virtual 关键字来重写虚函数，它仍然是虚函数，但为了代码的可读性和清晰性，通常建议在派生类的重写函数前也加上 virtual 关键字（尽管 C++11 引入的 override 关键字是更好的做法）。派生类中的 raiseSalary() 函数打印了不同的值（100 和 200），体现了各自不同的加薪逻辑。
globalRaiseSalary 函数: 这个函数接受一个 Employee 指针数组和数组大小作为参数。它的目的是对所有类型的员工执行统一的加薪操作。在循环内部，它通过基类指针 emp[i] 调用 raiseSalary()。由于 raiseSalary() 是虚函数，这里会发生运行时多态：编译器会根据 emp[i] 实际指向的对象的类型（是 Manager 还是 Engineer）来决定调用哪个版本的 raiseSalary() 函数。
main 函数:
第 37 行: 这是代码的核心之一，我们将在下面重点分析。
第 38 行: 调用 globalRaiseSalary 函数，并将 emp 数组和大小 2 传递进去。此时，程序会遍历 emp 数组，通过多态调用分别执行 Manager::raiseSalary() 和 Engineer::raiseSalary()。
内存泄漏: 一个非常重要的点是，第 37 行使用了 new 在堆上动态分配了 Manager 和 Engineer 对象，但代码没有对应的 delete 来释放这些内存。这会导致内存泄漏。在实际开发中，这是必须避免的。通常会使用智能指针（如 std::unique_ptr 或 std::shared_ptr）或容器（如 std::vector<std::unique_ptr<Employee>>）来自动管理动态分配的内存。
重点分析第 37 行语法：Employee *emp[] = {new Manager(), new Engineer};
这行代码包含以下几个部分：
Employee *emp[]:
Employee *: 表示一个指向 Employee 类型对象的指针。
emp[]: 声明 emp 是一个数组。数组的元素类型是 Employee *。方括号内没有指定数组大小，这意味着数组的大小将根据后面的初始化列表来确定。
合起来，Employee *emp[] 声明了一个名为 emp 的数组，其元素是指向 Employee 对象的指针，数组大小由初始化列表决定。
=: 赋值运算符，用于初始化数组。
{new Manager(), new Engineer}:
这是初始化列表 (Initializer List)。用于初始化数组或容器。
new Manager(): 这是在堆上动态分配一个 Manager 对象的表达式。new 运算符会调用 Manager 类的构造函数来创建对象，并返回一个指向这个 Manager 对象的指针（类型是 Manager *）。
new Engineer(): 同理，在堆上动态分配一个 Engineer 对象，并返回一个指向它的指针（类型是 Engineer *）。
类型转换: 在这个初始化列表中，new Manager() 返回的 Manager * 类型指针和 new Engineer() 返回的 Engineer * 类型指针被用来初始化一个 Employee * 类型的数组。由于 Manager 和 Engineer 都继承自 Employee，C++ 允许从派生类指针（或引用）隐式转换为基类指针（或引用）。这种转换是安全的，因为派生类对象包含了基类部分。所以，这里的 Manager * 和 Engineer * 指针被隐式提升 (upcast) 为 Employee * 类型，并存储到 emp 数组中。
数组大小: 初始化列表中有两个元素，所以编译器会自动确定 emp 数组的大小为 2。
综合来看，第 37 行做了以下事情：
声明了一个名为 emp 的、大小为 2 的数组。
数组的每个元素都是一个指向 Employee 对象的指针。
在堆上动态创建了一个 Manager 对象和一个 Engineer 对象。
将指向 Manager 对象的指针（隐式转换为 Employee * 类型）作为数组的第一个元素。
将指向 Engineer 对象的指针（隐式转换为 Employee * 类型）作为数组的第二个元素。
这样，emp 数组就存储了指向不同类型（Manager 和 Engineer）的对象的基类指针。这正是实现运行时多态的基础，使得我们可以通过统一的 Employee * 指针来调用不同派生类的虚函数实现各自的逻辑，如第 32 行在 globalRaiseSalary 函数中所展示的。
需要再次强调的是，这段代码为了示例多态而牺牲了内存安全。在实际应用中，务必对 new 的对象进行 delete，或者使用智能指针来自动化这一过程。
*/