#pragma once
#include "CargoCarrier.h"


class Train : public CargoCarrier
{
protected:
	int wagon_count = 0;

public:

	Train() : CargoCarrier() {}																								// конструктор по умолчанию

	Train(char* name, int speed, int stake, int wagon_count) : CargoCarrier(name, speed, stake)								// конструктор с параметрами
	{
		this->wagon_count = wagon_count;
	}

	Train(const Train& other) : CargoCarrier(other)																				// конструктор копирования
	{
		wagon_count = other.wagon_count;
	}

	~Train() {}																												// деструктор

	int getWagonCount() const;																									// гетер

	void setWagonCount(const int new_wagon_count);																				// сетер

	void printHead() const override;


	Train& operator = (const Train& object);																				// перегрузка оператора присваивания
	friend std::ostream& operator << (std::ostream& os, const Train& object);												// перегрузка оператора вывода 
	friend std::istream& operator >> (std::istream& is, Train& object);														// перегрузка оператора ввода
	friend std::ofstream& operator << (std::ofstream& osf, const Train& object);
	friend std::ifstream& operator >> (std::ifstream& isf, Train& object);
	friend std::fstream& operator << (std::fstream& out, const Train& obj);
	friend std::fstream& operator >> (std::fstream& in, Train& obj);
};
