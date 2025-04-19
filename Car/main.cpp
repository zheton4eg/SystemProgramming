#include<iostream>
using namespace std;

#define MIN_TANK_CAPASITY 20
#define MAX_TANK_CAPASITY 120

class Tank
{
	
	double fuel_level;
public:

	 const int CAPASITY;
	 double get_fuel_level()const
	 {
		 return fuel_level;
	 }
	 Tank(int capasity):CAPASITY
	 (
		 capasity < MIN_TANK_CAPASITY ? MIN_TANK_CAPASITY :
		 capasity > MAX_TANK_CAPASITY ? MAX_TANK_CAPASITY :
		 capasity
	 ),
		 fuel_level(0)
	{
		 cout << "Tank:";
		 if(capasity < MIN_TANK_CAPASITY)cout<<"Min capacity was applied"<<endl;
		 if(capasity > MAX_TANK_CAPASITY)cout<<"Max capasity was applied"<<endl;
		//this->CAPASITY = capasity;
		//this->fuel_level=0;
		cout << "Tank is ready" << endl;
	}
	~Tank()
	{
		cout << "Tank is over" << endl;
	}

	double fill(double amount)
	{
		if (amount < 0)return fuel_level;
		fuel_level += amount;
		if (fuel_level >= CAPASITY)
		{
			fuel_level = CAPASITY;
			cout << "Full Tank" << endl;
		}
		return fuel_level;
	}
	double give_fuel(double amount)
	{
		fuel_level -= amount;
		if (fuel_level < 0)fuel_level = 0;
		return fuel_level;
	}
	void info()const
	{
		cout << "Capasity:\t" << CAPASITY << " liters.\n";
		cout << "Fuel level:\t" << fuel_level<< " liters.\n";
	}
};

void main()
{
	setlocale(LC_ALL, "RU");
	Tank tank(80);
	double fuel;
	do
	{
		cout << "На сколько заправляемся? ";cin>> fuel;
		tank.fill(fuel);
		tank.info();
	} while (true);
	tank.info();
}