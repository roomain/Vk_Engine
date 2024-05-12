#pragma once
/***********************************************
* @headerfile VkEngineDevice.h
* @date 20 / 04 / 2024
* @author Roomain
************************************************/
#include <memory>
#include <vulkan/vulkan.hpp>
#include "vk_engine_globals.h"


struct VKDeviceSettings;
class VkApplication;
class VkSwapChain;


struct QueueInfo
{
	uint32_t QueueFamily;
	uint32_t QueueCount;
};

struct Queue : QueueInfo
{
	std::vector<VkCommandPool> CmdPools;
};
using QueueList = std::vector<Queue>;
using QueuePools = std::unordered_map<VkQueueFlags, QueueList>;


struct QueueConfig : QueueInfo
{
	std::vector<float> Priorities;
};


using QueueConfList = std::vector<QueueConfig>;

/*@brief configuration for compatible device*/
struct VKDeviceInfo
{
	VkPhysicalDevice PhysicalDeviceHandle = VK_NULL_HANDLE;				/*!< device handle*/
	VkDeviceCreateFlags Flag = 0;										/*!< device flags*/
	VkPhysicalDeviceType DeviceType = VK_PHYSICAL_DEVICE_TYPE_OTHER;	/*!< device type*/
	std::string DeviceName;												/*!< name of device*/
	std::unordered_map<VkQueueFlags, QueueConfList> Queues;				/*!< compatible queues by flag*/
};

/*@brief vulkan device*/
class ENGINE_EXPORT VkEngineDevice
{
	friend VkApplication;

protected:
	VkInstance m_vulkanInstance = VK_NULL_HANDLE;	/*!< vulkan instance*/
	VkPhysicalDevice m_physical = VK_NULL_HANDLE;	/*!< physical device that vulkan will use*/
	VkDevice m_device = VK_NULL_HANDLE;				/*!< vulkan logical device*/
	QueuePools m_queuePools;						/*!< used queues*/

	explicit VkEngineDevice(const VkInstance a_vkInstanceHandle, const VkPhysicalDevice a_physical, const VkDevice a_logical, const std::unordered_map<VkQueueFlags, QueueList>& a_queueInfo);
	void createCommandPool(const uint32_t a_familyIndex);

public:	
	VkEngineDevice() = delete;
	virtual ~VkEngineDevice();
	[[nodiscard]] constexpr bool isValid()const { return m_device != VK_NULL_HANDLE; }

	// check device compatibility
	static bool checkDeviceLayers(VkPhysicalDevice a_device, const std::vector<std::string>& a_desiredLayers);
	static bool checkDeviceExtension(VkPhysicalDevice a_device, const std::vector<std::string>& a_desiredExts);

	std::shared_ptr<VkSwapChain> createSwapChain(/*todo*/);

	// create command pool

	// create frame buffer

	//create image view

	// create image

	// create fence

	// create semaphore

	// wait device idle
	void waitForDeviceIdle();

};

using VkEngineDevicePtr = std::shared_ptr<VkEngineDevice>;