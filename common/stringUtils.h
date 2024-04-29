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

inline void trimLeft(std::string& a_toTrim)
{
    a_toTrim.erase(a_toTrim.begin(), std::find_if(a_toTrim.begin(), a_toTrim.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
}

inline void trimRight(std::string& a_toTrim)
{
    a_toTrim.erase(std::find_if(a_toTrim.rbegin(), a_toTrim.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), a_toTrim.end());
}

inline std::string trim(const std::string& a_toTrim)
{
    std::string temp = a_toTrim;
    trimLeft(temp);
    trimRight(temp);
    return temp;
}

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