#pragma once
#include "OneWayQueue.h"
#include "TextFile.h"
#include "BinaryFile.h"
#include "com_fun.h"
#include <algorithm>
#include <iomanip>
#include <map>
#include <vector>

template<typename T>
bool matchTransport(const CargoCarrier& search_object, const T& object)
{
	return (search_object.getName() == "0" || search_object.getName() == object.getName()) &&
		(search_object.getSpeed() == 0 || search_object.getSpeed() == object.getSpeed()) &&
		(search_object.getStake() == 0 || search_object.getStake() == object.getStake());
}

template<typename T>
int nextMapKey(const std::multimap<int, T>& container)
{
	return container.empty() ? 0 : container.rbegin()->first + 1;
}


template <typename T>
void findObjects(OneWayQueue<T>& queue)																		// функция поиска объекта 
{
	std::cout << "\n Введите поля по которым осуществлять поиск" << std::endl;


	CargoCarrier search_object;
	std::cin >> search_object;
	system("cls");																							// очистка экрана
	try
	{
		if (queue.empty())
		{
			throw OneWayQueueException(200, "очередь пуста");
		}
		else if (search_object.getName() == "0" && search_object.getSpeed() == 0 && search_object.getStake() == 0)
		{
			throw OneWayQueueException(201, "нет критериев поиска");
		}


		OneWayQueue<T> search_result(queue.find(search_object));						// возвращение очереди с найденными объектами


		if (search_result.empty())																		// проверка найдены ли элементы
		{
			throw OneWayQueueException(202, "элементы не найдены");
		}
		search_result.display();																			// вывод очереди на экран
	}
	catch (OneWayQueueException& e)
	{
		std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
	}

}


template<typename T>
bool compareTransportName(const Unit<T>* buffer, const Unit<T>* buffer_next)
{
	return buffer->object.getName() > buffer->next->object.getName();
}


template<typename T>
bool compareTransportSpeed(const Unit<T>* buffer, const Unit<T>* buffer_next)
{
	return buffer->object.getSpeed() > buffer->next->object.getSpeed();
}


template<typename T>
bool compareTransportStake(const Unit<T>* buffer, const Unit<T>* buffer_next)
{
	return buffer->object.getStake() > buffer->next->object.getStake();
}

template<typename T>
bool compareTransportNameValue(const T& lhs, const T& rhs)
{
	return lhs.getName() < rhs.getName();
}


template<typename T>
bool compareTransportSpeedValue(const T& lhs, const T& rhs)
{
	return lhs.getSpeed() < rhs.getSpeed();
}


template<typename T>
bool compareTransportStakeValue(const T& lhs, const T& rhs)
{
	return lhs.getStake() < rhs.getStake();
}


template<typename T>
void sortQueue(OneWayQueue<T>& queue)																		// функция выбора типа сортировки
{
	int choice = 0;

	try
	{
		showSortMenu();
		choice = readInt(std::cin, " Ваш выбор: ");															// выбор сортировки
		system("cls");																						// очистка экрана

		switch (choice)
		{
		case 0:	break;																					// завершение программы
		case 1: queue.sort(compareTransportName<T>);	break;															// сортировка по названию
		case 2: queue.sort(compareTransportSpeed<T>); break;															// сортировка по скорости
		case 3: queue.sort(compareTransportStake<T>); break;															// сортировка по ставке
		default: throw InputException(114, "выбрана несуществующая функция"); break;
		}
	}
	catch (const InputException& e)
	{
		std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
	}
	catch (const FileException& e)
	{
		std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
	}
}



template<typename T>
const std::string getTextFileName()
{
	if (typeid(T) == typeid(Airplane)) return "file_airplane.txt";
	else if (typeid(T) == typeid(Auto)) return "file_auto.txt";
	else return "file_train.txt";
}


template<typename T>
const std::string getBinaryFileName()
{
	if (typeid(T) == typeid(Airplane)) return "file_airplane.bin";
	else if (typeid(T) == typeid(Auto)) return "file_auto.bin";
	else return "file_train.bin";
}


template<typename T>
void read_from_text_file(OneWayQueue<T>& queue)
{
	TextFile<T> tf(getTextFileName<T>());
	tf.openForRead();

	while (!tf.eof())
	{
		try
		{
			T new_object = tf.read();
			queue.addUnit(new_object);
		}
		catch (const FileException& e)
		{

			if (e.getCode() == 305) break;
			else
			{
				std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
			}
		}
	}
}


