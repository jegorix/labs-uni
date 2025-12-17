#pragma once
#include "CargoCarrier.h"


class Auto : public CargoCarrier
{
protected:
	int load_capacity = 0;

public:

	Auto() : CargoCarrier() {}																				// конструктор по умолчанию

	Auto(char* name, int speed, int stake, int load_capacity) : CargoCarrier(name, speed, stake)			// конструктор с параметрами
	{
		this->load_capacity = load_capacity;
	}

	Auto(const Auto& other) : CargoCarrier(other)																	// конструктор копирования
	{
		load_capacity = other.load_capacity;
	}

	~Auto() {}																								// деструктор


	int getLoadCapacity() const;																			// гетер

	void setLoadCapacity(const int new_load_capacity);														// сетер

	void printHead() const override;


	Auto& operator = (const Auto& object);																	// перегрузка оператора присваивания
	friend std::ostream& operator << (std::ostream& os, const Auto& object);								// перегрузка оператора вывода
	friend std::istream& operator >> (std::istream& is, Auto& object);										// перегрузка оператора ввода 
	friend std::ofstream& operator << (std::ofstream& osf, const Auto& object);
	friend std::ifstream& operator >> (std::ifstream& isf, Auto& object);
	friend std::fstream& operator << (std::fstream& out, const Auto& obj);
	friend std::fstream& operator >> (std::fstream& in, Auto& obj);
};