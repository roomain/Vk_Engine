/***********************************************
* @headerfile stringUtils.h
* @date 29 / 04 / 2024
* @author Roomain
************************************************/
#pragma once
#include <cctype>
#include <string>
#include <ranges>
#include <vector>

[[nodiscard]] inline  bool char_equals(const char a_first, const char a_second)
{
    return std::tolower(a_first) == std::tolower(a_second);
}

[[nodiscard]] constexpr  bool iCompare(const std::string& a_first, const std::string& a_second)
{
    return std::equal(a_first.cbegin(), a_first.cend(), 
    a_second.cbegin(), a_second.cend(), char_equals);
}

constexpr void split(const std::string& a_entry, const char a_separator, std::vector<std::string>& a_splitted)
{
    std::string temp = a_entry;
    while(!temp.empty())
    {
        if(auto iter = std::ranges::find(temp, a_separator); iter != temp.cend())
        {
            const size_t index = iter - temp.cbegin();
            a_splitted.emplace_back(temp.substr(0, iter - temp.cbegin()));
            temp = temp.substr(index + 1, temp.size() - index - 1);
        }
        else
        {
            a_splitted.emplace_back(temp);
            temp = "";
        }
    }
}