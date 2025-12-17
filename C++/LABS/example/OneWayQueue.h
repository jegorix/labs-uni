#pragma once
#include "Airplane.h"
#include "Auto.h"
#include "Train.h" 
#include "OneWayQueueException.h" 
#include "Iterator.h"
#include <iostream>
#include <utility>


template<typename T>
struct Unit																											// объявление вложенной структуры узла очереди 								
{
	T object;
	Unit* next = nullptr;
	Unit(const T& object) : object(object) {}
};

template<typename T>
class OneWayQueue
{
public:
	using data_type = T;

private:
	Unit<T>* front = nullptr;																						// объявления указателя на начало очереди
	Unit<T>* back = nullptr;																						// объявления указателя на конец очереди

public:
	using iterator = Iterator<T>;

	OneWayQueue() {}																							// конструктор по умлочанию																	

	OneWayQueue(const T& object)																				// конструктор с параметрами
	{
		addUnit(object);
	}

	OneWayQueue(const OneWayQueue& other)																		// конструктор копирования
	{
		if (this != &other)
		{
			Unit<T>* buffer = other.front;																		// буферный указатель 

			while (buffer != nullptr)																			// цикл копирования всех объектов очереди
			{
				addUnit(buffer->object);
				buffer = buffer->next;
			}
		}
	}

	~OneWayQueue()																								// деструктор 
	{
		while (front)
		{
			delUnit();
		}
	}

	// Методы для итераторов
	

	Unit<T>* getFront();
	Unit<T>* getBack();
	void addUnit(const T& object);																				// метод для добавления объекта в очередь
	void delUnit();																								// метод для удаления объекта из очереди
	void display() const;																						// метод для вывода всей очереди
	bool match(CargoCarrier search_object, T object) const;														// метод сравнения объектов
	OneWayQueue<T> find(CargoCarrier search_object);															// метод поиска в очереди
	void sort(bool (*compareTransport)(const  Unit<T>*, const  Unit<T>*));										// метод сортировки в очереди
	iterator begin() { return iterator(this, front); }
	iterator end() { return iterator(this, nullptr); }

	// Методы для совместимости
	bool empty() const { return front == nullptr; }
	
};

#include "OneWayQueue.hpp"
