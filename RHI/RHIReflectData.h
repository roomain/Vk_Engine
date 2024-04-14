#pragma once
/***********************************************
* @headerfile RHIReflectData.h
* @date 13 / 04 / 2024
* @author Roomain
************************************************/
#include <vector>
#include <list>
#include <array>
#include <memory>
#include "not_copiable.h"
#include "RHIType_traits.h"
#include "RHIReflectiveClassSet.h"
#include "boost/property_tree/ptree.hpp"
#include "RHI_globals.h"

#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)

/*@brief represents a class content from json*/
class RHI_EXPORT RHIReflectData
{
private:
	boost::property_tree::ptree m_JsonContent;					/*!< Json class content*/
	boost::property_tree::ptree* m_TempJsonContent = nullptr;	/*!< Temporary json class content (used for member with class type)*/
	static RHIReflectiveClassSetPtr m_reflectiveClasses;	/*!< link to reflective classes*/

	template<typename Type> requires (!Is_reflective_v<Type>)
	static bool basic_memberValue(const boost::property_tree::ptree& a_tree, Type& a_value) noexcept
	{
		try
		{
			a_value = a_tree.get_value<Type>();
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool getMemberJson(const std::string& a_memberName, boost::property_tree::ptree& a_tree)const;

public:
	NOT_COPIABLE(RHIReflectData)
	explicit RHIReflectData(boost::property_tree::ptree&& a_JsonContent)noexcept : m_JsonContent{ a_JsonContent } {}
	explicit RHIReflectData(const boost::property_tree::ptree& a_JsonContent) : m_JsonContent{ a_JsonContent } {}
	~RHIReflectData() = default;

	static void setReflectiveClassSet(const RHIReflectiveClassSetPtr& a_classSet);

	template<typename Type>
	bool memberValue(const std::string& a_memberName, std::vector<Type>& a_value)const noexcept
	{
		boost::property_tree::ptree memberJson;
		if (getMemberJson(a_memberName, memberJson))
		{
			if constexpr (Is_reflective_v<Type> && Has_reflectName_v<Type>)
			{
				if (m_reflectiveClasses)
				{
					if (const auto iter = m_reflectiveClasses->find(Type::reflectName());
						iter != m_reflectiveClasses->cend())
					{
						for (const auto& [name, prop] : memberJson)
						{
							iter->second->m_TempJsonContent = &prop;
							a_value.emplace_back<Type>();
							iter->second->m_TempJsonContent = nullptr;
						}
						return true;
					}
				}
			}
			else
			{
				for (const auto& [name, prop] : memberJson)
				{	
					Type basic;
					if(RHIReflectData::basic_memberValue(prop, basic))
						a_value.emplace_back(basic);
				}
				return true;
			}
		}
		return false;
	}

	template<typename Type>
	bool memberValue(const std::string& a_memberName, std::list<Type>& a_value)const noexcept
	{
		boost::property_tree::ptree memberJson;
		if (getMemberJson(a_memberName, memberJson))
		{
			if constexpr (Is_reflective_v<Type> && Has_reflectName_v<Type>)
			{
				if (m_reflectiveClasses)
				{
					if (const auto iter = m_reflectiveClasses->find(Type::reflectName());
						iter != m_reflectiveClasses->cend())
					{
						for (const auto& [name, prop] : memberJson)
						{
							iter->second->m_TempJsonContent = &prop;
							a_value.emplace_back<Type>();
							iter->second->m_TempJsonContent = nullptr;
						}
						return true;
					}
				}
			}
			else
			{
				for (const auto& [name, prop] : memberJson)
				{
					Type basic;
					if (RHIReflectData::basic_memberValue(prop, basic))
						a_value.emplace_back(basic);
				}
				return true;
			}
		}
		return false;
	}

	template<typename Type, size_t Size>
	bool memberValue(const std::string& a_memberName, std::array<Type, Size>& a_value)const noexcept
	{
		boost::property_tree::ptree memberJson;
		if (getMemberJson(a_memberName, memberJson))
		{
			if constexpr (Is_reflective_v<Type> && Has_reflectName_v<Type>)
			{
				if (m_reflectiveClasses)
				{
					if (const auto iter = m_reflectiveClasses->find(Type::reflectName());
						iter != m_reflectiveClasses->cend())
					{
						size_t index  = 0;
						for (const auto& [name, prop] : memberJson)
						{
							if (index == Size)
								break;
							iter->second->m_TempJsonContent = &prop;
							a_value[index] = Type{};
							iter->second->m_TempJsonContent = nullptr;
							index++;
						}
						return true;
					}
				}
			}
			else
			{
				size_t index = 0;
				for (const auto& [name, prop] : memberJson)
				{
					if (index == Size)
						break;
					Type basic;
					if (RHIReflectData::basic_memberValue(prop, basic))
						a_value[index] = basic;
					index++;
				}
				return true;
			}
		}
		return false;
	}


	template<typename Type>
	bool memberValue(const std::string& a_memberName, Type& a_value)const noexcept
	{
		boost::property_tree::ptree memberJson;
		if (getMemberJson(a_memberName, memberJson))
		{
			if constexpr (Is_reflective_v<Type> && Has_reflectName_v<Type>)
			{
				if (m_reflectiveClasses)
				{
					if (const auto iter = m_reflectiveClasses->find(Type::reflectName());
						iter != m_reflectiveClasses->cend())
					{
						iter->second->m_TempJsonContent = &memberJson;
						Type::init_reflect(a_value);
						iter->second->m_TempJsonContent = nullptr;
						return true;
					}
				}
			}
			else
			{
				return RHIReflectData::basic_memberValue(memberJson, a_value);
			}
		}
		return false;
	}


};
#pragma warning(pop)