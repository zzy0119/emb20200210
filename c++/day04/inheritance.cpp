#include <iostream>

using namespace std;

// 基类
class Person {
	// private:
	protected:
		char *m_name;
		int m_age;
	public:
		void setName(char *name);
		void setAge(int age);
		char *getName();
		int getAge();
};
void Person::setName(char *name)
{
	m_name = name;
}
void Person::setAge(int age)
{
	m_age = age;
}
char *Person::getName()
{
	return m_name;	
}

int Person::getAge()
{
	return m_age;
}

class Student : public Person {
	private:
		float m_score;	
	public:
		void setScore(float score);
		float getScore();
};

void Student::setScore(float score)
{
	m_score = score;
	cout << m_name << endl;
}
float Student::getScore()
{
	return m_score;
}
int main(void)
{
	Student s;

	s.setName("小a");
	s.setAge(18);
	s.setScore(100);

	cout << s.getName() << endl;
	cout << s.getAge() << endl;
	cout << s.getScore() << endl;
	
	return 0;
}

