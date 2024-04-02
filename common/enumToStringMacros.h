/***********************************************
* @headerfile enumToStringMacros.h
* @date 21 / O3 / 2024
* @author Roomain
************************************************/
#pragma once

#include <string>

#define BEGIN_ENUM_TO_STRING(Type) \
static [[nodiscard]] constexpr std::string to_string(const Type a_value) \
{ \
    std::string strValue; \
    switch(a_value) \
    {

#define ENUM_TO_STRING(value) \
    case value: \
        strValue += #value; \
        break;


#define END_ENUM_TO_STRING \
    } \
    return strValue; \
}

/*use for enum enumerate
* BEGIN_ENUM_TO_STRING(enumerate)
* ENUM_TO_STRING(enumerate_value0)
* ENUM_TO_STRING(enumerate_value1)
* ENUM_TO_STRING(enumerate_valueN)
* END_ENUM_TO_STRING
*/