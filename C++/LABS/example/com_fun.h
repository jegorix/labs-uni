#pragma once
#include "InputException.h"
#include <iomanip>
#include <regex>

void showMenu();
void showMenuClass();
void showSortMenu();
void showMenuContainer();
std::string readString(std::istream& is, const std::string& massage_for_user);
std::string readRussianString(std::istream& is, const std::string& message_for_user);
int readInt(std::istream& is, const std::string& massage_for_user);
double readDouble(std::istream& is, const std::string& massage_for_user);
double readPosNum(std::istream& is, const std::string& massage_for_user, const int& type_flag);

