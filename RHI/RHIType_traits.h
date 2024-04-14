#pragma once
/***********************************************
* @headerfile RHIType_traits.h
* @date 13 / 04 / 2024
* @author Roomain
************************************************/

/*type traits has_init_reflect*/
template<typename Type>
struct Is_reflective
{
private:
	using TrueType = char;
	using FalseType = short;

	// template used for compile time evaluation
	template<typename C>
	static constexpr TrueType& has_reflect(decltype(&C::init_reflect));

	template<typename C>
	static constexpr FalseType& has_reflect(...);

public:
	enum { value = sizeof(has_reflect<Type>(0)) == sizeof(Is_reflective<Type>::TrueType) };
};

template<typename Type>
constexpr auto Is_reflective_v = Is_reflective<Type>::value;

template<typename Type>
struct Has_reflectName
{
private:
	using TrueType = char;
	using FalseType = short;

	// template used for compile time evaluation
	template<typename C>
	static constexpr TrueType& has_name(decltype(&C::reflectName));

	template<typename C>
	static constexpr FalseType& has_name(...);

public:
	enum { value = sizeof(has_name<Type>(0)) == sizeof(Has_reflectName<Type>::TrueType) };
};

template<typename Type>
constexpr auto Has_reflectName_v = Has_reflectName<Type>::value;
