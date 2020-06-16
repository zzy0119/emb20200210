#include <iostream>

using namespace std;

// 军队
class Troops {
	public:
		virtual void fight () {cout << "troops fight" << endl;}
};

// 陆军
class Army:public Troops {
	public:
		void fight() {cout << "Army is fighting ..." << endl;}
};

// 坦克
class Tank:public Army {
	public:
		void fight() {cout << "Tank is figthing..." << endl;}
};

// 空军类
class AirForce:public Troops {
	public:
		void fight() {cout << "AirForce is figthing..." << endl;}
};

class Plane:public AirForce {
	public:
		void fight() {cout << "Plane is fighting...." << endl;}
};

int main(void)
{
	Troops *p = new Troops();
	p->fight();

	p = new Army();
	p->fight();

	p = new Tank();
	p->fight();

	return 0;
}
