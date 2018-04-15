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

// Refs : http://en.cppreference.com/w/cpp/language/lambda
//        https://docs.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cmath>

auto func_print = []{ std::cout << "------------------\n"; };

void BasicLambda(){
	func_print();
	int a = 1, b = 1, c = 1;
	auto m1 = [a, &b, &c]() mutable {
		auto m2 = [a, b, &c]() mutable {
			std::cout << a << b << c << '\n';
			a = 4; b = 4; c = 4;
		};
		a = 3; b = 3; c = 3;
		m2();
	};

	a = 2; b = 2; c = 2;
	m1();                             // calls m2() and prints 123
	std::cout << a << b << c << '\n'; // prints 234
}

void AlgoLambda(){
	func_print();
	std::vector<int> c = {1, 2, 3, 4, 5, 6, 7};
	int x = 5;
    c.erase(std::remove_if(c.begin(), c.end(), [x](int n) { return n < x; }), c.end());
 
    std::cout << "c: ";
    std::for_each(c.begin(), c.end(), [](int i){ std::cout << i << ' '; });
    std::cout << '\n';
 
    // the type of a closure cannot be named, but can be inferred with auto
    // since C++14, lambda could own default arguments
    auto func1 = [](int i = 6) { return i + 4; };
    std::cout << "func1: " << func1() << '\n';
 
    // like all callable objects, closures can be captured in std::function
    // (this may incur unnecessary overhead)
    std::function<int(int)> func2 = [](int i) { return i + 4; };
    std::cout << "func2: " << func2(6) << '\n';
}

void ScopeLambda1(){
	func_print();
	auto x = 1;
	auto l = [&x](){
		auto y = 2;
		x *= y;
	};
	l();
	std::cout << "x : " << x << "\n"; 
}

void ScopeLambda2(){
	func_print();
	const auto n = 10;
	auto l = [&n]()-> decltype(n){ return n * n ; };
	std::cout << "n : " << l() << "\n";
}

void ScopeLambda3(){
    func_print();
    const auto x = 20;
    const auto y = 3;
    auto l = [&]()-> decltype(x) { return std::pow(x,y);};
	std::cout << "x : " << l() << "\n";
}

int main(){
	BasicLambda();
	AlgoLambda();
	ScopeLambda1();
	ScopeLambda2();
	ScopeLambda3();
}
