//
// Created by jegorix on 6.09.25.
//

#ifndef LAB1_PRINT_H
#define LAB1_PRINT_H

#include <iostream>
#include <sstream>
#include <string_view>
#include <type_traits>

namespace py {
    void print() {
        std::cout << std::endl;
    }


    template<typename... Args>
    void print_helper(std::ostringstream stream, std::string_view sep, const Args&... args)
    {
        ((stream << args << sep), ...);
        std::string content = stream.str();

        if(!content.empty() && !sep.empty())
        {
            content.erase(content.size() - sep.size()); // удаляем послед символ
            stream.str(content);
        }

    }


    template<typename... Args>
    void print_impl(const std::string_view &sep, const std::string_view &end, const Args &... args)
    {
        std::ostringstream stream;
        print_helper(stream, sep, args...);
        std::cout << stream.str() << end;
    }

    template<typename... Args>
    void print(const Args &... args)
    {
        print_impl(" ", "\n", args...);
    }

    template<typename... Args>
    void print(const std::string_view &sep, const Args &... args)
    {
        print_impl(sep, "\n", args...);
    }

    template<typename... Args>
    void print(const std::string_view &sep, const std::string_view &end, const Args &... args)
    {
        print_impl(sep, end, args...);
    }
}
#endif //LAB1_PRINT_H
