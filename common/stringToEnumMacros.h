/***********************************************
* @headerfile stringToEnumMacros.h
* @date 27 / 04 / 2024
* @author Roomain
************************************************/
#pragma once
#include "stringUtils.h"


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