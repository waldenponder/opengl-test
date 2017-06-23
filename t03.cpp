// t03.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

class AAA
{
public:
	AAA()
	{
		cout << " AAA()  " << i << endl;
	}
	
	AAA(const AAA&& a)
	{
		cout << "AAA&& " << i << "   a.i " << a.i << endl;
	}

	~AAA()
	{
		cout << " ~AAA()  " << i <<  endl;
	}

	AAA(const AAA & a) 
	{
		cout << " AAA(const AAA & a)  " << i << "   a.i   " << a.i << endl;
	}

	AAA & operator = (const AAA & a)
	{
		cout << " AAA && operator =   " << i << endl;
		return *this;
	}

	int i;
};

AAA getA()
{
	cout << "enter  " << endl;
	AAA aaa;
	aaa.i = 12;

	cout << "leave  " << endl;
	return aaa;
}

void p(const string & a)
{
	std::cout << "11111  " << endl;
}

void p(const string && a)
{
	std::cout << "222222  " << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (1)
	{
		AAA //a1;
		a1 = getA();
	}

	if (0)
	{
		AAA a(getA());
		a.i = 123;
	}

	//string ss("aaa");
	//p(ss);
	//p("123");

	while (true)
	{}
	return 0;
}

