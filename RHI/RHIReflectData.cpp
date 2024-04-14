#include "pch.h"
#include "RHIReflectData.h"


RHIReflectiveClassSetPtr RHIReflectData::m_reflectiveClasses;

bool RHIReflectData::getMemberJson(const std::string& a_memberName, boost::property_tree::ptree& a_tree)const
{
	if (m_TempJsonContent)
	{
		auto iter = m_TempJsonContent->find(a_memberName);
		if (iter != m_TempJsonContent->not_found())
		{
			a_tree = iter->second;
			return true;
		}
	}
	else
	{
		auto iter = m_JsonContent.find(a_memberName);
		if (iter != m_JsonContent.not_found())
		{
			a_tree = iter->second;
			return true;
		}
	}
	return false;
}

void RHIReflectData::setReflectiveClassSet(const RHIReflectiveClassSetPtr& a_classSet)
{
	RHIReflectData::m_reflectiveClasses = a_classSet;
}