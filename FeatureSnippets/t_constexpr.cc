/*
 * Copyright (c) 2018
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

// Refs : https://docs.microsoft.com/en-us/cpp/cpp/constexpr-cpp
//        http://en.cppreference.com/w/cpp/language/constexpr

#include <iostream>

constexpr int factorial(int n){
    return (n <= 1 ? 1 : (n * factorial(n - 1)));
}

// literal class
class ConstStr {
    const char* p;
    std::size_t sz;
public:
    template<std::size_t N>
    constexpr ConstStr(const char(&a)[N]): p(a), sz(N - 1) {}
 
    // constexpr functions signal errors by throwing exceptions
    // in C++11, they must do so from the conditional operator ?:
    constexpr char operator[](std::size_t n) const
    {
        return n < sz ? p[n] : throw std::out_of_range("");
    }
    constexpr std::size_t size() const { return sz; }
};
 
// C++11 constexpr functions had to put everything in a single return statement
// (C++14 doesn't have that requirement)
constexpr std::size_t compare(ConstStr s)
{
	return s.size();
}
 
// output function that requires a compile-time constant, for testing
template<int n>
struct constN
{
    constN() { 
		static_assert(n);
		std::cout << n << '\n'; 
	}
};
 
int main()
{
	// CONST_NUM is being provided as a compiler time paremeter with -D flag.
    std::cout << CONST_NUM << "! = " << factorial(CONST_NUM) << "\n"; 
    
	constN<compare("Hello, world!")> out2; // implicitly converted to ConstStr
	// constN<compare("")> out3; // Will fail to compile since the string length is 0.
}
