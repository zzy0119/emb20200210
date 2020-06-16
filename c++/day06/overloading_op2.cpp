#include <iostream>

using namespace std;

// 复数类
class Complex {
	public:
		Complex();
		Complex(double real, double imag);
		friend Complex operator+(const Complex &A, const Complex &B);
		friend bool operator==(const Complex &a, const Complex &b);
		friend Complex operator-(const Complex &A, const Complex &B);
		void display() const;
	private:
		double m_real;
		double m_imag;
};

Complex::Complex() : m_real(0.0), m_imag(0.0) {}
Complex::Complex(double real, double imag) : m_real(real), m_imag(imag) {}
Complex operator+(const Complex &A, const Complex &B)
{
	Complex C;
	C.m_real = B.m_real + A.m_real;
	C.m_imag = B.m_imag + A.m_imag;

	return C;
}

// 重载-运算符
Complex operator-(const Complex &A, const Complex &B)
{
	Complex C;
	C.m_real = A.m_real - B.m_real;
	C.m_imag = A.m_imag - B.m_imag;

	return C;
}

// 重载==运算符
bool operator==(const Complex &a, const Complex &b)
{
	if (a.m_real == b.m_real && a.m_imag == b.m_imag)
		return true;
	else
		return false;
}

void Complex::display() const
{
	cout << m_real << "+" << m_imag << "i" << endl;
}

int main(void)
{
	Complex obj1(2.3, 5.2);
	Complex obj2(3.9, 5.5);

	Complex obj3 = obj1 + obj2;// operator+(obj1, obj2)
	obj3.display();

	obj3 = obj1 - obj2;
	obj3.display();
	
	if (obj1==obj2)
		cout << "true" << endl;
	else
		cout << "false" << endl;

	return 0;
}

