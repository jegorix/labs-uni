#include <iomanip>

template<typename T>
Unit<T>* OneWayQueue<T>::getFront()
{
	return front;
}

template<typename T>
Unit<T>* OneWayQueue<T>::getBack()
{
	return back;
}



template<typename T>
void OneWayQueue<T>::addUnit(const T& object)																// метод для добавления объекта в очередь
{
	Unit<T>* new_unit = new Unit<T>(object);																// создание узла
	if (!front)																								// проверка на существование очереди
	{
		front = new_unit;																					// создание очереди если ее нет
		back = front;
	}
	else
	{
		back->next = new_unit;																				// добавление объекта в конец 
		back = new_unit;																					// переопределение конца очереди
	}
}



template<typename T>
void OneWayQueue<T>::delUnit()																				// метод для удаления объекта из очереди
{
	try																										// проверка на существование очереди
	{
		if (!front)
		{
			throw OneWayQueueException(200, "очередь пуста");
		}

		Unit<T>* buffer = front;																			// создание буфера
		front = front->next;																				// замещение первого объекта в очереди

		if (front == nullptr)																				// проверка закончилась ли очередь 
		{
			back = nullptr;
		}

		delete buffer;																						// удаление элемента
	}
	catch (const OneWayQueueException& e)
	{
		std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;						// вывод ошибки на экран
	}
}



template<typename T>
void OneWayQueue<T>::display() const																		// метод для вывода всей очереди
{
	try
	{
		if (!front)
		{
			throw OneWayQueueException(200, "очередь пуста");
		}

		// Используем итератор для вывода
		auto it = const_cast<OneWayQueue<T>*>(this)->begin();

		it->printHead();																			// отрисовка головы

		std::cout << " " << std::setfill('=') << std::setw(80) << "=" << std::setfill(' ') << std::endl;

		for (; it != const_cast<OneWayQueue<T>*>(this)->end(); ++it)
		{
			std::cout << *it;
		}

		std::cout << " " << std::setfill('=') << std::setw(80) << "=" << std::setfill(' ') << std::endl;	// отрисовка нижней границы
	}
	catch (const OneWayQueueException& e)
	{
		std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;						// вывод ошибки на экран
	}
}



template<typename T>
bool OneWayQueue<T>::match(CargoCarrier search_object, T object) const
{
	return (search_object.getName() == "0" || search_object.getName() == object.getName()) &&							// условие для проверки элемента 
		(search_object.getSpeed() == 0 || search_object.getSpeed() == object.getSpeed()) &&
		(search_object.getStake() == 0 || search_object.getStake() == object.getStake());
}



template<typename T>
OneWayQueue<T> OneWayQueue<T>::find(CargoCarrier search_object)												// метод поиска в очереди
{
	OneWayQueue<T> result_search;																			// объявления очереди для подходящих объектов
	try
	{
		// Используем итератор для поиска
		for (auto it = begin(); it != end(); ++it)
		{
			if (match(search_object, *it))
			{
				result_search.addUnit(*it);														// добавление элемента в новую очередь
			}
		}
	}
	catch (const OneWayQueueException& e)
	{
		std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;						// вывод ошибки на экран
	}

	return result_search;
}


template<typename T>
void OneWayQueue<T>::sort(bool (*compareTransport)(const  Unit<T>*, const  Unit<T>*))						// метод сортировки в очереди
{
	try
	{
		if (!front || !front->next)
		{
			throw OneWayQueueException(202, "недостаточно элементов для сортировки");
		}

		bool swapped;

		do
		{
			swapped = false;
			Unit<T>* buffer = front;

			while (buffer->next)																			// проход по всем элементам
			{
				if (compareTransport(buffer, buffer->next))
				{
					std::swap(buffer->object, buffer->next->object);										// свап элементов
					swapped = true;
				}

				buffer = buffer->next;
			}

		} while (swapped);

		std::cout << " Очередь отсортирована!\n";
	}
	catch (const OneWayQueueException& e)
	{
		std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;						// вывод ошибки на экран
	}
}
