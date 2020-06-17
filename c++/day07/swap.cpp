#include <iostream>

using namespace std;

#if 0
void swap(int *a, int *b)
{
	int t;
	t = *b;
	*b = *a;
	*a = t;
}

void swap(float *a, float *b)
{
	float t;
	t = *b;
	*b = *a;
	*a = t;
}
#endif

// 函数模板
template<typename T> void Swap(T &a, T &b)
{
	T temp;
	temp = a;	
	a = b;
	b = temp;
}

int main(void)
{
	int n1 = 100, n2 = 200;
	Swap(n1, n2);
	cout << n1 << "," << n2 << endl;

	float f1 = 10.4, f2 = 99.89;
	Swap(f1, f2);
	cout << f1 << "," << f2 << endl;

	return 0;
}

