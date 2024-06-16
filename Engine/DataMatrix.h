#pragma once
/***********************************************
* @headerfile DataMatrix.h
* @date 16 / 06 / 2024
* @author Roomain
************************************************/
#include <vector>
#include <tuple>

/*@brief represents a data matrix*/
template<typename ...Types>
class DataMatrix : private std::tuple<std::vector<Types>...>
{
protected:
	template<typename Type>
	constexpr std::vector<Type>& row()
	{
		return std::get<std::vector<Type>>(*this);
	}

	template<typename Type>
	constexpr Type& cell(const size_t& a_index)
	{
		return row<Type>()[a_index];
	}

public:
    template<typename Type>
    constexpr std::vector<Type>::iterator begin()
    {
        return std::get<std::vector<Type>>(*this).begin();
    }

    template<typename Type>
    constexpr std::vector<Type>::iterator end()
    {
        return std::get<std::vector<Type>>(*this).end();
    }

    template<typename Type>
    constexpr std::vector<Type>::const_iterator cbegin()const
    {
        return std::get<std::vector<Type>>(*this).cbegin();
    }

    template<typename Type>
    constexpr std::vector<Type>::const_iterator cend()const
    {
        return std::get<std::vector<Type>>(*this).cend();
    }
};
