#include <iostream>
#include "ethread.h"
using namespace std;

benaphore b1, b2;

int threadme1()
{
	thread::sleep(1000);
	cout << "A has finished\n";
	return 1000;
}

void threadme2(int time)
{
	thread::sleep(time);
	cout << "B has finished\n";
}

string threadme3(int time, string message)
{
	thread::sleep(time);
	cout << message;
	return message;
}

void print(char c, int j)
{
	for (int i = 0; i < j; i++)
	{
		cout << c;
		thread::sleep(1);
	}
	cout << '\n';
}

void safeprint(char c, int j)
{
	b1.lock();
	for (int i = 0; i < j; i++)
	{
		cout << c;
		thread::sleep(1);
	}
	cout << '\n';
	b1.unlock();
}

void recursive(char c, int i)
{
	if (i == 50)
	{
		cout << '\n';
		return;
	}
	cout << c;
	thread::sleep(1);
	recursive(c, i + 1);
}

void saferecursive(char c, int i)
{
	if (i == 50)
	{
		cout << '\n';
		return;
	}
	b2.r_lock();
	cout << c;
	thread::sleep(1);
	saferecursive(c, i + 1);
	b2.r_unlock();
}

int main()
{
	cout << "three threads\n";
	thread a(threadme1);
	thread b(threadme2, 600);
	string lol = "C has finished\n";
	thread c(threadme3, 120, lol);
	a.rejoin();
	b.rejoin();
	c.rejoin();
	cout << "return value of A: " << a.getResult<int>() << endl;
	cout << "return value of B: " << b.getResult<int>() << endl;
	cout << "return value of C: " << c.getResult<string>();
	cout << "\nPress any key to begin Benaphore test.";
	getline(cin, lol);
	cout << "Without Benaphore:\n";
	thread d(print, 'a', 50);
	thread e(print, 'b', 50);
	thread f(print, 'c', 50);
	d.rejoin();
	e.rejoin();
	f.rejoin();
	cout << "With Benaphore:\n";
	thread g(safeprint, 'a', 50);
	thread h(safeprint, 'b', 50);
	thread i(safeprint, 'c', 50);
	g.rejoin();
	h.rejoin();
	i.rejoin();
	cout << "\nPress any key to begin recursive Benaphore test.";
	getline(cin, lol);
	cout << "Without Benaphore:\n";
	thread j(recursive, 'a', 0);
	thread k(recursive, 'b', 0);
	thread l(recursive, 'c', 0);
	j.rejoin();
	k.rejoin();
	l.rejoin();
	cout << "With Benaphore:\n";
	thread m(saferecursive, 'a', 0);
	thread n(saferecursive, 'b', 0);
	thread o(saferecursive, 'c', 0);
	m.rejoin();
	n.rejoin();
	o.rejoin();
	getline(cin, lol);
}

