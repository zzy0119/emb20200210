#include <iostream>

using namespace std;

template<typename T1, typename T2> // 不能有分号
class Point {
public:
	Point(T1 x, T2 y) : m_x(x), m_y(y) {}

public:
	T1 getX() const;
	T2 getY() const;
	void setX(T1 x);
	void setY(T1 y);
private:
	// x, y坐标允许任意类型
	T1 m_x;
	T2 m_y;
};
template<typename T1, typename T2> // 模板头
T1 Point<T1, T2>::getX() const
{
	return m_x;
}
template<typename T1, typename T2> // 模板头
T2 Point<T1, T2>::getY() const
{
	return m_y;
}
template<typename T1, typename T2> // 模板头
void Point<T1, T2>::setX(T1 x)
{
	m_x = x;
}
template<typename T1, typename T2> // 模板头
void Point<T1, T2>::setY(T1 y)
{
	m_y = y;
}

int main(void)
{
	Point<int, int> p1(1, 2);
	Point<char *, char *> p2("东经20度", "北纬100度");
	Point<int, float> *p3 = new Point<int, float>(1, 10.1f);

	cout << p3->getX() << endl;
	cout << p3->getY() << endl;

	return 0;
}

