#pragma once
/***********************************************
* @headerfile RHILoadingUtility.h
* @date 11 / 04 / 2024
* @author Roomain
************************************************/
#include <string>
#include <type_traits>
#include <vector>
#include <list>

bool from_string(const std::string& a_strValue, int& a_value);
bool from_string(const std::string& a_strValue, unsigned int& a_value);
bool from_string(const std::string& a_strValue, float& a_value);
bool from_string(const std::string& a_strValue, double& a_value);
bool from_string(const std::string& a_strValue, std::string& a_value);



template<typename Type> requires std::is_enum_v<Type>
bool from_string(const std::string& a_strValue, Type& a_value)
{
	//todo
}
