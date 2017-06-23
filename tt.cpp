#include <iostream>
#include <thread>
#include <mutex>  

using namespace std;

std::mutex mtx;

class AAA
{
public:
	static AAA* ins()
	{
		if (_aa == nullptr)
		{
			mtx.lock();
			if (_aa == nullptr)
			{
				_aa = new AAA;
			}
			else
			{
				cout << "aaaa " << endl;
			}
			mtx.unlock();
		}

		return _aa;
	}

private:
	AAA() 
	{
		cout << "AAAAAAA" << endl; 
	}
	static AAA * _aa;
};


AAA* AAA::_aa;

void pp()
{
	for (int i = 0; i < 1000000; i++)
	{
		AAA::ins();
	}
}

void main()
{
	thread t(pp);
			  
	thread t2(pp);

	t2.join();
	t.join();

	while (true)
	{
	}
}