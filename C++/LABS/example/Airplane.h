#pragma once
#include "CargoCarrier.h"


class Airplane : public CargoCarrier
{
protected:
	int max_altitude = 0;

public:

	Airplane() : CargoCarrier() {}																				// конструктор по умолчанию


	Airplane(char* name, int speed, int stake, int max_altitude) : CargoCarrier(name, speed, stake)				// конструктор с параметрами
	{
		this->max_altitude = max_altitude;
	}

	Airplane(const Airplane& other) : CargoCarrier(other)																// конструктор копирования
	{
		max_altitude = other.max_altitude;
	}

	~Airplane() {}																								// деструткор


	int getMaxAltitude() const;																						// гетер

	void setMaxAltitude(const int new_max_altitude);																	// сетер

	void printHead() const override;


	Airplane& operator = (const Airplane& object);																// перегрузка оператора присваивания
	friend std::ostream& operator << (std::ostream& os, const Airplane& object);								// перегрузка оператора вывода 
	friend std::istream& operator >> (std::istream& is, Airplane& object);										// перегрузка оператора ввода 
	friend std::ofstream& operator << (std::ofstream& ofs, const Airplane& object);
	friend std::ifstream& operator >> (std::ifstream& ifs, Airplane& object);
	friend std::fstream& operator << (std::fstream& out, const Airplane& object);
	friend std::fstream& operator >> (std::fstream& in, Airplane& object);
};