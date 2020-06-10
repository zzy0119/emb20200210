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
	void setName(char *name);
	void setAge(int age);
	void setScore(float score);
	void show();
	void printThis();
};

void Person::setName(char *name)
{
	this->name = name;
}

void Person::setAge(int age)
{
	this->age = age;
}

void Person::setScore(float s)
{
	this->score = s;
}

void Person::show()
{
	cout << this->name << "的年龄是" << this->age << "成绩是" \
		<< this->score << endl;
}

void Person::printThis()
{
	cout << this << endl;
}

int main(void)
{
	Person p;// 栈
	Person *pp = new Person;

	// p.m_name = "xx";
	p.setName("c++");
	p.setAge(20);
	p.setScore(100);
	p.show();

	pp->setName("point");
	pp->setAge(22);
	pp->setScore(98.3);
	pp->show();

	pp->printThis();
	cout << pp << endl;
	
	return 0;
}

