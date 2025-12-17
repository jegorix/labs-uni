#include "Airplane.h"


int Airplane::getMaxAltitude() const																									// гетер
{
	return max_altitude;
}


void Airplane::setMaxAltitude(const int new_max_altitude)																				// сетер
{
	max_altitude = new_max_altitude;
}


Airplane& Airplane::operator = (const Airplane& object)																					// перегрузка оператора присваивания
{
	CargoCarrier::operator = (object);																									// вызов перегрузки из базового класса
	max_altitude = object.max_altitude;
	return *this;
}


std::ostream& operator << (std::ostream& os, const Airplane& object)																	// перегрузка оператора вывода 
{
	os << static_cast<const CargoCarrier&>(object);																						// преобразования типа для вызова перегрузки из базового класса
	os << std::left << std::setw(17) << object.max_altitude << "|" << std::endl;													// вывод высоты полета на экран
	return os;
}


std::istream& operator >> (std::istream& is, Airplane& object)																			// перегрузка оператора ввода 
{
	is >> static_cast<CargoCarrier&>(object);																							// преобразования типа для вызова перегрузки из базового класса
	object.max_altitude = readPosNum(is, " Введите макс. высоту полета(км): ", 0);															// ввод высоты полета

	return is;
}

std::ofstream& operator << (std::ofstream& ofs, const Airplane& object)																	// перегрузка оператора вывода 
{
	ofs << static_cast<const CargoCarrier&>(object);																						// преобразования типа для вызова перегрузки из базового класса
	ofs << ' ' << object.max_altitude << std::endl;													// вывод высоты полета на экран
	return ofs;
}


std::ifstream& operator >> (std::ifstream& ifs, Airplane& object)																			// перегрузка оператора ввода 
{
	ifs >> static_cast<CargoCarrier&>(object);																							// преобразования типа для вызова перегрузки из базового класса
	ifs >> object.max_altitude;													// ввод высоты полета
	return ifs;
}



std::fstream& operator << (std::fstream& out, const Airplane& object)
{
	out << static_cast<const CargoCarrier&>(object);
	out.write(reinterpret_cast<const char*>(&object.max_altitude), sizeof(object.max_altitude));

	if (!out.good())
	{
		throw FileException(314, " ошибка записи бинарных данных");
	}

	return out;
}



std::fstream& operator >> (std::fstream& in, Airplane& object)
{
	in >> static_cast<CargoCarrier&>(object);
	in.read(reinterpret_cast<char*>(&object.max_altitude), sizeof(object.max_altitude));

	if (!in.good() && !in.eof())
	{
		throw FileException(319, " ошибка чтения бинарных данных");
	}

	return in;
}


void Airplane::printHead() const																									// функция для отрисовки таблицы с данными объектов 
{
	CargoCarrier::printHead();

	std::cout << "| " << std::left << std::setw(17) << "Высота полета" << "|" << std::endl;

}