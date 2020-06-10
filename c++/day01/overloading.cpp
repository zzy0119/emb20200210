#include <iostream>
// 函数的重载--->多个函数有相同的名字，只要参数列表不同就可以
// 参数列表----> 参数的类型，参数的个数，参数的顺序

using namespace std;
void swap(int *m, int *n)
{
	int t;
	t = *m;
	*m = *n;
	*n = t;
}

void swap(float *m, float *n)
{
	float t;
	t = *m;
	*m = *n;
	*n = t;
}

int main(void)
{
	int a, b;
	float a2, b2;
	
	a = 10, b = 20;
	swap(&a, &b);
	cout << a << "," << b << endl;

	a2 = 10.45, b2 = 90.3;
	swap(&a2, &b2);
	cout << a2 << "," << b2 << endl;

	return 0;
}

