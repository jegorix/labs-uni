#include "Auto.h"


int Auto::getLoadCapacity() const                                                              // гетер
{
	return load_capacity;
}


void Auto::setLoadCapacity(const int new_load_capacity)                                         // сетер
{
	load_capacity = new_load_capacity;
}


Auto& Auto::operator = (const Auto& object)                                                     // перегрузка оператора присваивания
{
	CargoCarrier::operator = (object);                                                          // вызов перегрузки из базового класса        
	load_capacity = object.load_capacity;
	return *this;
}


std::ostream& operator << (std::ostream& os, const Auto& object)                                // перегрузка оператора вывода
{
	os << static_cast<const CargoCarrier&>(object);                                             // преобразования типа для вызова перегрузки из базового класса
	os << std::left << std::setw(17) << object.load_capacity << "|" << std::endl;                // вывод грузоподъемности на экран

	return os;
}


std::istream& operator >> (std::istream& is, Auto& object)                                      // перегрузка оператора ввода
{
	is >> static_cast<CargoCarrier&>(object);                                                   // преобразования типа для вызова перегрузки из базового класса
	object.load_capacity = readPosNum(is, " Введите грузоподъёмность(кг): ", 0);				       // ввод грузоподъемности
	return is;
}


std::ofstream& operator << (std::ofstream& ofs, const Auto& object)																	// перегрузка оператора вывода 
{
	ofs << static_cast<const CargoCarrier&>(object);																						// преобразования типа для вызова перегрузки из базового класса
	ofs << ' ' << object.load_capacity << std::endl;													// вывод высоты полета на экран
	return ofs;
}


std::ifstream& operator >> (std::ifstream& ifs, Auto& object)																			// перегрузка оператора ввода 
{
	ifs >> static_cast<CargoCarrier&>(object);																							// преобразования типа для вызова перегрузки из базового класса
	ifs >> object.load_capacity;													// ввод высоты полета

	return ifs;
}



std::fstream& operator << (std::fstream& out, const Auto& object)
{
	out << static_cast<const CargoCarrier&>(object);
	out.write(reinterpret_cast<const char*>(&object.load_capacity), sizeof(object.load_capacity));

	if (!out.good())
	{
		throw FileException(314, " ошибка записи бинарных данных");
	}

	return out;
}



std::fstream& operator >> (std::fstream& in, Auto& object)
{
	in >> static_cast<CargoCarrier&>(object);
	in.read(reinterpret_cast<char*>(&object.load_capacity), sizeof(object.load_capacity));

	if (!in.good() && !in.eof())
	{
		throw FileException(319, " ошибка чтения бинарных данных");
	}

	return in;
}


void Auto::printHead() const																	// функция для отрисовки таблицы с данными объектов 
{
	CargoCarrier::printHead();

	std::cout << "| " << std::left << std::setw(17) << "Грузоподъемность" << "|" << std::endl;

}