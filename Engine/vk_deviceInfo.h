#pragma once
/***********************************************
* @headerfile vk_deviceInfo.h
* @date 25 / 05 / 2024
* @author Roomain
************************************************/
#include <vector>
#include <unordered_map>
#include <vulkan/vulkan.hpp>


#pragma warning(push)
#pragma warning(disable : 4251)

/*@brief queue family capabilities*/
struct QueueCapabilities
{
	uint32_t QueueFamily = 0;
	uint32_t QueueCount = 0;
};

/*@brief queue configuration*/
struct QueueConfig : QueueCapabilities
{
	std::vector<float> Priorities;
};

/*@brief list of queue configuration*/
using QueueConfList = std::vector<QueueConfig>;

/*@brief list of configuration by flag*/
using QueueConfMap = std::unordered_map<VkQueueFlags, QueueConfList>;

/*@brief configuration for compatible device*/
struct VKDeviceInfo
{
	VkPhysicalDevice PhysicalDeviceHandle = VK_NULL_HANDLE;				/*!< device handle*/
	VkDeviceCreateFlags Flag = 0;										/*!< device flags*/
	VkPhysicalDeviceType DeviceType = VK_PHYSICAL_DEVICE_TYPE_OTHER;	/*!< device type*/
	std::string DeviceName;												/*!< name of device*/
	QueueConfMap Queues;												/*!< compatible queues per flag*/
};


#pragma warning(pop)