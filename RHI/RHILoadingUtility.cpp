#include "pch.h"
#include "RHILoadingUtility.h"

bool from_string(const std::string& a_strValue, int& a_value)
{
	try
	{
		a_value = std::stoi(a_strValue);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool from_string(const std::string& a_strValue, unsigned int& a_value)
{
	try
	{
		a_value = std::stoi(a_strValue);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool from_string(const std::string& a_strValue, float& a_value)
{
	try
	{
		a_value = std::stof(a_strValue);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool from_string(const std::string& a_strValue, double& a_value)
{
	try
	{
		a_value = std::stod(a_strValue);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool from_string(const std::string& a_strValue, std::string& a_value)
{
	a_value = a_strValue;
	return true;
}