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

    template<typename... Args>
    void print_helper(std::ostringstream& stream, std::string_view sep, const Args&... args)
    {
        using std::operator<<; // при переопределении этого метода например при выводе объекта юзер класса
        // чтоб принт знал как его выводить (кастомный объект)

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

    // FORMAT implementation
namespace detail
{
    template<typename T, typename... Args>
    void print_arg(std::ostringstream &result, size_t target_index,
                   size_t &current_index, const T &first, const Args &... args) {
        if (current_index == target_index) {
            result << first;
            return;
        }
        current_index++;

        if constexpr (sizeof...(args) > 0) print_arg(result, target_index, current_index, args...);
    }

    template<typename... Args>
    std::string format(std::string_view fmt, const Args &... args) {
        std::ostringstream result;
        size_t arg_index = 0;
        const size_t total_args = sizeof...(args);

        for (size_t i = 0; i < fmt.size(); i++) {
            if (i + 1 < fmt.size() && fmt[i] == '{' && fmt[i + 1] == '}') {
                if (arg_index >= total_args) {
                    throw std::runtime_error("Not enough arguments for format string");
                }

                size_t current_index = 0;
                print_arg(result, arg_index, current_index, args...);
                arg_index++;
                i++;
            } else {
                result << fmt[i];
            }
        }

        if (arg_index != total_args) {
            throw std::runtime_error("Too many arguments for format string");
        }
        return result.str();
    }

}
    template<typename... Args>
    void printf(std::string_view fmt, const Args&... args)
    {
        std::cout << detail::format(fmt, args...);
    }


}
#endif //LAB1_PRINT_H