template<typename T>
void write_to_text_file(OneWayQueue<T>& queue)
{
	TextFile<T> tf(getTextFileName<T>());

	tf.openForWrite();


	for (auto it = queue.begin(); it != queue.end(); ++it)
	{
		try
		{
			tf.write(*it);
		}
		catch (const FileException& e)
		{
			std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
		}
	}
}


template<typename T>
void read_from_binary_file(OneWayQueue<T>& queue)
{
	BinaryFile<T> bf(getBinaryFileName<T>());
	bf.openForRead();

	while (!bf.eof())
	{
		try
		{
			T new_object = bf.read();
			queue.addUnit(new_object);  // добавляем в очередь
		}
		catch (const FileException& e)
		{
			if (e.getCode() == 315) break;
			else
			{
				std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
			}
		}
	}
}


template<typename T>
void write_to_binary_file(OneWayQueue<T>& queue)
{
	BinaryFile<T> bf(getBinaryFileName<T>());
	bf.openForWrite();

	for (auto it = queue.begin(); it != queue.end(); ++it)
	{
		try
		{
			bf.write(*it);
		}
		catch (const FileException& e)
		{
			std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
		}
	}
}




template<typename T>
void read_from_file(OneWayQueue<T>& queue)
{
	std::cout << " Выберите тип файла для чтения:" << std::endl;
	std::cout << " 1 — Текстовый" << std::endl;
	std::cout << " 2 — Бинарный" << std::endl;


	int choice;
	choice = readInt(std::cin, " Ваш выбор: ");
	system("cls");
	try
	{
		if (choice == 1)
		{
			read_from_text_file(queue);
		}
		else if (choice == 2)
		{
			read_from_binary_file(queue);
		}
		else
		{
			throw InputException(115, "выбран несуществующий файл");
		}
	}
	catch (const InputException& e)
	{
		std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
	}
	catch (const FileException& e)
	{
		std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
	}
}



template<typename T>
void write_to_file(OneWayQueue<T>& queue)
{
	std::cout << " Выберите тип файла для записи:" << std::endl;
	std::cout << " 1 — Текстовый" << std::endl;
	std::cout << " 2 — Бинарный" << std::endl;


	int choice;
	choice = readInt(std::cin, " Ваш выбор: ");
	system("cls");
	try
	{
		if (choice == 1)
		{
			write_to_text_file(queue);
		}
		else if (choice == 2)
		{
			write_to_binary_file(queue);
		}
		else
		{
			throw InputException(115, "выбран несуществующий файл");
		}
	}
	catch (const InputException& e)
	{
		std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
	}
	catch (const FileException& e)
	{
		std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
	}
}


template<typename T>
void displayMultimap(const std::multimap<int, T>& container)
{
	try
	{
		if (container.empty())
		{
			throw OneWayQueueException(200, "контейнер пуст");
		}

		container.begin()->second.printHead();

		std::cout << " " << std::setfill('=') << std::setw(80) << "=" << std::setfill(' ') << std::endl;
		for (const auto& [index, value] : container)
		{
			std::cout << value;
		}
		std::cout << " " << std::setfill('=') << std::setw(80) << "=" << std::setfill(' ') << std::endl;
	}
	catch (const OneWayQueueException& e)
	{
		std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
	}
}


template <typename T>
void findObjectsMap(std::multimap<int, T>& container)															// функция поиска объекта 
{
	std::cout << "\n Введите поля по которым осуществлять поиск" << std::endl;


	CargoCarrier search_object;
	std::cin >> search_object;
	system("cls");																							// очистка экрана
	try
	{
		if (container.empty())
		{
			throw OneWayQueueException(200, "контейнер пуст");
		}
		else if (search_object.getName() == "0" && search_object.getSpeed() == 0 && search_object.getStake() == 0)
		{
			throw OneWayQueueException(201, "нет критериев поиска");
		}


		std::multimap<int, T> search_result;						// возвращение очереди с найденными объектами
		int key = 0;


		for (const auto& [index, value] : container)
		{
			if (matchTransport(search_object, value))
			{
				search_result.emplace(key++, value);														// добавление элемента в новую очередь
			}
		}


		if (search_result.empty())																		// проверка найдены ли элементы
		{
			throw OneWayQueueException(202, "элементы не найдены");
		}
		displayMultimap(search_result);																			// вывод очереди на экран
	}
	catch (OneWayQueueException& e)
	{
		std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
	}

}


