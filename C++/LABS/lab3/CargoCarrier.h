#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>
#include <cstring>
#include <limits>
#include <cstdlib>	
#include <iomanip>

class CargoCarrier
{
protected:
	char name[32];
	int speed;
	int stake;

public:
	CargoCarrier()
	{
		name[0] = '\0';
		speed = 0;
		stake = 0;
	}

	CargoCarrier(char* name)
	{
		strcpy(this->name, name);
		speed = 150;
		stake = 100;
	}

	CargoCarrier(CargoCarrier& other)
	{
		strcpy(name, other.name);
		speed = other.speed;
		stake = other.stake;
	}

	~CargoCarrier() {}


	char* getName();
	int getSpeed();
	int getStake();

	void setName(char* new_name);
	void setSpeed(int new_speed);
	void setStake(int new_stake);

	double calculatePrice(int distance);
	double calculateTime(int distance);
	virtual void showMenu();

	CargoCarrier& operator = (const CargoCarrier& object);
	friend std::ostream& operator << (std::ostream& os, const CargoCarrier& object);
	friend std::istream& operator >> (std::istream& is, CargoCarrier& object);
};