#pragma once
#include "From_string.h"
#include "TestReflectFlag.h"
#include "stringUtils.h"

template<>
inline bool from_string(FlagTestBit& a_data, const std::string& a_value)
{
	if (iCompare(a_value, "First_bit"))
	{
		a_data = First_bit;
		return true;
	}
	if (iCompare(a_value, "Second_bit"))
	{
		a_data = Second_bit;
		return true;
	}
	if (iCompare(a_value, "Third_bit"))
	{
		a_data = Third_bit;
		return true;
	}
	if (iCompare(a_value, "Fourth_bit"))
	{
		a_data = Fourth_bit;
		return true;
	}
	return false;
}