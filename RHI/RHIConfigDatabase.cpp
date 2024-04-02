#include "pch.h"
#include <filesystem>
#include <ranges>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "RHIConfigDatabase.h"

namespace fs = std::filesystem;

void RHIConfigDatabase::loadClass(const boost::property_tree::ptree& a_tree, Class& a_class)
{
	for (const auto&[name, prop] : a_tree)
	{
		if (prop.empty())
		{
			a_class.m_member.try_emplace(name, prop.data());
		}
		else
		{
			auto [iter, valid] = a_class.m_subClass.try_emplace(name);
			if (valid)
				RHIConfigDatabase::loadClass(prop, iter->second);
		}
	}
}

void RHIConfigDatabase::loadConfiguration(const std::string& a_directory, ClassMap& a_data)
{
	fs::path jsonDir(a_directory);
	auto isJsonFile = [](auto& a_entry) { return a_entry.is_regular_file() &&
		(a_entry.path().extension() == ".json" || a_entry.path().extension() == ".JSON"); };

	if (fs::exists(jsonDir) && fs::is_directory(jsonDir))
	{
		for (const auto& entry : fs::recursive_directory_iterator(jsonDir) | std::views::filter(isJsonFile))
		{
			boost::property_tree::ptree propTree;
			boost::property_tree::read_json(entry.path().string(), propTree);
			for (const auto& [name, prop] : propTree)
			{
				auto [iter, valid] = a_data.try_emplace(name);
				if (valid)
					RHIConfigDatabase::loadClass(prop, iter->second);
			}
		}
	}
}

RHIConfigDatabase::RHIConfigDatabase(const std::string& a_directory)
{
	RHIConfigDatabase::loadConfiguration(a_directory, m_classes);
}

RHIConfigDatabase::const_ClassIterator RHIConfigDatabase::find(const std::string& a_classname)const
{
	return m_classes.find(a_classname);
}