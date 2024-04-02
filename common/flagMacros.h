/***********************************************
* @headerfile flagMacros.h
* @date 21 / O3 / 2024
* @author Roomain
************************************************/
#pragma once

#define FLAG_OPERATOR(enumType) \
constexpr enumType operator | (const enumType a_first, const enumType a_second)\
{\
	return static_cast<enumType>(static_cast<unsigned int>(a_first) | static_cast<unsigned int>(a_second));\
}\
\
constexpr enumType operator & (const enumType a_first, const enumType a_second)\
{\
	return static_cast<enumType>(static_cast<unsigned int>(a_first) & static_cast<unsigned int>(a_second)); \
}\
\
constexpr enumType operator ~ (const enumType a_enum)\
{\
	return static_cast<enumType>(~static_cast<unsigned int>(a_enum)); \
}