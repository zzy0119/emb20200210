#include <iostream>

using namespace std;

// 基类
class A {
	protected:
		int m_a;
	public:
		A(int a);
		void show();
};

A::A(int a) : m_a(a) {}
void A::show()
{
	cout << "A: " << m_a << endl;
}

class B : public A{
	private:
		int m_b;
	public:
		B(int a, int b);
		void show();
};
B::B(int a, int b):A(a), m_b(b) {};
void B::show()
{
	cout << "B:" << m_a << "," << m_b << endl;
}

int main(void)
{
	A a(1);
	B b(2, 3);
	a.show();
	b.show();

	a = b;
	a.show();
	b.show();

	return 0;
}
