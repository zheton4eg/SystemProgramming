#include<iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;

#define MIN_TANK_CAPASITY 20
#define MAX_TANK_CAPASITY 120
#define Escape 27
#define Enter  13

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
		is_started = false;
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
	void info()const
	{
		cout<<"ConsumptionL "<< CONSUMPTION <<"liters/100km\n"<< endl;
		cout<<"Default Consumption "<< DEFAULT_CONSUMPTION_PER_SECOND <<"liters/s\n"<< endl;
		cout<<"Consumption "<< consumption_per_second <<"liters/s\n"<< endl;
	}
};
#define MAX_SPEED_LOWER_LIMIT  130
#define MAX_SPEED_HIGHER_LIMIT 408
class Car
{
	Engine engine;
	Tank tank;
	const int MAX_SPEED;
	int speed;
	bool driver_inside;
public:
	Car(double consumption, int capacity, int max_speed = 250) :
		MAX_SPEED
		(
			max_speed < MAX_SPEED_LOWER_LIMIT ? MAX_SPEED_LOWER_LIMIT :
			max_speed > MAX_SPEED_HIGHER_LIMIT ? MAX_SPEED_HIGHER_LIMIT :
			max_speed
		),
		engine(consumption),
		tank(capacity),
		speed(0)
	{
		driver_inside = false;
		cout << "Your car is ready, press 'Enter' to get in ;-)"  << endl;
	}
	~Car()
	{
		cout << "The car is over" << endl;
	}
	void get_in()
	{
		driver_inside = true;
		panel();
	}
	void get_out()
	{
		driver_inside = false;
	}
	void control()
	{
		char key = 0;
		do 
		{
			key = _getch();
			switch (key)
			{
			case Enter:
				driver_inside ? get_out() : get_in();
				break;
			}
		} while (key != Escape);
	}
	void panel()
	{
		while (driver_inside)
		{
			system("CLS");
			cout << "Fuel level" << tank.get_fuel_level() << "liters\n";
			cout << "Engine is " << (engine.started() ? "started": "stoped") << endl;
			cout << "Speed:\t" << speed << "km/h\n";
			Sleep(100);

		}
	}
	void info()const
	{ 
		engine.info();
		tank.info();
		cout << "Speed: " << speed << "km/h\n";
		cout << "MaxSpeed: " << MAX_SPEED << "km/h\n";
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
	Car car(10, 50, 250);
	//car.info();
	car.control();
}