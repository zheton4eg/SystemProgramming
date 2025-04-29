#include<Windows.h>
#include<iostream>
#include<conio.h>
#include<thread>
using std::cin;
using std::cout;
using std::endl;
using namespace std::chrono_literals;

#define Enter		13
#define Escape		27

#define MIN_TANK_CAPACITY	 20
#define MAX_TANK_CAPACITY	120

class Tank
{
	double fuel_level;
public:
	const int CAPACITY;
	double get_fuel_level()const
	{
		return fuel_level;
	}
	Tank(int capacity) :CAPACITY
	(
		capacity < MIN_TANK_CAPACITY ? MIN_TANK_CAPACITY :
		capacity > MAX_TANK_CAPACITY ? MAX_TANK_CAPACITY :
		capacity
	),
		fuel_level(0)
	{
		cout << "Tank:";
		if (capacity < MIN_TANK_CAPACITY)cout << "Min capacity was applied" << endl;
		if (capacity > MAX_TANK_CAPACITY)cout << "Max capacity was applied" << endl;
		//this->CAPACITY = capacity;
		//this->fuel_level = 0;
		cout << "Tank is ready" << endl;
	}
	~Tank()
	{
		cout << "Tank is over" << endl;
		//My Darkest Days - Come undone
	}
	double fill(double amount)
	{
		if (amount < 0)return fuel_level;
		fuel_level += amount;
		if (fuel_level >= CAPACITY)
		{
			fuel_level = CAPACITY;
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
		cout << "Capacity:\t" << CAPACITY << " liters.\n";
		cout << "Fuel level:\t" << fuel_level << " liters.\n";
	}
};

#define MIN_ENGINE_CONSUMPTION		3
#define MAX_ENGINE_CONSUMPTION	   25

class Engine
{
	const double CONSUMPTION;	//������ �� 100 ��.
	const double DEFAULT_CONSUMPTION_PER_SECOND;
	
	double consumption_per_second;
	bool is_started;
public:
	const double CONSUMPTION_PER_SECOND_IN_0_GEAR;
	const double CONSUMPTION_PER_SECOND_IN_1_GEAR;
	const double CONSUMPTION_PER_SECOND_IN_2_GEAR;
	const double CONSUMPTION_PER_SECOND_IN_3_GEAR;
	const double CONSUMPTION_PER_SECOND_IN_4_GEAR;
	const double CONSUMPTION_PER_SECOND_IN_5_GEAR;
	double get_consumption_per_second()
	{
		return consumption_per_second;
	}
	double set_consumption_per_second(double new_consumption_per_second)
	{
		return  consumption_per_second = new_consumption_per_second;
	}
	
	Engine(double consumption) :
		CONSUMPTION
		(
			consumption < MIN_ENGINE_CONSUMPTION ? MIN_ENGINE_CONSUMPTION :
			consumption > MAX_ENGINE_CONSUMPTION ? MAX_ENGINE_CONSUMPTION :
			consumption
		),
		DEFAULT_CONSUMPTION_PER_SECOND(CONSUMPTION   * 3e-5),	//3*10^-5
		CONSUMPTION_PER_SECOND_IN_0_GEAR(CONSUMPTION * 3e-5),
		CONSUMPTION_PER_SECOND_IN_1_GEAR(CONSUMPTION * 2e-4),
		CONSUMPTION_PER_SECOND_IN_2_GEAR(CONSUMPTION * 14e-5),
		CONSUMPTION_PER_SECOND_IN_3_GEAR(CONSUMPTION * 2e-4),
		CONSUMPTION_PER_SECOND_IN_4_GEAR(CONSUMPTION * 25e-5),
		CONSUMPTION_PER_SECOND_IN_5_GEAR(CONSUMPTION * 3e-4),
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
		cout << "Consumption:          " << CONSUMPTION                      << " liters/100km\n";
		cout << "Default Consumption:  " << DEFAULT_CONSUMPTION_PER_SECOND   << " liters/s\n";
		cout << "Consumption 1 gear:   " << CONSUMPTION_PER_SECOND_IN_1_GEAR << " liters/s\n";
		cout << "Consumption 2 gear:   " << CONSUMPTION_PER_SECOND_IN_2_GEAR << " liters/s\n";
		cout << "Consumption 3 gear:   " << CONSUMPTION_PER_SECOND_IN_3_GEAR << " liters/s\n";
		cout << "Consumption 4 gear:   " << CONSUMPTION_PER_SECOND_IN_4_GEAR << " liters/s\n";
		cout << "Consumption 5 gear:   " << CONSUMPTION_PER_SECOND_IN_5_GEAR << " liters/s\n";
		cout << "Consumption gear:	   " << consumption_per_second           << " liters/s\n";
	}
};

#define MAX_SPEED_LOWER_LIMIT	130
#define MAX_SPEED_HIGHER_LIMIT	408

