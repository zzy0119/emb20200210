#include <iostream>

using namespace std;

int main(void)
{
	int *p = new int;
	int *q = new int[10];

	*p = 100;
	cout << *p << endl;

	// 释放
	delete p;
	delete[] q;

	return 0;
}
