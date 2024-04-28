/***********************************************
* @headerfile stringToEnumMacros.h
* @date 27 / 04 / 2024
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


#define BEGIN_STRING_TO_ENUM(Type) \
[[nodiscard]] constexpr bool string_to_enum(const std::string& a_value, Type& a_enum) \
{ \

#define STRING_TO_ENUM(value) \
    if(iCompare(a_value, #value)) \
    { \
        a_enum = value; \
        return true; \
    } \


#define END_STRING_TO_ENUM \
    return false; \
} \

template<typename T>
class FlagInput
{};

#define BEGIN_STRING_TO_FLAG(BaseType, TypeFlag) \
template<> \
class FlagInput<BaseType>\
{\
public: \
    static [[nodiscard]] inline bool string_to_flag(const std::string& a_value, TypeFlag& a_enum) \
    { \
        std::vector<std::string> splitted; \
        split(a_value, '|', splitted); \
        size_t foundCount = 0; \
        for(const auto& enumerate : splitted) \
        { \

#define STRING_TO_FLAG(value) \
            if(iCompare(a_value, #value)) \
            { \
                a_enum |= value; \
                foundCount++; \
            } \

#define END_STRING_TO_FLAG \
        }\
        return foundCount == splitted.size(); \
    } \
};