class Car
{
	Engine engine;
	Tank tank;
	int speed;
	int acceleration;	//���������
	const int MAX_SPEED;
	bool driver_inside;
	struct
	{
		std::thread panel_thread;
		std::thread engine_idle_thread;
		std::thread free_wheeling_thread;
		std::thread consumption_now_thread;
	}threads_container;	//��� ��������� �� ����� �����, � ��������� ������ ���� ���������.
public:
	Car(double consumption, int capacity, int max_speed = 250, int acceleration = 10) :
		MAX_SPEED
		(
			max_speed < MAX_SPEED_LOWER_LIMIT ? MAX_SPEED_LOWER_LIMIT :
			max_speed > MAX_SPEED_HIGHER_LIMIT ? MAX_SPEED_HIGHER_LIMIT :
			max_speed
		),
		engine(consumption),
		tank(capacity),
		speed(0),
		acceleration(acceleration)
	{
		

		driver_inside = false;
		cout << "Your car is ready to go, press 'Enter' to get in ;-)" << endl;

	}
	~Car()
	{
		cout << "The car is over" << endl;
	}
	void get_in()
	{
		driver_inside = true;
		threads_container.panel_thread = std::thread(&Car::panel, this);
		//panel();
	}
	void get_out()
	{
		driver_inside = false;
		if (threads_container.panel_thread.joinable())threads_container.panel_thread.join();
		system("CLS");
		cout << "You are out of the Car" << endl;
	}
	void start()
	{
		if (tank.get_fuel_level())
		{
			engine.start();
			threads_container.engine_idle_thread = std::thread(&Car::engine_idle, this);
		}
	}
	void stop()
	{
		engine.stop();
		if (threads_container.engine_idle_thread.joinable())
			threads_container.engine_idle_thread.join();
	}
	void accelerate()
	{
		if (driver_inside && engine.started())
		{
			speed += acceleration;
			if (!threads_container.free_wheeling_thread.joinable())
				threads_container.free_wheeling_thread = std::thread(&Car::free_wheeling, this);
			if (speed > MAX_SPEED)speed = MAX_SPEED;
			std::this_thread::sleep_for(1s);
		}
	}
	void slow_down()
	{
		if (driver_inside)
		{
			speed -= acceleration;
			if (speed < 0)speed = 0;
			std::this_thread::sleep_for(1s);
		}
	}
	void control()
	{
		char key = 0;
		do
		{
			key = 0;
			if (_kbhit())key = _getch();
			switch (key)
			{
			case Enter:
				driver_inside ? get_out() : get_in();
				break;
			case'F':case'f':
				double fuel;
				cout << "������� ����� �������: "; cin >> fuel;
				tank.fill(fuel);
				break;
			case 'I':case'i':	//Ignition
				if (driver_inside)!engine.started() ? start() : stop();
				break;
			case 'W':case 'w':
				accelerate();
				//consumption_now();
				if (!threads_container.consumption_now_thread.joinable())
					threads_container.consumption_now_thread = std::thread(&Car::consumption_now, this);
				break;
			case 'S':case's':
				slow_down();
				//consumption_now();
				if (!threads_container.consumption_now_thread.joinable())
					threads_container.consumption_now_thread = std::thread(&Car::consumption_now, this);
				break;
			case Escape:
				stop();
				get_out();
			}
			if (tank.get_fuel_level() <= 0)stop();
			if (speed <= 0 && threads_container.free_wheeling_thread.joinable())
				threads_container.free_wheeling_thread.join();
		} while (key != Escape);
		//Concurent execution (������������� ����������).
	}
	void free_wheeling()
	{
		while (--speed > 0)
		{
			if (speed < 0)speed = 0;
			std::this_thread::sleep_for(1s);
		}
	}
	void engine_idle()
	{
		while (engine.started() && tank.give_fuel(engine.get_consumption_per_second()))
		{
			std::this_thread::sleep_for(1s);
		}
	}
	void consumption_now()
	{
		while (engine.started())
		{
			if (speed <= 0)
				this->engine.set_consumption_per_second(engine.CONSUMPTION_PER_SECOND_IN_0_GEAR);
			else if (speed > 0 && speed < 61)
				this->engine.set_consumption_per_second(engine.CONSUMPTION_PER_SECOND_IN_1_GEAR);
			else if (speed > 60 && speed < 101)
				this->engine.set_consumption_per_second(engine.CONSUMPTION_PER_SECOND_IN_2_GEAR);
			else if (speed > 100 && speed < 141)
				this->engine.set_consumption_per_second(engine.CONSUMPTION_PER_SECOND_IN_3_GEAR);
			else if (speed > 140 && speed < 201)
				this->engine.set_consumption_per_second(engine.CONSUMPTION_PER_SECOND_IN_4_GEAR);
			else if (speed > 200 && speed < 250)
				this->engine.set_consumption_per_second(engine.CONSUMPTION_PER_SECOND_IN_5_GEAR);
			
		}		
	}
	void panel()
	{
		while (driver_inside)
		{
			system("CLS");
			cout << "Fuel level: " << tank.get_fuel_level() << " liters\n";
			if (tank.get_fuel_level() < 5)
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 0xCF);
				cout << " LOW FUEL ";
				SetConsoleTextAttribute(hConsole, 0x07);
			}
			cout << endl;
			cout << "Speed:\t" << speed << " km/h\n";
			cout << engine.get_consumption_per_second() << " liters/s\n";
			cout << "Engine is " << (engine.started() ? "started" : "stopped") << endl;
			
			Sleep(100);
		}
	}
	void info()const
	{
		engine.info();
		tank.info();
		cout << "Speed:   " << speed << " km/h\n";
		cout << "MaxSpeed:" << MAX_SPEED << " km/h\n";
	}
};

//#define TANK_CHECK
//#define ENGINE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef TANK_CHECK
	Tank tank(80);
	double fuel;
	do
	{
		cout << "�� ������� ������������? "; cin >> fuel;
		tank.fill(fuel);
		tank.info();
	} while (true);
#endif // TANK_CHECK

#ifdef ENGINE_CHECK
	Engine engine(10);
	engine.info();
#endif // ENGINE_CHECK

	Car car(20, 80, 270);
	car.info();
	car.control();
}
