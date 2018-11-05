// Copyright (c) 2018 phoenix1584
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <iostream>
#include <thread>

void ThreadEngine() { std::cout << "Hello from thread!\n"; }

class Task {
public:
  void operator()() const { ThreadEngine(); }
};

int main() {
  std::thread t(ThreadEngine);
  t.join();

  std::thread t1{Task()};
  t1.join();

  std::thread t2([]{ThreadEngine();});
  t2.join();
}