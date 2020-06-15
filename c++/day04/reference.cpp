#include <iostream>

using namespace std;

// 交换两个整型变量
void swap(int &a, int &b)
{
	int t;
	t = a;
	a = b;
	b = t;
}

int main(void)
{
	int num = 100;
	int &r = num; // 定义的同时初始化,从一而终，不能在作为其他变量的引用
	int m = 100, n = 200;

	r = 200;

	swap(m, n);
	cout << "m:" << m << "," << "n:" << n << endl;

	cout << num << endl;
	cout << r << endl;
	cout << &num << "," << &r << endl;

	return 0;
}

