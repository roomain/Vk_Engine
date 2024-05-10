#include "pch.h"
#include "RHIReflectiveClassSet.h"
#include "RHIReflectData.h"
#include <filesystem>
#include <ranges>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "RHIReflectData_intern.h"

namespace fs = std::filesystem;

RHIReflectDataPtr RHIReflectiveClassSet::emplaceNewReflectData(const std::string& a_name)
{
	return m_classesDataset.try_emplace(a_name, std::make_unique<RHIReflectData>(
		std::make_shared<RHIReflectData_intern>()
	)).first->second;
}

void RHIReflectiveClassSet::loadConfigurationFile(const std::string& a_file, RHIReflectDataSet& a_dataset)
{
	boost::property_tree::ptree propTree;
	boost::property_tree::read_json(a_file, propTree);
	for (const auto& [name, prop] : propTree)
		a_dataset.try_emplace(name, std::make_unique<RHIReflectData>(
			std::make_shared<RHIReflectData_intern>(prop, nullptr)
		));
}

void RHIReflectiveClassSet::loadConfiguration(const std::string& a_directory, RHIReflectDataSet& a_dataset)
{
	fs::path jsonDir = std::filesystem::current_path();
	jsonDir.append(a_directory);
	
	auto isJsonFile = [](auto& a_entry) { return a_entry.is_regular_file() &&
		(a_entry.path().extension() == ".json" || a_entry.path().extension() == ".JSON"); };
	
	if (fs::exists(jsonDir) && fs::is_directory(jsonDir))
	{
		for (const auto& entry : fs::recursive_directory_iterator(jsonDir) | std::views::filter(isJsonFile))
			RHIReflectiveClassSet::loadConfigurationFile(entry.path().string(), a_dataset);
	}
}

RHIReflectiveClassSet::RHIReflectiveClassSet(const std::string& a_directory)
{
	RHIReflectiveClassSet::loadConfiguration(a_directory, m_classesDataset);
}

void RHIReflectiveClassSet::loadConfigurationFile(const std::string& a_file)
{
	RHIReflectiveClassSet::loadConfigurationFile(a_file, m_classesDataset);
}

RHIReflectiveClassSet::const_ReflectDataSetIterator RHIReflectiveClassSet::find(const std::string& a_classname)const
{
	return m_classesDataset.find(a_classname);
}