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
#include <functional>
#include "not_copiable.h"
#include "RHIType_traits.h"
#include "RHIReflectiveClassSet.h"
#include "RHI_globals.h"
#include "From_string.h"
#include "stringUtils.h"

#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)



using GetValueFromString = std::function<bool(const std::string&)>;
using LoadInstance = std::function<void()>;

struct RHIReflectData_intern;



/*@brief represents a class content from json*/
class RHI_EXPORT RHIReflectData
{
private:
	std::shared_ptr<RHIReflectData_intern> m_internData;
	
	static RHIReflectiveClassSetPtr m_reflectiveClasses;	/*!< link to reflective classes*/

	bool memberValuesInternal(const RHIReflectDataPtr& a_reflecData, const std::string& a_memberName, const LoadInstance& a_callback)const;
	bool memberValuesInternal(const std::string& a_memberName, const GetValueFromString& a_callback)const;
	bool memberValueInternal(const std::string& a_memberName, std::string& a_value)const;
	bool setTempTreeNode(const RHIReflectDataPtr& a_reflecData, const std::string& a_memberName)const;
	bool flagValueInternal(const std::string& a_memberName, std::vector<std::string>& a_value)const;
	static void releaseTempTreeNode(const RHIReflectDataPtr& a_reflecData);

public:
	NOT_COPIABLE(RHIReflectData)
	explicit RHIReflectData(std::shared_ptr<RHIReflectData_intern> a_JsonContent)noexcept;
	~RHIReflectData() = default;

	static void setReflectiveClassSet(const RHIReflectiveClassSetPtr& a_classSet);

	template<typename Type>
	bool memberValue(const std::string& a_memberName, std::vector<Type>& a_value)const noexcept
	{
		if constexpr (Is_reflective_v<Type> && Has_reflectName_v<Type>)
		{
			// is complex type
			if (m_reflectiveClasses)
			{
				if (const auto iter = m_reflectiveClasses->find(Type::reflectName());
					iter != m_reflectiveClasses->cend())
				{
					return memberValuesInternal(iter->second, a_memberName, [&a_value]()
						{
							a_value.emplace_back<Type>(Type{});
						});
				}
				return false;
			}
		}
		else
		{
			// is simple type
			return memberValuesInternal(a_memberName, [&a_value](const std::string& a_strValue)
				{
					if (Type temp; from_string(temp, a_strValue))
					{
						a_value.emplace_back(std::move(temp));
						return true;
					}
					return false;
				});
		}
		return false;
	}

	template<typename Type>
	bool memberValue(const std::string& a_memberName, std::list<Type>& a_value)const noexcept
	{
		if constexpr (Is_reflective_v<Type> && Has_reflectName_v<Type>)
		{
			// is complex type
			if (m_reflectiveClasses)
			{
				if (const auto iter = m_reflectiveClasses->find(Type::reflectName());
					iter != m_reflectiveClasses->cend())
				{
					return memberValuesInternal(iter->second, a_memberName, [&a_value]()
						{
							a_value.emplace_back<Type>(Type{});
						});
				}
				return false;
			}
		}
		else
		{
			// is simple type
			return memberValuesInternal(a_memberName, [&a_value](const std::string& a_strValue)
				{
					if (Type temp; from_string(temp, a_strValue))
					{
						a_value.emplace_back(std::move(temp));
						return true;
					}
					return false;
				});
		}
		return false;
	}
		
	template<typename Type, size_t Size>
	bool memberValue(const std::string& a_memberName, std::array<Type, Size>& a_value)const noexcept
	{
		size_t index = 0;
		if constexpr (Is_reflective_v<Type> && Has_reflectName_v<Type>)
		{
			// is complex type
			if (m_reflectiveClasses)
			{
				if (const auto iter = m_reflectiveClasses->find(Type::reflectName());
					iter != m_reflectiveClasses->cend())
				{
					return memberValuesInternal(iter->second, a_memberName, [&a_value, &index]()
						{
							if (a_value.size() < index)
							{
								a_value[index] = Type{};
								++index;
							}
						});
				}
				return false;
			}
		}
		else
		{
			// is simple type
			return memberValues(a_memberName, [&a_value, &index](const std::string& a_strValue)
				{
					if (Type temp; (a_value.size() < index) && from_string(temp, a_strValue))
					{
						a_value[index] = std::move(temp);
						++index;
						return true;
					}
					return false;
				});
		}
		return false;
	}

	template<typename Type>
	bool memberValue(const std::string& a_memberName, Type& a_value)const noexcept
	{
		if constexpr (Is_reflective_v<Type> && Has_reflectName_v<Type>)
		{
			// is complex type
			if (m_reflectiveClasses)
			{
				if (const auto iter = m_reflectiveClasses->find(Type::reflectName());
					iter != m_reflectiveClasses->cend())
				{
					setTempTreeNode(iter->second, a_memberName);
					Type::init_reflect(a_value);
					RHIReflectData::releaseTempTreeNode(iter->second);
					return true;
				}
			}
		}
		else
		{
			// is simple type
			std::string strValue;
			if (RHIReflectData::memberValueInternal(a_memberName, strValue))
			{
				from_string(a_value, strValue);
				return true;
			}
		}
		return false;
	}

	template<typename FlagType, typename BaseType>
	bool flagValue(const std::string& a_memberName, FlagType& a_value)const
	{
		if (std::vector<std::string> values; flagValueInternal(a_memberName, values))
		{
			for (const auto& str : values)
			{
				if (BaseType temp; from_string<BaseType>(temp, trim(str)))
				{
					a_value |= temp;
				}
				else
				{
					return false;
				}
			}
		}
		return false;
	}

};
#pragma warning(pop)