#pragma once
#include "com_fun.h"

void showMenuClass()
{
	std::cout << "\n " << std::setfill('=') << std::setw(60) << "=" << std::endl;							// отрисовка заголовка меню
	std::cout << std::setfill(' ') << " |" << std::setw(20) << " " << "МЕНЮ ВЫБОРА КЛАССА" << std::setw(20) << " " << "|\n";
	std::cout << " " << std::setfill('=') << std::setw(60) << "=" << std::endl;


	std::cout << std::setfill(' ') << " |  1. Класс \"Airplane\"";											// отрисовка 1 пункта 
	std::cout << std::setw(37) << " " << "|\n";

	std::cout << std::setfill(' ') << " |  2. Класс \"Auto\"";												// отрисовка 2 пункта 
	std::cout << std::setw(41) << " " << "|\n";

	std::cout << std::setfill(' ') << " |  3. Класс \"Train\"";												// отрисовка 3 пункта 
	std::cout << std::setw(40) << " " << "|\n";

	std::cout << " |  0. Выход";                                                                            // отрисовка пункта выхода 
	std::cout << std::setw(48) << " " << "|\n";

	std::cout << " " << std::setfill('=') << std::setw(60) << "=" << "\n";									// отрисовка нижней границы меню
}


void showMenu()																								// метод для вывода меню очереди
{
	std::cout << "\n " << std::setfill('=') << std::setw(60) << "=" << std::endl;							// отрисовка заголовка меню
	std::cout << std::setfill(' ') << " |" << std::setw(23) << " " << "МЕНЮ ОЧЕРЕДИ" << std::setw(23) << " " << "|\n";
	std::cout << " " << std::setfill('=') << std::setw(60) << "=" << std::endl;


	std::cout << std::setfill(' ') << " |  1. Вывести всю очередь";											// отрисовка 1 пункта 
	std::cout << std::setw(34) << " " << "|\n";

	std::cout << " |  2. Добавить элемент";                                                                 // отрисовка 2 пункта 
	std::cout << std::setw(37) << " " << "|\n";

	std::cout << " |  3. Удалить элемент";																	// отрисовка 3 пункта 
	std::cout << std::setw(38) << " " << "|\n";

	std::cout << " |  4. Отсортировать очередь";															// отрисовка 4 пункта 
	std::cout << std::setw(32) << " " << "|\n";

	std::cout << " |  5. Найти элемент";																	// отрисовка 5 пункта 
	std::cout << std::setw(40) << " " << "|\n";

	std::cout << " |  6. Считать элементы из файла";														// отрисовка 6 пункта 
	std::cout << std::setw(28) << " " << "|\n";

	std::cout << " |  7. Перенести элементы в файл";														// отрисовка 7 пункта 
	std::cout << std::setw(28) << " " << "|\n";

	std::cout << " |  0. Выход";                                                                            // отрисовка пункта выхода 
	std::cout << std::setw(48) << " " << "|\n";

	std::cout << " " << std::setfill('=') << std::setw(60) << "=" << "\n";									// отрисовка нижней границы меню

}


void showSortMenu()																							// функция поиска объекта 
{
	std::cout << "\n " << std::setfill('=') << std::setw(60) << "=" << std::endl;							// отрисовка заголовка меню
	std::cout << std::setfill(' ') << " |" << std::setw(18) << " " << "МЕНЮ ВЫБОРА СОРТИРОВКИ" << std::setw(18) << " " << "|\n";
	std::cout << " " << std::setfill('=') << std::setw(60) << "=" << std::endl;


	std::cout << std::setfill(' ') << " |  1. Отсортировать по имени";										// отрисовка 1 пункта 
	std::cout << std::setw(31) << " " << "|\n";

	std::cout << std::setfill(' ') << " |  2. Отсортировать по скорости";									// отрисовка 2 пункта 
	std::cout << std::setw(28) << " " << "|\n";

	std::cout << std::setfill(' ') << " |  3. Отсортировать по ставке";										// отрисовка 3 пункта 
	std::cout << std::setw(30) << " " << "|\n";

	std::cout << " |  0. Назад";                                                                            // отрисовка пункта возвращения
	std::cout << std::setw(48) << " " << "|\n";

	std::cout << " " << std::setfill('=') << std::setw(60) << "=" << "\n";									// отрисовка нижней границы меню	
}


