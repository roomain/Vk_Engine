#pragma once
/***********************************************
* @headerfile RHIConfigDatabase.h
* @date 09 / 04 / 2024
* @author Roomain
************************************************/
#include "RHI_globals.h"
#include "RHIReflectiveClassSet.h"
#include "not_copiable.h"

#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)

/*@brief singleton managin RHI*/
class RHI_EXPORT RHIManager
{
private:
	RHIReflectiveClassSetPtr m_configuration; /*!< classes configurations*/
	RHIManager() = default;

public:
	static RHIManager& instance();
	NOT_COPIABLE(RHIManager);

	void loadConfiguration(const std::string& a_directory);
	RHIReflectiveClassSetPtr configuration()const noexcept;
};

#pragma warning(pop)