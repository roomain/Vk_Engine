#pragma once
/***********************************************
* @headerfile RHIReflectData_intern.h
* @date 26 / 04 / 2024
* @author Roomain
************************************************/
#include "boost/property_tree/ptree.hpp"

struct RHIReflectData_intern
{
	boost::property_tree::ptree m_localJsonContent;				/*!< Json local class content*/
	boost::property_tree::ptree* m_extenJsonContent = nullptr;	/*!< Temporary json class content (used for member with class type)*/
};
