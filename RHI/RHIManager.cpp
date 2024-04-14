#include "pch.h"
#include "RHIManager.h"
#include "RHIReflectData.h"

RHIManager& RHIManager::instance()
{
	static RHIManager instance;
	return instance;
}

void RHIManager::loadConfiguration(const std::string& a_directory)
{
	m_configuration = std::make_shared<RHIReflectiveClassSet>(a_directory);
	RHIReflectData::setReflectiveClassSet(m_configuration);
}

RHIReflectiveClassSetPtr RHIManager::configuration()const noexcept
{
	return m_configuration;
}