template<typename T, typename Comparator>
void sortMultimapBy(std::multimap<int, T>& container, int& nextKey, Comparator comp)
{
	if (container.size() < 2)
	{
		throw OneWayQueueException(202, "недостаточно элементов для сортировки");
	}

	std::vector<T> values;
	values.reserve(container.size());

	for (const auto& [index, value] : container)
	{
		values.push_back(value);
	}

	std::stable_sort(values.begin(), values.end(), comp);

	container.clear();
	nextKey = 0;
	for (const auto& value : values)
	{
		container.emplace(nextKey++, value);
	}
}


template<typename T>
void sortMultimap(std::multimap<int, T>& container, int& nextKey)																		// функция выбора типа сортировки
{
	int choice = 0;

	try
	{
		showSortMenu();
		choice = readInt(std::cin, " Ваш выбор: ");															// выбор сортировки
		system("cls");																						// очистка экрана

		switch (choice)
		{
		case 0:	break;																					// завершение программы
		case 1: sortMultimapBy(container, nextKey, compareTransportNameValue<T>); std::cout << " Контейнер multimap отсортирован!\n"; break;															// сортировка по названию
		case 2: sortMultimapBy(container, nextKey, compareTransportSpeedValue<T>); std::cout << " Контейнер multimap отсортирован!\n"; break;															// сортировка по скорости
		case 3: sortMultimapBy(container, nextKey, compareTransportStakeValue<T>); std::cout << " Контейнер multimap отсортирован!\n"; break;															// сортировка по ставке
		default: throw InputException(114, "выбрана несуществующая функция"); break;
		}
	}
	catch (const InputException& e)
	{
		std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
	}
	catch (const OneWayQueueException& e)
	{
		std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
	}
}


template<typename T>
void read_from_text_file(std::multimap<int, T>& container, int& nextKey)
{
	TextFile<T> tf(getTextFileName<T>());
	tf.openForRead();

	while (!tf.eof())
	{
		try
		{
			T new_object = tf.read();
			container.emplace(nextKey++, new_object);
		}
		catch (const FileException& e)
		{

			if (e.getCode() == 305) break;
			else
			{
				std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
			}
		}
	}
}


template<typename T>
void write_to_text_file(const std::multimap<int, T>& container)
{
	TextFile<T> tf(getTextFileName<T>());

	tf.openForWrite();


	for (const auto& [index, value] : container)
	{
		try
		{
			tf.write(value);
		}
		catch (const FileException& e)
		{
			std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
		}
	}
}


template<typename T>
void read_from_binary_file(std::multimap<int, T>& container, int& nextKey)
{
	BinaryFile<T> bf(getBinaryFileName<T>());
	bf.openForRead();

	while (!bf.eof())
	{
		try
		{
			T new_object = bf.read();
			container.emplace(nextKey++, new_object);  // добавляем в очередь
		}
		catch (const FileException& e)
		{
			if (e.getCode() == 315) break;
			else
			{
				std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
			}
		}
	}
}


template<typename T>
void write_to_binary_file(const std::multimap<int, T>& container)
{
	BinaryFile<T> bf(getBinaryFileName<T>());
	bf.openForWrite();

	for (const auto& [index, value] : container)
	{
		try
		{
			bf.write(value);
		}
		catch (const FileException& e)
		{
			std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
		}
	}
}


template<typename T>
void read_from_file(std::multimap<int, T>& container, int& nextKey)
{
	std::cout << " Выберите тип файла для чтения:" << std::endl;
	std::cout << " 1 — Текстовый" << std::endl;
	std::cout << " 2 — Бинарный" << std::endl;


	int choice;
	choice = readInt(std::cin, " Ваш выбор: ");
	system("cls");
	try
	{
		if (choice == 1)
		{
			read_from_text_file(container, nextKey);
		}
		else if (choice == 2)
		{
			read_from_binary_file(container, nextKey);
		}
		else
		{
			throw InputException(115, "выбран несуществующий файл");
		}
	}
	catch (const InputException& e)
	{
		std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
	}
	catch (const FileException& e)
	{
		std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
	}
}



