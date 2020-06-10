#include <iostream>

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
	// 常成员函数
	char *getName() const;
	int getAge() const;
	float getScore() const;
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
char *Person::getName() const
{
	return this->name;
}

int Person::getAge() const
{
	return this->age;
}
float Person::getScore() const
{
	return this->score;
}

int main(void)
{
	// 常对象 Person const *p--->只能访问修改调用常变量和常函数
	const Person *p = new Person("c++", 20, 100);
	
	cout << p->getName() << "," << p->getAge() << "," << p->getScore() << endl;
	// p->show();
		
	return 0;
}

