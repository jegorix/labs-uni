#pragma once
#include "CargoCarrier.h"


class Airplane : public CargoCarrier
{
protected:
	int max_altitude;

public:

	Airplane() : CargoCarrier()
	{
		max_altitude = 0;
	}

	Airplane(char* name) : CargoCarrier(name)
	{
		max_altitude = 10;
	}

	Airplane(Airplane& other) : CargoCarrier(other)
	{
		max_altitude = other.max_altitude;
	}

	~Airplane() {}


	int getMaxAltitude();

	void setMaxAltitude(int new_max_altitude);

	void showMenu() override;

	Airplane& operator = (const Airplane& object);
	friend std::ostream& operator << (std::ostream& os, const Airplane& object);
	friend std::istream& operator >> (std::istream& is, Airplane& object);
};