#include <iostream>
using namespace std;

enum class Color { RED, BLUE };
enum class Feeling { EXCITED, BLUE };

int main() {
  Color a = Color::BLUE; // 需要明确指定作用域
  Feeling b = Feeling::EXCITED;
  // std::cout << a << ":" << b << std::endl; // enum class 成员不能直接输出，需要转换为底层类型
  std::cout << static_cast<int>(a) << ":" << static_cast<int>(b) << std::endl;
  return 0;
}
