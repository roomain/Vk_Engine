#pragma once
/***********************************************
* @headerfile RHIReflectiveClassSet.h
* @date 13 / 04 / 2024
* @author Roomain
************************************************/
#include <memory>
#include <string>
#include <unordered_map>
#include "not_copiable.h"
#include "RHI_globals.h"

#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)

class RHIReflectData;
using RHIReflectDataPtr = std::shared_ptr<RHIReflectData>;
using RHIReflectDataSet = std::unordered_map<std::string, RHIReflectDataPtr>;

/*@brief regroup all reflective class values read from Json files*/
class RHI_EXPORT RHIReflectiveClassSet : public std::enable_shared_from_this<RHIReflectiveClassSet>
{
private:
	RHIReflectDataSet m_classesDataset;	/*!< values of each class*/

	static void loadConfiguration(const std::string& a_directory, RHIReflectDataSet& a_dataset);

public:
	NOT_COPIABLE(RHIReflectiveClassSet);
	// read all json in directory recursively
	explicit RHIReflectiveClassSet(const std::string& a_directory);

	using const_ReflectDataSetIterator = RHIReflectDataSet::const_iterator;
	const_ReflectDataSetIterator cbegin()const { return m_classesDataset.cbegin(); }
	const_ReflectDataSetIterator cend()const { return m_classesDataset.cend(); }
	const_ReflectDataSetIterator find(const std::string& a_classname)const;
};

using RHIReflectiveClassSetPtr = std::shared_ptr<RHIReflectiveClassSet>;
#pragma warning(pop)