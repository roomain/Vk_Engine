#pragma once
/***********************************************
* @headerfile FromStrings.h
* @date 26 / 04 / 2024
* @author Roomain
************************************************/
#include <string>

template<typename Type>
bool from_string(Type& a_data, const std::string& a_value) { return false; }


template<>
inline bool from_string(int& a_data, const std::string& a_value)
{
	try
	{
		a_data = std::atoi(a_value.c_str());
		return true;
	}
	catch (...)
	{
		return false;
	}
}

template<>
inline bool from_string(float& a_data, const std::string& a_value)
{
	try
	{
		a_data = static_cast<float>(std::atof(a_value.c_str()));
		return true;
	}
	catch (...)
	{
		return false;
	}
}

template<>
inline bool from_string(double& a_data, const std::string& a_value)
{
	try
	{
		a_data = std::atof(a_value.c_str());
		return true;
	}
	catch (...)
	{
		return false;
	}
}

template<>
inline bool from_string(std::string& a_data, const std::string& a_value)
{
	a_data = a_value;
	return true;
}