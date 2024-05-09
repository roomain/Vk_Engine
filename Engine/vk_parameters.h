#pragma once
/***********************************************
* @headerfile vk_parameters.h
* @date 23 / 04 / 2024
* @author Roomain
************************************************/
#include "RHI_macros.h"
#include <vector>
#include <string>
#include "vk_engine_globals.h"
#include "vk_From_string.h"
#include "vk_parameters.generated.h"

#pragma warning(push)
#pragma warning(disable : 4251)

struct ENGINE_EXPORT VKSettings
{
	virtual bool isValid()const noexcept = 0;
};

REFLECT_CLASS(VKInstanceSettings)
struct ENGINE_EXPORT VKInstanceSettings : VKSettings
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


REFLECT_CLASS(VKQueueSettings)
struct VKQueueSettings
{
	REFLECT_MEMBER
	int Count = 1;

	REFLECT_FLAG(VkQueueFlagBits)
	VkQueueFlags QueueFlag = 0;
private:
	DECLARE_REFLECT_CLASS(VKQueueSettings)
};


REFLECT_CLASS(VKDeviceSettings)
struct ENGINE_EXPORT VKDeviceSettings : VKSettings
{
	REFLECT_MEMBER;
	int DeviceIndex = -1;

	REFLECT_FLAG(VkQueueFlagBits)
	VkDeviceCreateFlags DeviceFlag = 0;

	REFLECT_MEMBER;
	std::vector<std::string> Layers;

	REFLECT_MEMBER;
	std::vector<std::string> Extensions;

	REFLECT_MEMBER;
	std::vector<VKQueueSettings> QueuesSettings;

	inline bool isValid()const noexcept override
	{
		return DeviceIndex >= 0 && !QueuesSettings.empty();

	}
private:
	DECLARE_REFLECT_CLASS(VKDeviceSettings)
};

#pragma warning(pop)