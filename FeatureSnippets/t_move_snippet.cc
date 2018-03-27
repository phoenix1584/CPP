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

// Refs : https://docs.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp

#include <iostream>  
#include <algorithm>  
#include <vector>  

class MemoryBlock  
{  
	public:  

		// Simple constructor that initializes the resource.  
		explicit MemoryBlock(size_t length)  
			: m_length(length)  
			  , m_data(new int[length])  
		{  
			std::cout << __PRETTY_FUNCTION__ << " length = " << m_length << ".\n" ;  
		}  

		// Destructor.  
		~MemoryBlock()  
		{  
			std::cout << __PRETTY_FUNCTION__ << " length = " << m_length << ".\n";  

			if (m_data != nullptr)  
			{  
				std::cout << " Deleting resource.\n";  
				// Delete the resource.  
				delete[] m_data;  
			}  
		}  

		// Copy constructor.  
		MemoryBlock(const MemoryBlock& other)  
			: m_length(other.m_length)  
			  , m_data(new int[other.m_length])  
		{  
			std::cout <<  __PRETTY_FUNCTION__ << other.m_length << ". Copying resource.\n";  
			std::copy(other.m_data, other.m_data + m_length, m_data);  
		}  

		// Copy assignment operator.  
		MemoryBlock& operator=(const MemoryBlock& other)  
		{  
			std::cout <<  __PRETTY_FUNCTION__  << other.m_length << ". Copying resource.\n";  
			if (this != &other)  
			{  
				// Free the existing resource.  
				delete[] m_data;  

				m_length = other.m_length;  
				m_data = new int[m_length];  
				std::copy(other.m_data, other.m_data + m_length, m_data);  
			}  
			return *this;  
		} 

	 	// Move constructor.  
		MemoryBlock(MemoryBlock&& other)  
		   : m_length(0)   
		   , m_data(nullptr)
		{ 
			std::cout << __PRETTY_FUNCTION__ << other.m_length << ". Moving resource.\n"; 
		   *this = std::move(other);  
		}  	

		// Move assignment operator.  
		MemoryBlock& operator=(MemoryBlock&& other)  
		{  
		   std::cout << __PRETTY_FUNCTION__ << other.m_length << ".\n";  
		
		   if(this != &other)  
		   {  
		      // Free the existing resource.  
		      delete[] m_data;  
		
		      // Copy the data pointer and its length from the   
		      // source object.  
		      m_data = other.m_data;  
		      m_length = other.m_length;  
		
		      // Release the data pointer from the source object so that  
		      // the destructor does not free the memory multiple times.  
		      other.m_data = nullptr;  
		      other.m_length = 0;  
		   }  
		   return *this;  
		}   

		// Retrieves the length of the data resource.  
		size_t Length() const  
		{  
			return m_length;  
		}  

	private:  
		size_t m_length; // The length of the resource.  
		int* m_data; // The resource.  
};  

int main()  
{ 
	std::cout << "Compiled at : " << __DATE__  << ":" <<  __TIME__ << "\n"; 
	// Create a vector object and add a few elements to it.  
	std::vector<MemoryBlock> v; 
	std::cout << "-----------------------\n";
	v.push_back(MemoryBlock(25));  
	std::cout << "-----------------------\n";
	v.push_back(MemoryBlock(75));  
	std::cout << "-----------------------\n";
	// Insert a new element into the second position of the vector.  
	v.insert(v.begin() + 1, MemoryBlock(50));  
	std::cout << "------Emplace--------------\n";
	v.emplace_back(10);
	std::cout << "-----------------------\n";
	v.emplace_back(20);
	std::cout << "-----------------------\n";
}  
