#pragma once
#include "CargoCarrier.h"


class Train : public CargoCarrier
{
protected:
	int wagon_count;

public:

	Train() : CargoCarrier()
	{
		wagon_count = 0;
	}

	Train(char* name) : CargoCarrier(name)
	{
		wagon_count = 20;
	}

	Train(Train& other) : CargoCarrier(other)
	{
		wagon_count = other.wagon_count;
	}

	~Train() {}

	int getWagonCount();

	void setWagonCount(int new_wagon_count);

	void showMenu() override;

	Train& operator = (const Train& object);

	friend std::ostream& operator << (std::ostream& os, const Train& object);
	friend std::istream& operator >> (std::istream& is, Train& object);
};