#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

namespace MyTypes 
{
	const bool kDebugOutput = false;	// debug output to see how many times comparisons/ctors/dtors/assignments are called
	bool gSleep = false;				// sleep to emulate work with "heavy" classes K and V

	inline void sleep() { std::this_thread::sleep_for(std::chrono::microseconds(500)); }

	class MyKey {
	public:
		MyKey() : MyKey(0)
		{
		};
		MyKey(int val) 
		{
			m_val = new int[1];
			m_val[0] = val;

			if (kDebugOutput) std::cout << "KEY CONSTRUCTOR: " << m_val[0] << std::endl;
			if (gSleep) sleep();
		};
		MyKey(const MyKey& other)
		{
			m_val = new int[1];
			m_val[0] = other.m_val[0];
			if (kDebugOutput) std::cout << "KEY COPY CONSTRUCTOR: " << m_val[0] << std::endl;
			if (gSleep) sleep();
		};
		MyKey(MyKey&& other) noexcept
		{
			m_val = other.m_val;
			other.m_val = nullptr;
			if (kDebugOutput) std::cout << "KEY MOVE CONSTRUCTOR: " << m_val[0] << std::endl;
			if (gSleep) sleep();
		}
		~MyKey()
		{
			if (kDebugOutput) std::cout << "KEY DESTRUCTOR: " << m_val[0] << std::endl;
			if (gSleep) sleep();
			delete[] m_val;	
		};
		bool operator< (const MyKey& other) const
		{
			if (kDebugOutput) std::cout << "KEY COMPARISON: " << m_val[0] << " < " << other.m_val[0] << " ? " << std::endl;
			if (gSleep) sleep();
			return m_val[0] < other.m_val[0];
		};
		bool operator== (const MyKey&) = delete;
		int get() const
		{
			return m_val[0];
		}
	private:
		int* m_val = nullptr;
	};

	class MyVal
	{
	public:
		MyVal()
		{
			m_val = new std::string[1];
			m_val[0] = "";
			if (kDebugOutput) std::cout << "VAL CONSTRUCTOR: \"" << m_val[0] << "\"" << std::endl;
			if (gSleep) sleep();
		};
		MyVal(std::string val) {
			m_val = new std::string[1];
			m_val[0] = val;
			if (kDebugOutput) std::cout << "VAL CONSTRUCTOR: \"" << m_val[0] << "\"" << std::endl;
			if (gSleep) sleep();
		};
		MyVal(const MyVal& other)
		{
			m_val = new std::string[1];
			m_val[0] = other.m_val[0];
			if (kDebugOutput) std::cout << "VAL COPY CONSTRUCTOR: \"" << m_val[0] << "\"" << std::endl;
			if (gSleep) sleep();
		};
		~MyVal()
		{
			if (kDebugOutput) std::cout << "VAL DESTRUCTOR: \"" << m_val[0] << "\"" << std::endl;
			if (gSleep) sleep();
			delete[] m_val;
			m_val = nullptr;
		}
		MyVal& operator= (const MyVal& other)
		{
			m_val[0] = other.m_val[0];
			if (kDebugOutput) std::cout << "VAL ASSIGNMENT: \"" << m_val[0] << "\"" << std::endl;
			if (gSleep) sleep();
			return *this;
		};
		bool operator==(const MyVal& other) const
		{
			if (kDebugOutput) std::cout << "VAL COMPARISON: " << m_val[0] << " == " << other.m_val[0] << " ? " << std::endl;
			if (gSleep) sleep();
			return m_val[0] == other.m_val[0];
		}
		std::string get() const
		{
			return m_val[0];
		}
		MyVal(MyVal&& other) noexcept
		{
			if (kDebugOutput) std::cout << "MOVE CONSTRUCTOR: " << m_val[0] << " = " << other.m_val[0] << " ? " << std::endl;
			if (gSleep) sleep();
			m_val = other.m_val;
			other.m_val = nullptr;
		}
		MyVal& operator=(MyVal&& other) noexcept
		{
			if (kDebugOutput) std::cout << "MOVE ASSIGNMENT: " << m_val[0] << " = " << other.m_val[0] << " ? " << std::endl;
			if (gSleep) sleep();
			m_val = other.m_val;
			other.m_val = nullptr;
			return *this;
		}
	private:
		std::string* m_val = nullptr;
	};
} // namespace