#include <iostream>
using namespace std;

class Apple {
public:
  // static member function
  static void printMsg(int i) { cout << "Welcome to Apple!" << i << endl; }
};

// main function
int main() {
  // invoking a static member function
  Apple::printMsg(2);
  Apple apple;
  apple.printMsg(3);
}