void showMenuContainer()
{
	std::cout << "\n " << std::setfill('=') << std::setw(60) << "=" << std::endl;							// отрисовка заголовка меню
	std::cout << std::setfill(' ') << " |" << std::setw(17) << " " << "ВЫБОР КОНТЕЙНЕРА" << std::setw(17) << " " << "|\n";
	std::cout << " " << std::setfill('=') << std::setw(60) << "=" << std::endl;


	std::cout << std::setfill(' ') << " |  1. Очередь OneWayQueue";											// отрисовка 1 пункта 
	std::cout << std::setw(31) << " " << "|\n";

	std::cout << std::setfill(' ') << " |  2. STL multimap";													// отрисовка 2 пункта 
	std::cout << std::setw(38) << " " << "|\n";

	std::cout << " |  0. Назад";                                                                            // отрисовка пункта возвращения
	std::cout << std::setw(48) << " " << "|\n";

	std::cout << " " << std::setfill('=') << std::setw(60) << "=" << "\n";									// отрисовка нижней границы меню	
}

std::string readString(std::istream& is, const std::string& massage_for_user)								// функция безопасного ввода строки
{
	while (1)
	{
		try
		{
			std::cout << massage_for_user;																	// вывод сообщения для пользователя 

			char symbol;
			std::string result;

			while (1)
			{
				int byte = is.get();																		// считка первого символа в виде байта 

				if (byte == EOF)																			// проверка конца ввода
				{
					throw InputException(101, "Неожиданный конец ввода");
				}

				symbol = byte;																				// перевод байта в символ

				if (symbol == '\n') break;																	// прекращение ввода при переводе на следующую строку

				result.push_back(symbol);																	// добавление символа в строку
			}

			if (result.empty())																				// проверка на пустую строку
			{
				throw InputException(100, "Пустая строка недопустима");
			}

			return result;
		}
		catch (const InputException& e)
		{
			std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << "\n Повторите ввод" << std::endl;
		}
	}
}



std::string readRussianString(std::istream& is, const std::string& message_for_user)						// функция безопасного ввода строки только на русском
{
	while (1)
	{
		try
		{
			std::string result = readString(is, message_for_user);											// стандартная считка строки

			if (result.length() > 17)
			{
				throw InputException(103, "название слишком длинное");
			}

			static const std::regex pattern(u8"^[А-Яа-яЁё0-9 \\-]+$");										// допустимые символы: А-Я, а-я, Ё, ё, пробел, дефис, цифры
			if (!std::regex_match(result, pattern))
			{
				throw InputException(102, "строка содержит не только русские буквы");
			}

			return result;
		}
		catch (const InputException& e)
		{
			std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << "\n Повторите ввод" << std::endl;
		}
	}
}



int readInt(std::istream& is, const std::string& massage_for_user)
{
	while (1)
	{
		try
		{
			std::cout << massage_for_user;

			int num;

			is >> num;
			if (is.fail())																			// Проверка на ошибку формата
			{
				is.clear(); // сброс ошибки
				is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				throw InputException(104, "ожидалось целое число");
			}


			if (is.peek() != '\n')
			{
				is.clear();
				is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				throw InputException(106, "лишние символы");
			}


			is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return num;
		}
		catch (const InputException& e)
		{
			std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << "\n Повторите ввод" << std::endl;
		}
	}
}


double readDouble(std::istream& is, const std::string& massage_for_user)
{
	while (1)
	{
		try
		{
			std::cout << massage_for_user;

			double num;

			is >> num;
			if (is.fail())																		// Проверка на ошибку формата
			{
				is.clear();
				is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				throw InputException(105, "ожидалось вещественное число");
			}


			if (is.peek() != '\n' && is.peek() != '.')
			{
				is.clear();
				is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				throw InputException(107, "лишние символы");
			}


			is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return num;
		}
		catch (const InputException& e)
		{
			std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << "\n Повторите ввод" << std::endl;
		}
	}
}




double readPosNum(std::istream& is, const std::string& massage_for_user, const int& type_flag)
{
	while (1)
	{
		try
		{
			double num = 0;

			if (type_flag == 0)
			{
				num = readInt(is, massage_for_user);
			}
			else if (type_flag == 1)
			{
				num = readDouble(is, massage_for_user);
			}

			if (num < 0)
			{
				throw InputException(108, "ожидалось положительное число");
			}

			return num;
		}
		catch (const InputException& e)
		{
			std::cout << " Ошибка " << e.getCode() << ": " << e.getMessage() << "\n Повторите ввод" << std::endl;
		}
	}
}
