#include <iostream>

using namespace std;
// 算一个整型数值的n次方
int square_n(int n, int m=2)
{
	int v = n;
	for (int i = 0; i < m-1; i++)
		n *= v;
	return n;
}

int main(void)
{
	cout << square_n(2, 5) << endl;
	cout << square_n(3) << endl;

	return 0;
}

