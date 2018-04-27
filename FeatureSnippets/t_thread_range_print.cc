/*
 * Copyright (c) 2018
 * Author phoenix1584 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <chrono>

int global_data = 1;
std::condition_variable cv;
std::mutex m;

void f_printer(std::function<bool()> condition,std::function<bool()> range){
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk,condition);
    while(range){
        std::cout << global_data << "\n";
        ++global_data;
    }
    lk.unlock();
    cv.notify_all();
}

int main() {
    std::thread t1(f_printer,std::function<bool()>([](){return (global_data > 0);}),std::function<bool()>([](){return (global_data <= 20);}));
    std::thread t2(f_printer,std::function<bool()>([](){return (global_data > 20);}),std::function<bool()>([](){return (global_data <= 60);}));
    std::thread t3(f_printer,std::function<bool()>([](){return (global_data > 60);}),std::function<bool()>([](){return (global_data <= 100);}));
    t1.join();
    t2.join();
    t3.join();
    return 0;
}

