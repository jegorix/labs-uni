#pragma once

#include <iostream>
#include <cmath>
#include <cstring>
#include <limits>
#include <cstdlib>	
#include <iomanip>
#include <fstream>
#include "com_fun.h"
#include "FileException.h"	

class CargoCarrier
{
protected:
	std::string name = "";
	int speed = 0;
	double stake = 0;

public:
	CargoCarrier() {}																		// конструктор по умолчанию

	CargoCarrier(std::string name, int speed, double stake)									// конструктор с параметрами
	{
		this->name = name;
		this->speed = speed;
		this->stake = stake;
	}

	CargoCarrier(const CargoCarrier& other)													// конструктор копирования
	{
		name = other.name;
		speed = other.speed;
		stake = other.stake;
	}

	~CargoCarrier() {}																		// деструктор 


	std::string getName() const;															// гетеры
	int getSpeed() const;
	double getStake() const;

	void setName(std::string new_name);														// сетеры
	void setSpeed(const int new_speed);
	void setStake(const double new_stake);

	virtual void printHead() const;


	CargoCarrier& operator = (const CargoCarrier& object);									// перегрузка оператора присваивания
	bool operator == (const std::string& other_name) const;									// перегрузка оператора сравнения объекта c переменной типа стринг
	bool operator == (const int& other_speed) const;										// перегрузка оператора сравнения объекта c переменной типа инт
	bool operator == (const double& other_stake) const;										// перегрузка оператора сравнения объекта c переменной типа дабл
	friend bool operator == (const std::string& other_name, const CargoCarrier& object);	// перегрузка оператора сравнения переменной типа стринг с объектом
	friend bool operator == (const int& other_speed, const CargoCarrier& object);			// перегрузка оператора сравнения переменной типа инт с объектом
	friend bool operator == (const double& other_stake, const CargoCarrier& object);		// перегрузка оператора сравнения переменной типа дабл с объектом
	friend std::ostream& operator << (std::ostream& os, const CargoCarrier& object);		// перегрузка оператора вывода 
	friend std::istream& operator >> (std::istream& is, CargoCarrier& object);				// перегрузка оператора ввода 
	friend std::ofstream& operator << (std::ofstream& osf, const CargoCarrier& object);
	friend std::ifstream& operator >> (std::ifstream& isf, CargoCarrier& object);
	friend std::fstream& operator << (std::fstream& out, const CargoCarrier& object);
	friend std::fstream& operator >> (std::fstream& in, CargoCarrier& object);

};
