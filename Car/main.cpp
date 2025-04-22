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
#define MIN_ENGINE_CONSUMPTION 3
#define MAX_ENGINE_CONSUMPTION 25
class Engine
{
	const double CONSUMPTION;	//расход на 100км
	const double DEFAULT_CONSUMPTION_PER_SECOND;
	double consumption_per_second;
	bool is_started;
public:
	double get_consumption_per_second()const
	{
		return consumption_per_second;
	}
	Engine(double consumption) :
		CONSUMPTION
		(
			consumption < MIN_ENGINE_CONSUMPTION ? MIN_ENGINE_CONSUMPTION :
			consumption > MAX_ENGINE_CONSUMPTION ? MAX_ENGINE_CONSUMPTION :
			consumption
		),
		DEFAULT_CONSUMPTION_PER_SECOND(CONSUMPTION * 3e-5),
		consumption_per_second(DEFAULT_CONSUMPTION_PER_SECOND)
	{
		cout << "Engine is ready" << endl;
	}
	~Engine()
	{
		cout << "Engine is over" << endl;
	}
	void start()
	{
		is_started = true;
	}
	void stop()
	{
		is_started = false;
	}
	bool started()const
	{
		return is_started;
	}
	void info()
	{
		cout<<"ConsumptionL "<< CONSUMPTION <<"liters/100km\n"<< endl;
		cout<<"Default Consumption "<< DEFAULT_CONSUMPTION_PER_SECOND <<"liters/s\n"<< endl;
		cout<<"Consumption "<< consumption_per_second <<"liters/s\n"<< endl;
	}
};
//#define TANK_CHECK
//#define ENGINE_CHECK

void main()
{
	setlocale(LC_ALL, "RU");
#ifdef TANK_CHEK
	Tank tank(80);
	double fuel;
	do
	{
		cout << "На сколько заправляемся? "; cin >> fuel;
		tank.fill(fuel);
		tank.info();
	} while (true);
	tank.info();
#endif // TANK_CHEK
#ifdef ENGINE_CHECK

	Engine engine(10);
	engine.info();

#endif // ENGINE_CHECK

}