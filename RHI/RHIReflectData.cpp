#include "pch.h"
#include "RHIReflectData.h"
#include "RHIReflectData_intern.h"


//----------------------------------------------------------

RHIReflectiveClassSetPtr RHIReflectData::m_reflectiveClasses;

bool RHIReflectData::setTempTreeNode(const RHIReflectDataPtr& a_reflecData, const std::string& a_memberName)const
{
	if (auto iterValue = m_internData->m_localJsonContent.find(a_memberName); iterValue != m_internData->m_localJsonContent.not_found())
	{
		a_reflecData->m_internData->m_extenJsonContent = &iterValue->second;
		return true;
	}
	return false;
}

void RHIReflectData::releaseTempTreeNode(const RHIReflectDataPtr& a_reflecData)
{
	a_reflecData->m_internData->m_extenJsonContent = nullptr;
}

bool RHIReflectData::memberValuesInternal(const RHIReflectDataPtr& a_reflecData, const std::string& a_memberName, const LoadInstance& a_callback)const
{
	if (m_internData->m_extenJsonContent)
	{
		if (auto iterValue = m_internData->m_extenJsonContent->find(a_memberName); iterValue != m_internData->m_extenJsonContent->not_found())
		{
			for (auto& [name, prop] : iterValue->second)
			{
				a_reflecData->m_internData->m_extenJsonContent = &prop;
				a_callback();
				a_reflecData->m_internData->m_extenJsonContent = nullptr;
			}
			return true;
		}
	}
	else
	{
		if (auto iterValue = m_internData->m_localJsonContent.find(a_memberName); iterValue != m_internData->m_localJsonContent.not_found())
		{
			for (auto& [name, prop] : iterValue->second)
			{
				a_reflecData->m_internData->m_extenJsonContent = &prop;
				a_callback();
				a_reflecData->m_internData->m_extenJsonContent = nullptr;
			}
			return true;
		}
	}
	return false;
}

bool RHIReflectData::memberValuesInternal(const std::string& a_memberName, const GetValueFromString& a_callback)const
{
	if (m_internData->m_extenJsonContent)
	{
		if (auto iterValue = m_internData->m_extenJsonContent->find(a_memberName); iterValue != m_internData->m_extenJsonContent->not_found())
		{
			for (const auto& [name, prop] : iterValue->second)
			{
				if (!a_callback(prop.data()))
					return false;
			}
			return true;
		}
	}
	else
	{
		if (auto iterValue = m_internData->m_localJsonContent.find(a_memberName); iterValue != m_internData->m_localJsonContent.not_found())
		{
			for (const auto& [name, prop] : iterValue->second)
			{
				if (!a_callback(prop.data()))
					return false;
			}
			return true;
		}
	}
	return false;
}

bool RHIReflectData::memberValueInternal(const std::string& a_memberName, std::string& a_value)const
{
	if (m_internData->m_extenJsonContent)
	{
		if (auto iterValue = m_internData->m_extenJsonContent->find(a_memberName); iterValue != m_internData->m_extenJsonContent->not_found())
		{
			a_value = iterValue->second.data();
			return true;
		}
	}
	else
	{
		if (auto iterValue = m_internData->m_localJsonContent.find(a_memberName); iterValue != m_internData->m_localJsonContent.not_found())
		{
			a_value = iterValue->second.data();
			return true;
		}
	}

	return false;
}

RHIReflectData::RHIReflectData(std::shared_ptr<RHIReflectData_intern> a_JsonContent) noexcept:
	m_internData{ a_JsonContent }
{
}

void RHIReflectData::setReflectiveClassSet(const RHIReflectiveClassSetPtr& a_classSet)
{
	RHIReflectData::m_reflectiveClasses = a_classSet;
}