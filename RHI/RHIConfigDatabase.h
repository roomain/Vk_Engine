#pragma once
/***********************************************
* @headerfile RHIConfigDatabase.h
* @date 31 / 03 / 2024
* @author Roomain
************************************************/
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

namespace boost::property_tree
{
	class ptree;
}

/*@brief Contains all read data from json*/
class RHIConfigDatabase
{
public:
	struct Class
	{
		std::unordered_map<std::string, std::string> m_member;
		std::unordered_map<std::string, Class> m_subClass;
		
		template<typename Type>
		bool getMember(const std::string& a_name, Type& a_value)const
		{
			if (auto iterMember = m_member.find(a_name); iterMember != m_member.cend())
			{
				return from_string(iterMember->second, a_value);
			}
			else if (auto iterClass = m_subClass.find(a_name); iterClass != m_subClass.cend())
			{
				Type::init(a_value, iterClass->second);
			}
			return false;
		}
	};

private:
	using ClassMap = std::unordered_map<std::string, Class>;
	ClassMap m_classes;

	static void loadClass(const boost::property_tree::ptree& a_tree, Class& a_class);
	static void loadConfiguration(const std::string& a_directory, ClassMap& a_data);

public:
	RHIConfigDatabase() = delete;
	// read all json in directory recursively
	explicit RHIConfigDatabase(const std::string& a_directory);

	using const_ClassIterator = std::unordered_map<std::string, Class>::const_iterator;
	const_ClassIterator cbegin()const { return m_classes.cbegin(); }
	const_ClassIterator cend()const { return m_classes.cend(); }
	const_ClassIterator find(const std::string & a_classname)const;
};

