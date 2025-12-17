#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <stdexcept>
#include "InputException.hpp"
#include "Date.hpp"

enum class Language {
    ENGLISH,
    RUSSIAN
};

template <typename T>
T safeInputNumeric(std::istream& is, T min, T max, const std::string& prompt = "") {
    T result;
    bool success = false;

    do {
        if (!prompt.empty()) {
            std::cout << prompt;
        }

        std::string input;
        if (!std::getline(is, input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input error. Try again.\n";
            continue;
        }

        try {
            if (input.empty()) {
                throw InputException(1, "Empty input. Please enter a number.");
            }

            std::istringstream iss(input);
            T temp;

            if (!(iss >> temp)) {
                throw InputException(2, "Invalid input. Expected a number, got: " + input);
            }

            char remaining;
            if (iss >> remaining) {
                throw InputException(3, "Invalid input. Number contains non-numeric characters: " + input);
            }

            if (temp < min || temp > max) {
                std::stringstream ss;
                ss << "Number out of range. Expected value between " << min << " and " << max << ", got: " << temp;
                throw InputException(4, ss.str());
            }

            result = temp;
            success = true;

        } catch (const InputException& e) {
            std::cout << e.what() << "\n";
            success = false;
        }

    } while (!success);

    return result;
}

std::string safeGetLine(std::istream& is, Language lang, const std::string& prompt = "");

Date safeInputDate(std::istream& is, const std::string& format = "", const std::string& prompt = "");

bool isEnglishOnly(const std::string& str);

bool isRussianOnly(const std::string& str);