template<typename T>
void write_to_file(const std::multimap<int, T>& container)
{
	std::cout << " Выберите тип файла для записи:" << std::endl;
	std::cout << " 1 — Текстовый" << std::endl;
	std::cout << " 2 — Бинарный" << std::endl;


	int choice;
	choice = readInt(std::cin, " Ваш выбор: ");
	system("cls");
	try
	{
		if (choice == 1)
		{
			write_to_text_file(container);
		}
		else if (choice == 2)
		{
			write_to_binary_file(container);
		}
		else
		{
			throw InputException(115, "выбран несуществующий файл");
		}
	}
	catch (const InputException& e)
	{
		std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
	}
}


template<typename T>
void chooseFun()																								// функция работы с очередью
{
	OneWayQueue<T> queue;

	while (1)
	{
		T buffer;
		int choice = 0;

		try
		{
			showMenu();
			choice = readInt(std::cin, " Ваш выбор: ");															// выбор функции
			system("cls");																						// очистка экрана

			switch (choice)
			{
			case 0:
				exit(0);																						// завершение программы
				break;

			case 1:
				queue.display();																				// вывод таблицы на экран
				break;

			case 2:
				std::cout << " Введите новый элемент очереди:" << std::endl;									// ввод нового элемента							
				std::cin >> buffer;
				system("cls");
				queue.addUnit(buffer);																			// добавление элемента в очередь
				break;

			case 3:
				queue.delUnit();																				// удаление элемента 
				break;

			case 4:
				sortQueue(queue);																				// вызов функция для сортировки
				break;

			case 5:
				findObjects(queue);																				// вызов функция для поиска
				break;

			case 6:
				read_from_file(queue);																			// вызов функция для поиска
				break;

			case 7:
				write_to_file(queue);																			// вызов функция для поиска
				break;

			default:
				throw InputException(114, "выбрана несуществующая функция");
				break;
			}
		}
		catch (const InputException& e)
		{
			std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
		}
	}
}

template<typename T>
void chooseFunMap()																								// функция работы с multimap
{
	std::multimap<int, T> container;
	int nextKey = 0;

	while (1)
	{
		T buffer;
		int choice = 0;

		try
		{
			showMenu();
			choice = readInt(std::cin, " Ваш выбор: ");															// выбор функции
			system("cls");																						// очистка экрана

			switch (choice)
			{
			case 0:
				exit(0);																						// завершение программы
				break;

			case 1:
				displayMultimap(container);																		// вывод таблицы на экран
				break;

			case 2:
				std::cout << " Введите новый элемент очереди:" << std::endl;									// ввод нового элемента							
				std::cin >> buffer;
				system("cls");
				container.emplace(nextKey++, buffer);															// добавление элемента в контейнер
				break;

			case 3:
				try
				{
					if (container.empty())
					{
						throw OneWayQueueException(200, "контейнер пуст");
					}

					container.erase(container.begin());															// удаление элемента 
					nextKey = nextMapKey(container);
				}
				catch (const OneWayQueueException& e)
				{
					std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
				}
				break;

			case 4:
				sortMultimap(container, nextKey);																// вызов функция для сортировки
				break;

			case 5:
				findObjectsMap(container);																		// вызов функция для поиска
				break;

			case 6:
				read_from_file(container, nextKey);																// вызов функция для поиска
				nextKey = nextMapKey(container);
				break;

			case 7:
				write_to_file(container);																		// вызов функция для поиска
				break;

			default:
				throw InputException(114, "выбрана несуществующая функция");
				break;
			}
		}
		catch (const InputException& e)
		{
			std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
		}
	}
}


template<typename T>
void chooseContainer()
{
	while (1)
	{
		try
		{
			showMenuContainer();
			int container_choice = readInt(std::cin, " Ваш выбор: ");											// выбор контейнера
			system("cls");

			switch (container_choice)
			{
			case 0: return;
			case 1: chooseFun<T>(); break;
			case 2: chooseFunMap<T>(); break;
			default: throw InputException(116, "выбран несуществующий контейнер"); break;
			}
		}
		catch (const InputException& e)
		{
			std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
		}
	}
}

void chooseQueueType()																						// функция для выбора типа очереди
{
	int choice = 0;

	while (1)
	{
		try
		{
			showMenuClass();
			choice = readInt(std::cin, " Ваш выбор: ");																// выбор класса для очереди
			system("cls");

			switch (choice)
			{
			case 0: exit(0);
			case 1: chooseContainer<Airplane>(); break;
			case 2: chooseContainer<Auto>(); break;
			case 3: chooseContainer<Train>(); break;
			default: throw InputException(115, "выбран несуществующий класс"); break;
			}
		}
		catch (const InputException& e)
		{
			std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << std::endl;
		}
	}
}
