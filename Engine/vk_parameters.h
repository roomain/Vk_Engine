#pragma once
/***********************************************
* @headerfile vk_parameters.h
* @date 23 / 04 / 2024
* @author Roomain
************************************************/
#include "RHI_macros.h"
#include <vector>
#include <string>
#include "vk_parameters.generated.h"
#include "vk_From_string.h"

struct VKSettings
{
	virtual bool isValid()const noexcept = 0;
};

REFLECT_CLASS(VKInstanceSettings)
struct VKInstanceSettings : VKSettings
{
	REFLECT_MEMBER
	std::string ApplicationName;
	
	REFLECT_MEMBER
	std::string EngineName;

	REFLECT_MEMBER
	int AppVersion = 0;

	REFLECT_MEMBER;
	std::vector<std::string> Layers;

	REFLECT_MEMBER;
	std::vector<std::string> Extensions;

	[[nodiscard]] bool isValid()const noexcept override
	{
		return !ApplicationName.empty() && !EngineName.empty() && AppVersion > 0;
	}
private:
	DECLARE_REFLECT_CLASS(VKInstanceSettings)
};

IMPLEMENT_REFLECT_CLASS(VKInstanceSettings)



REFLECT_CLASS(VKDeviceSettings)
struct VKDeviceSettings : VKSettings
{
	int DeviceIndex = -1;

	REFLECT_MEMBER;
	std::vector<std::string> Layers;

	REFLECT_MEMBER;
	std::vector<std::string> Extensions;

	bool isValid()const noexcept override
	{
		return DeviceIndex >= 0 /*todo*/;
	}
private:
	DECLARE_REFLECT_CLASS(VKDeviceSettings)
};

IMPLEMENT_REFLECT_CLASS(VKDeviceSettings)