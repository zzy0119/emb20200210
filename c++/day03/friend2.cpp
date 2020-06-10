#include <iostream>

using namespace std;

// 声明地址类
class Address;

class Student {
	public:
		Student(char *name, int age);
		void show(Address *addr);
	private:
		char *m_name;
		int m_age;
};

class Address {
	public:
		Address(char *province, char *city, char *district);
		// Student类的show方法作为当前类的友元方法
		friend void Student::show(Address *addr);
	private:
		char *m_province;
		char *m_city;
		char *m_district;
};

Student::Student(char *name, int age) : m_name(name), m_age(age) {}

void Student::show(Address *addr)
{
	cout << "姓名:" << m_name << "年龄:" << m_age << endl;
	cout << addr->m_province << "省" << addr->m_city << "市" << \
		addr->m_district << "区" << endl;
}

Address::Address(char *province, char *city, char *district) : \
		m_province(province), m_city(city), m_district(district){}

int main(void)
{	
	Student *pstu = new Student("小芳", 18);
	Address *addr = new Address("北京", "北京", "朝阳");
	pstu->show(addr);
	return 0;
}

