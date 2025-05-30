//
// Created by light on 19-12-12.
//
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <bits/unique_ptr.h>  // ->  <memory>  unique_ptr

using namespace std;
unique_ptr<vector<string>> read_lines_from_file(string &file_name) {
    unique_ptr<vector<string>> lines(new vector<string>);
    string line;

    ifstream file_handle (file_name.c_str());
    while (file_handle.good() && !file_handle.eof()) {
    // while (getline(file_handle, line)) 解决多读一行问题
        getline(file_handle, line);
        lines->push_back(line);
    }

    file_handle.close();

    return lines;
}
int main() {
    // get file name from the first argument
    string file_name ("/home/light/CLionProjects/Morden_C++/CMakeLists.txt");
    int count = read_lines_from_file(file_name).get()->size();
    cout << "File " << file_name << " contains " << count << " lines.";
    cout<<endl;
    return 0;
}

/*



好的，从一个资深工程师的角度来看，这段代码是前一个示例 (`c++_example1.cpp`) 的改进版本，它引入了 C++11 的**智能指针 `std::unique_ptr`** 来更好地管理动态分配的内存资源，进一步体现了 **RAII (Resource Acquisition Is Initialization)** 的思想。

代码如下：
```1:32:workspace/cocobooks/CPlusPlusThings/codingStyleIdioms/3_RAII/c++_example2.cpp
//
// Created by light on 19-12-12.
//
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <bits/unique_ptr.h> // 这是一个非标准的头文件，应使用 <memory>

using namespace std;
unique_ptr<vector<string>> read_lines_from_file(string &file_name) {
    // 使用 unique_ptr 管理动态分配的 vector
    unique_ptr<vector<string>> lines(new vector<string>);
    string line;

    // ifstream 管理文件句柄，体现 RAII
    ifstream file_handle (file_name.c_str());
    //  file_handle.good() 检查流状态更可靠
    while (file_handle.good() && !file_handle.eof()) {
        getline(file_handle, line);
        lines->push_back(line);
    }

    file_handle.close(); // 显式关闭文件（可选，析构函数也会做）

    // 返回 unique_ptr，转移所有权
    return lines;
}
int main() {
    string file_name ("/home/light/CLionProjects/Morden_C++/CMakeLists.txt");
    // 调用函数，获取 unique_ptr
    unique_ptr<vector<string>> file_lines_ptr = read_lines_from_file(file_name);
    // 使用智能指针安全地访问成员，而不是 get()
    int count = file_lines_ptr->size();
    // 或者更简洁的链式调用 (不推荐 get())
    // int count = read_lines_from_file(file_name)->size();

    cout << "File " << file_name << " contains " << count << " lines.";
    cout<<endl;
    // main 函数结束，file_lines_ptr 超出作用域，unique_ptr 析构函数被调用，
    // 自动释放其管理的 vector 内存。没有内存泄漏！
    return 0;
}
```

**解读：**

1.  **包含智能指针头文件**: 代码包含了 `<bits/unique_ptr.h>`。这是一个**非标准的、编译器内部的头文件**。在标准的 C++ 中，应该包含 `<memory>` 头文件来使用 `std::unique_ptr` 和 `std::shared_ptr` 等智能指针。这是一个需要修正的地方。
2.  **`read_lines_from_file` 函数的改进**:
    *   **返回值类型**: 函数现在返回 `unique_ptr<vector<string>>`。这明确表示函数在堆上创建了一个 `vector<string>`，并将其**唯一所有权**传递给调用者。
    *   **动态内存管理**: `unique_ptr<vector<string>> lines(new vector<string>);` 在堆上使用 `new` 分配 `vector<string>` 对象。这个原始指针被立即传递给了 `unique_ptr`。从此刻起，这块动态分配的内存的生命周期就由 `lines` 这个 `unique_ptr` 对象负责管理了。
    *   **RAII 应用**:
        *   **文件句柄**: 就像前一个例子中最好的实现一样，`ifstream file_handle` 对象管理着文件句柄资源。它的生命周期与 `read_lines_from_file` 函数的作用域绑定，函数返回时，`file_handle` 析构并自动关闭文件。
        *   **动态内存**: `unique_ptr` 对象 `lines` 管理着动态分配的 `vector`。当 `lines` 超出作用域（无论是函数正常返回，还是因为异常导致函数提前退出），`lines` 的析构函数会被调用，并自动调用 `delete` 来释放它所指向的 `vector` 对象占用的内存。这完美地解决了前一个例子中 `read_lines_from_file1_1` 函数的内存泄漏问题。
    *   **循环条件**: 文件读取循环条件 `while (file_handle.good() && !file_handle.eof())` 相较于前一个例子虽然去掉了 `peek()!=EOF`，但仍然不是最佳实践。更安全和惯用的 C++ 文件读取循环是 `while (getline(file_handle, line))`。
    *   **显式关闭文件**: `file_handle.close();` 这一行是可选的，因为 `ifstream` 的析构函数会自动完成关闭操作。保留它可以更明确地表达文件何时不再需要，但在 RAII 风格中，通常依赖析构函数的自动行为。
3.  **`main` 函数**:
    *   **接收 `unique_ptr`**: `unique_ptr<vector<string>> file_lines_ptr = read_lines_from_file(file_name);` 接收了函数返回的 `unique_ptr`。这里的等号 (`=`) 实际上触发了 `unique_ptr` 的**移动语义**，将 `read_lines_from_file` 函数中局部 `unique_ptr` (`lines`) 对内存的所有权转移到了 `main` 函数中的 `file_lines_ptr`。函数返回后，局部 `lines` 变为空，其管理的内存现在完全由 `file_lines_ptr` 控制。
    *   **访问成员**: `file_lines_ptr.get()->size();` 这一行通过 `.get()` 获取 `unique_ptr` 管理的原始指针，然后通过原始指针访问 `vector` 的 `size()` 方法。虽然这里功能上没问题，但**不推荐**使用 `.get()` 来进行常规访问，因为它暴露了原始指针，打破了 `unique_ptr` 的封装和安全性保证。更推荐的方式是直接使用 `unique_ptr` 的解引用运算符：`file_lines_ptr->size()`。这使得代码更安全、更符合智能指针的使用模式。
    *   **内存释放**: 当 `main` 函数执行完毕，`file_lines_ptr` 超出作用域时，它的析构函数会自动调用 `delete` 来释放它所拥有的 `vector` 对象占用的内存，从而避免了内存泄漏。

**总结：**

这段代码是使用 C++ 智能指针管理动态内存的良好示例。它成功地将动态分配的 `vector` 对象的生命周期与 `unique_ptr` 对象绑定，确保了资源（内存）在不再需要时能够被自动释放，有效地防止了内存泄漏。同时，它也正确地利用了 `ifstream` 的 RAII 特性来管理文件句柄。

需要改进的地方主要包括：
*   将 `#include <bits/unique_ptr.h>` 改为标准的 `#include <memory>`。
*   优化文件读取循环条件，使用 `while (getline(file_handle, line))`。
*   避免在 `main` 函数中使用 `.get()` 获取原始指针来访问 `vector` 成员，直接使用 `file_lines_ptr->size()` 更安全。

尽管有这些小瑕疵，这段代码清晰地展示了智能指针在实践中的应用，以及它是如何在动态资源管理中实现 RAII 并提升代码安全性的。

*/