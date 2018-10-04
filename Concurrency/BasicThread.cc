// Copyright (c) 2018 phoenix1584
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <iostream>
#include <thread>

void ThreadEngine(){
    std::cout << "Hello from thread!\n";
}

int main(){
    std::thread t(ThreadEngine);
    t.join();
}