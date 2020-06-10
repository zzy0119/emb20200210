#include <iostream>

/*
 this指针
 	1.const类型的指针，不能赋值，修改
	2.只能在成员函数内使用
	3.只有对象被创建后才有意义
 */

using namespace std;

// 类的声明
class Person {
private:// 私有的
	char *name;
	int age;
	float score;
public:
	static int m_total;// 静态成员变量
public:
	Person(char *nm, int a, float s);
	void show();
	void printThis();
	// 静态成员函数
	static int getTotal();
};

// 静态成员变量初始化
int Person::m_total = 0;

Person::Person(char *nm, int a, float s):name(nm), age(a), score(s) 
{
	m_total ++;
}

void Person::show()
{
	cout << this->name << "的年龄是" << this->age << "成绩是" \
		<< this->score << endl;
	cout << "共有" << m_total << "名学生" << endl;
}

void Person::printThis()
{
	cout << this << endl;
}

int Person::getTotal()
{
	return m_total;
}

int main(void)
{
	(new Person("Lily", 19, 90))->show();
	(new Person("Lilei", 20, 99))->show();
	(new Person("hanmeimei", 18, 92))->show();
	(new Person("reli", 20, 97))->show();

	cout << Person::m_total << endl;
	cout << Person::getTotal() << endl;
	return 0;
}

