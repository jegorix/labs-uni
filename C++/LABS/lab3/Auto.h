#pragma once
#include "CargoCarrier.h"


class Auto : public CargoCarrier
{
protected:
	int load_capacity;

public:

	Auto() : CargoCarrier()
	{
		load_capacity = 0;
	}

	Auto(char* name) : CargoCarrier(name)
	{
		load_capacity = 2500;
	}

	Auto(Auto& other) : CargoCarrier(other)
	{
		load_capacity = other.load_capacity;
	}

	~Auto() {}


	int getLoadCapacity();

	void setLoadCapacity(int new_load_capacity);

	void showMenu() override;

	using CargoCarrier::operator =;
	Auto& operator = (const Auto& object);

	friend std::ostream& operator << (std::ostream& os, const Auto& object);
	friend std::istream& operator >> (std::istream& is, Auto& object);
};