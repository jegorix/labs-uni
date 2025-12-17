//template<typename T>
//Unit<T>* OneWayQueue<T>::getFront()
//{
//	return front;
//}
//
//template<typename T>
//Unit<T>* OneWayQueue<T>::getBack()
//{
//	return back;
//}
//
//
//
//template<typename T>
//void OneWayQueue<T>::addUnit(const T& object)																// метод дл€ добавлени€ объекта в очередь
//{
//	Unit<T>* new_unit = new Unit<T>(object);																// создание узла
//	if (!front)																								// проверка на существование очереди
//	{
//		front = new_unit;																					// создание очереди если ее нет
//		back = front;
//	}
//	else
//	{
//		back->next = new_unit;																				// добавление объекта в конец 
//		back = new_unit;																					// переопределение конца очереди
//	}
//}
//
//
//
//template<typename T>
//void OneWayQueue<T>::delUnit()																				// метод дл€ удалени€ объекта из очереди
//{
//	try																										// проверка на существование очереди
//	{
//		if (!front)
//		{
//			throw OneWayQueueException(200, "очередь пуста");
//		}
//
//		Unit<T>* buffer = front;																			// создание буфера
//		front = front->next;																				// замещение первого объекта в очереди
//
//		if (front == nullptr)																				// проверка закончилась ли очередь 
//		{
//			back = nullptr;
//		}
//
//		delete buffer;																						// удаление элемента
//	}
//	catch (const OneWayQueueException& e)
//	{
//		std::cout << " ќшибка " << e.getCode() << ": " << e.getMessage() << std::endl;						// вывод ошибки на экран
//	}
//}
//
//
//
//template<typename T>
//void OneWayQueue<T>::display() const																		// метод дл€ вывода всей очереди
//{
//	try
//	{
//		if (!front)
//		{
//			throw OneWayQueueException(200, "очередь пуста");
//		}
//
//		Unit<T>* buffer = front;																			// объ€вление буфера 
//		buffer->object.printHead();																			// отрисовка головы
//
//		std::cout << " " << std::setfill('=') << std::setw(80) << "=" << std::setfill(' ') << std::endl;
//		while (buffer != nullptr)
//		{
//			std::cout << buffer->object;
//			buffer = buffer->next;																			// переход к следующему элементу
//		}
//		std::cout << " " << std::setfill('=') << std::setw(80) << "=" << std::setfill(' ') << std::endl;	// отрисовка нижней границы
//	}
//	catch (const OneWayQueueException& e)
//	{
//		std::cout << " ќшибка " << e.getCode() << ": " << e.getMessage() << std::endl;						// вывод ошибки на экран
//	}
//}
//
//
//
//template<typename T>
//bool OneWayQueue<T>::match(CargoCarrier search_object, T object) const
//{
//	return (search_object.getName() == "0" || search_object.getName() == object) &&							// условие дл€ проверки элемента 
//		(search_object.getSpeed() == 0 || search_object.getSpeed() == object) &&
//		(search_object.getStake() == 0 || search_object.getStake() == object);
//}
//
//
//
//template<typename T>
//OneWayQueue<T> OneWayQueue<T>::find(CargoCarrier search_object)												// метод поиска в очереди
//{
//	OneWayQueue<T> result_search;																			// объ€влени€ очереди дл€ подход€щих объектов
//	try
//	{
//		Unit<T>* buffer = front;
//
//		while (buffer)																						// проход по всем элементам очереди
//		{
//			if (match(search_object, buffer->object))
//			{
//				result_search.addUnit(buffer->object);														// добавление элемента в новую очередь
//			}
//			buffer = buffer->next;
//		}
//	}
//	catch (const OneWayQueueException& e)
//	{
//		std::cout << " ќшибка " << e.getCode() << ": " << e.getMessage() << std::endl;						// вывод ошибки на экран
//	}
//
//	return result_search;
//}
//
//
//template<typename T>
//void OneWayQueue<T>::sort(bool (*compareTransport)(const  Unit<T>*, const  Unit<T>*))						// метод сортировки в очереди
//{
//	try
//	{
//		if (!front || !front->next)
//		{
//			throw OneWayQueueException(202, "недостаточно элементов дл€ сортировки");
//		}
//
//		bool swapped;
//
//		do
//		{
//			swapped = false;
//			Unit<T>* buffer = front;
//
//			while (buffer->next)																			// проход по всем элементам
//			{
//				if (compareTransport(buffer, buffer->next))
//				{
//					std::swap(buffer->object, buffer->next->object);										// свап элементов
//					swapped = true;
//				}
//
//				buffer = buffer->next;
//			}
//
//		} while (swapped);
//
//		std::cout << " ќчередь отсортирована!\n";
//	}
//	catch (const OneWayQueueException& e)
//	{
//		std::cout << " ќшибка " << e.getCode() << ": " << e.getMessage() << std::endl;						// вывод ошибки на экран
//	}
//}