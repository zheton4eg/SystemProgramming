#include<Windows.h>
#include<iostream>
#include<conio.h>
#include<thread>

using std::cin;
using std::cout;
using std::endl;

#define MIN_TANK_CAPASITY 20
#define MAX_TANK_CAPASITY 120
#define MIN_SPEED 1
#define MAX_SPEED 220
class Tank
{
	friend class Engine;
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
class Engine
{
	
public:
	double speed;	//RPM
	double consuption_per_100km;
	
	Engine(double consuption_per_100km, double speed=0)
	{
		this->consuption_per_100km= consuption_per_100km;
		this->speed = speed < MIN_SPEED ? MIN_SPEED :
			speed>MAX_SPEED ? MAX_SPEED :
			speed;
	}
	void Drive(Tank &tank)
	{
		double resoult;
		
		 if (speed == 100)
		{
		    resoult = consuption_per_100km / 100;
			cout << "Вы потратите " << resoult << "л за час" << endl;
		}
		 else
		{
			double  The_liter_multiplier = 100 / speed;
			resoult = consuption_per_100km / The_liter_multiplier;
			cout << "Вы потратите " << resoult << "л за час" << endl;
		}
		double distance;
		cout << "Какое расстояние вы хотите проехать в км?"; cin >> distance;
		if (tank.fuel_level < (consuption_per_100km / 100) * distance)
		{
			cout << "Внимание, топлива не хватит, попробуйте снова!" << endl;
		}
		else
		{
			tank.fuel_level -= (consuption_per_100km / 100) * distance;
			cout << "Ваше время в пути составит " <<  distance/speed << " часов" << endl;
		}
	}
	~Engine()
	{
		cout << "Engine is over" << endl;
	}
	void Print()
	{
		cout << "Расход вашего авто на 100 км составляет " << consuption_per_100km <<"л" <<endl;
		cout << "Скорость вашего авто составляет " << speed <<" км/ч"<< endl;
	}
};
void main()
{
	setlocale(LC_ALL, "RU");
	Tank tank(80);
	double fuel;
	double fuel_consumption;
	double speed;
	do {
	cout << "Какой расход топлива на 100км? "; cin >> fuel_consumption;
	cout << "С какой скоростью поедем? "; cin >> speed;
	Engine engine(fuel_consumption,speed);
	engine.Print();
		cout << "На сколько заправляемся? "; cin >> fuel;
		tank.fill(fuel);
		tank.info();
		engine.Drive(tank);

		tank.info();
	} while (true);
}