#include "CargoCarrier.h"


std::string CargoCarrier::getName() const																					// гетеры 
{
	return name;
}

int CargoCarrier::getSpeed() const
{
	return speed;
}

double CargoCarrier::getStake() const
{
	return stake;
}



void CargoCarrier::setName(std::string new_name)																			// сетеры
{
	name = new_name;
}

void CargoCarrier::setSpeed(const int new_speed)
{
	speed = new_speed;
}

void CargoCarrier::setStake(const double new_stake)
{
	stake = new_stake;
}


CargoCarrier& CargoCarrier::operator = (const CargoCarrier& other)															// перегрузка оператора присваивания
{
	if (this != &other)																										// условия чтобы не копировать тот же объект
	{
		name = other.name;																									// копирование объекта
		speed = other.speed;
		stake = other.stake;
	}
	return *this;
}


bool CargoCarrier::operator == (const std::string& other_name) const														// перегрузка оператора сравнения объекта c переменной типа стринг
{
	return name == other_name;
}


bool CargoCarrier::operator == (const int& other_speed) const																// перегрузка оператора сравнения объекта c переменной типа инт
{
	return speed == other_speed;
}


bool CargoCarrier::operator == (const double& other_stake) const															// перегрузка оператора сравнения объекта c переменной типа дабл
{
	return stake == other_stake;
}


bool operator == (const std::string& other_name, const CargoCarrier& object)												// перегрузка оператора сравнения переменной типа стринг с объектом
{
	return other_name == object.name;
}


bool operator == (const int& other_speed, const CargoCarrier& object)														// перегрузка оператора сравнения переменной типа инт с объектом
{
	return other_speed == object.speed;
}


bool operator == (const double& other_stake, const CargoCarrier& object)													// перегрузка оператора сравнения переменной типа дабл с объектом
{
	return other_stake == object.stake;
}


std::ostream& operator << (std::ostream& os, const CargoCarrier& object)													// перегрузка оператора вывод
{
	os << std::setfill(' ') << " | " << std::left << std::setw(18) << object.name;											// вывод названия на экран
	os << "| " << std::left << std::setw(18) << object.speed;																// вывод скорости на экран
	os << "| " << std::left << std::setw(18) << object.stake << "| ";														// вывод ставки		
	return os;
}


std::istream& operator >> (std::istream& is, CargoCarrier& object)															// перегрузка оператора ввода
{
	object.name = readRussianString(is, " Введите название(максимум 17 символов): ");																	// ввод названия
	object.speed = readPosNum(is, " Введите скорость(км/ч): ", 0);																// ввод скорости
	object.stake = readPosNum(is, " Введите ставку(руб/ч): ", 1);																// ввод ставки


	return is;
}


std::ifstream& operator >> (std::ifstream& isf, CargoCarrier& object)															// перегрузка оператора ввода
{
	isf >> object.name >> object.speed >> object.stake;															// ввод ставки

	return isf;
}


std::ofstream& operator << (std::ofstream& osf, const CargoCarrier& object)															// перегрузка оператора ввода
{
	osf << object.name << ' ' << object.speed << ' ' << object.stake;															// ввод ставки

	return osf;
}



std::fstream& operator << (std::fstream& out, const CargoCarrier& object)
{
	if (!out.is_open())
	{
		throw FileException(308, " файл не открыт для бинарной записи");
	}


	int len = static_cast<int>(object.name.size());
	out.write(reinterpret_cast<const char*>(&len), sizeof(len));
	if (!out.good())
	{
		throw FileException(310, " ошибка записи длины строки");
	}
	out.write(object.name.data(), len);
	if (!out.good())
	{
		throw FileException(311, " ошибка записи длины строки");
	}

	out.write(reinterpret_cast<const char*>(&object.speed), sizeof(object.speed));
	if (!out.good())
	{
		throw FileException(312, " ошибка записи длины строки");
	}

	out.write(reinterpret_cast<const char*>(&object.stake), sizeof(object.stake));
	if (!out.good())
	{
		throw FileException(313, " ошибка записи длины строки");
	}

	return out;
}



std::fstream& operator >> (std::fstream& in, CargoCarrier& object)
{
	int len;
	char* buffer;

	in.read(reinterpret_cast<char*>(&len), sizeof(len));
	if (!in.good())
	{
		throw FileException(315, " ошибка чтения строки из бинарного файла");
	}
	buffer = new char[len + 1];


	in.read(buffer, len);
	if (!in.good())
	{
		delete[] buffer;
		throw FileException(316, " ошибка чтения строки из бинарного файла");
	}
	buffer[len] = '\0';

	object.name = buffer;
	delete[] buffer;


	in.read(reinterpret_cast<char*>(&object.speed), sizeof(object.speed));
	if (!in.good())
	{
		throw FileException(317, " ошибка чтения строки из бинарного файла");
	}


	in.read(reinterpret_cast<char*>(&object.stake), sizeof(object.stake));
	if (!in.good())
	{
		throw FileException(318, " ошибка чтения строки из бинарного файла");
	}
	return in;
}


void CargoCarrier::printHead() const																						// функция для отрисовки таблицы с данными объектов 
{
	std::cout << " " << std::setfill('=') << std::setw(80) << "=" << std::setfill(' ') << std::endl;
	std::cout << " | " << std::left << std::setw(18) << "Название";
	std::cout << "| " << std::left << std::setw(18) << "Скорость";
	std::cout << "| " << std::left << std::setw(18) << "Ставка";
}

