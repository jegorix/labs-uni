#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

class ValidationException : public std::exception
{
    private:
        std::string message;
    
    public:
        explicit ValidationException(const std::string& msg) : message(msg) {};

        const char* what() const noexcept override
        {
            return message.c_str();
        }
};


class InvalidCharacterException : public ValidationException
{
    public:
        explicit InvalidCharacterException(char invalidChar)
            : ValidationException("Недопустимый символ: '" + std::string(1, invalidChar) + "'")
            {};

};


class EmptyInputException : public ValidationException
{
    public:
        EmptyInputException()
            : ValidationException("Введена пустая строка") {}
        
};


class TooLongStringException : public ValidationException
{
    public:
        TooLongStringException(size_t maxLength)
            : ValidationException("Строка слишком длинная. Максимум: " + 
                            std::to_string(maxLength) + " символов") {}
};


bool containsOnlyEnglishLetters(const std::string& str)
{
    for(char c: str)
    {
        if(!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
        {
            throw InvalidCharacterException(c);
        }
    }

    return true;
}

std::string validateEnglishInput(const std::string& input, size_t maxLength = 50)
{

    if(input.empty())
    {
        throw EmptyInputException();
    }

    if(input.length() > maxLength)
    {
        throw TooLongStringException(maxLength);
    }

    containsOnlyEnglishLetters(input);

    return input;

}



std::string getUserInput()
{
    std::string input;
    std::cout << "Введите текст (только английские буквы): ";
    std::getline(std::cin, input);

    try
    {
        return validateEnglishInput(input);
    }
    catch (const ValidationException& e)
    {
        std::cout << e.what() << std::endl;
        throw;
    }

}


void registerUser() {
    try {
        std::cout << "=== Регистрация пользователя ===\n";
        
        std::cout << "Введите имя: ";
        std::string name = getUserInput();
        
        std::cout << "Введите фамилию: ";
        std::string surname = getUserInput();
        
        std::cout << "\nРегистрация успешна!\n";
        std::cout << "Имя: " << name << "\n";
        std::cout << "Фамилия: " << surname << std::endl;
    }
    catch (const ValidationException& e) {
        std::cerr << "Ошибка валидации: " << e.what() << std::endl;
        std::cout << "Пожалуйста, попробуйте еще раз.\n" << std::endl;
        registerUser(); // Рекурсивный вызов для повторной попытки
    }
    catch (const std::exception& e) {
        std::cerr << "Неизвестная ошибка: " << e.what() << std::endl;
    }
}


int main()
{
    registerUser();
}