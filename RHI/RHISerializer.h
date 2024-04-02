#pragma once

/***********************************************
* @headerfile RHISerializer.h
* @date 27 / 03 / 2024
* @author Roomain
************************************************/
#include "RHI_globals.h"
#include <string>
#include <utility>
#include <vector>

class RHI_EXPORT RHISerializer
{
protected:
	using MemberValue = std::pair<std::string, std::string>;
	std::string m_currentClass;			/*!< current serialized class name*/
	std::vector<MemberValue> m_members;	/*!< current class member and value*/

public:
	RHISerializer() = default;
	virtual ~RHISerializer() = default;
	virtual bool beginSerializer(const std::string& a_classname) = 0;
	template<typename Type>
	void serialize(const std::string& a_argname, const Type& a_value)
	{
		m_members.emplace_back(std::make_pair(a_argname, to_string(a_value));
	}
	virtual void endSerializer() = 0;
};