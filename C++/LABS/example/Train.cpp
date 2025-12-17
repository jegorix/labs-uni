#include "Train.h"



int Train::getWagonCount() const																						// гетер
{
	return wagon_count;
}


void Train::setWagonCount(const int new_wagon_count)																	// сетер
{
	wagon_count = new_wagon_count;
}


Train& Train::operator = (const Train& object)																			// перегрузка оператора присваивания
{
	CargoCarrier::operator = (object);																					// вызов перегрузки из базового класса
	wagon_count = object.wagon_count;
	return *this;
}


std::ostream& operator << (std::ostream& os, const Train& object)														// перегрузка оператора вывода 
{
	os << static_cast<const CargoCarrier&>(object);																		// преобразования типа для вызова перегрузки из базового класса
	os << std::left << std::setw(17) << object.wagon_count << "|" << std::endl;											// вывод количества вагонов на экран

	return os;
}


std::istream& operator >> (std::istream& is, Train& object)																// перегрузка оператора ввода
{
	is >> static_cast<CargoCarrier&>(object);																			// преобразования типа для вызова перегрузки из базового класса
	object.wagon_count = readPosNum(is, " Введите количество вагонов(шт): ", 0);												// ввод количества вагонов
	return is;
}


std::ofstream& operator << (std::ofstream& ofs, const Train& object)																	// перегрузка оператора вывода 
{
	ofs << static_cast<const CargoCarrier&>(object);																						// преобразования типа для вызова перегрузки из базового класса
	ofs << ' ' << object.wagon_count << std::endl;													// вывод высоты полета на экран
	return ofs;
}


std::ifstream& operator >> (std::ifstream& ifs, Train& object)																			// перегрузка оператора ввода 
{
	ifs >> static_cast<CargoCarrier&>(object);																							// преобразования типа для вызова перегрузки из базового класса
	ifs >> object.wagon_count;													// ввод высоты полета

	return ifs;
}


std::fstream& operator << (std::fstream& out, const Train& object)
{
	out << static_cast<const CargoCarrier&>(object);
	out.write(reinterpret_cast<const char*>(&object.wagon_count), sizeof(object.wagon_count));

	if (!out.good())
	{
		throw FileException(314, " ошибка записи бинарных данных");
	}

	return out;
}



std::fstream& operator >> (std::fstream& in, Train& object)
{
	in >> static_cast<CargoCarrier&>(object);
	in.read(reinterpret_cast<char*>(&object.wagon_count), sizeof(object.wagon_count));

	if (!in.good() && !in.eof())
	{
		throw FileException(319, " ошибка чтения бинарных данных");
	}

	return in;
}


void Train::printHead() const																							// функция для отрисовки таблицы с данными объектов 
{
	CargoCarrier::printHead();

	std::cout << "| " << std::left << std::setw(17) << "Кол-во вагонов" << "|" << std::endl;

}	