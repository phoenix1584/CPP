/*
 * Copyright (c) 2018
 * Author: phoenix1584
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

int global_data = 1;
auto const divisor = 2;
std::condition_variable cv;
std::mutex m;

void f_printer(std::function<bool()> condition){
    for(auto x = 0 ; x < CONST_NUM ; ++x){
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk,condition);
        std::cout << ((global_data % divisor) ? "ODD" : "EVEN") << " : " << global_data << "\n";
        ++global_data;
        lk.unlock();
        cv.notify_all();
    }
}

void LambdaTest(std::function<bool()> l){
    l();
}

int main() {
    {
        unsigned int n = std::thread::hardware_concurrency();
        std::cout << n << " Concurrent threads are supported.\n";
        std::function<bool()> l = [](){ std::cout << "it works.\n======================================\n"; return true; };
        LambdaTest(l);
    }
    
    std::thread t_odd(f_printer,std::function<bool()>([](){return (global_data % divisor);}));
    std::thread t_even(f_printer,std::function<bool()>([](){return (0 == global_data % divisor);}));
    cv.notify_all();
    t_odd.join();
    t_even.join();
    return 0;
}



