#include <iostream>

using namespace std;

// 类的声明
class Person {
private:// 私有的
	char *m_name;
	int m_age;
	float m_score;
public:
	void setName(char *name);
	void setAge(int age);
	void setScore(float score);
	void show();
};

void Person::setName(char *name)
{
	m_name = name;
}

void Person::setAge(int age)
{
	m_age = age;
}

void Person::setScore(float s)
{
	m_score = s;
}

void Person::show()
{
	cout << m_name << "的年龄是" << m_age << "成绩是" \
		<< m_score << endl;
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
	
	return 0;
}

