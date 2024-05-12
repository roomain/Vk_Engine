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

using QueueInfoList = std::vector<QueueInfo>;
using QueueInfoMap = std::unordered_map<VkQueueFlags, QueueInfoList>;

using CmdPoolList = std::vector<VkCommandPool>;
using CmdPoolMap = std::unordered_map<VkQueueFlags, CmdPoolList>;


struct QueueConfig : QueueInfo
{
	std::vector<float> Priorities;
};

using QueueConfList = std::vector<QueueConfig>;
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

/*@brief vulkan device*/
class ENGINE_EXPORT VkEngineDevice
{
	friend VkApplication;

protected:
	VkInstance m_vulkanInstance = VK_NULL_HANDLE;	/*!< vulkan instance*/
	VkPhysicalDevice m_physical = VK_NULL_HANDLE;	/*!< physical device that vulkan will use*/
	VkDevice m_device = VK_NULL_HANDLE;				/*!< vulkan logical device*/
	QueueInfoMap m_queueMap;						/*!< used queues*/
	CmdPoolMap m_cmdPools;							/*!< command pool per type*/

	explicit VkEngineDevice(const VkInstance a_vkInstanceHandle, const VkPhysicalDevice a_physical, const VkDevice a_logical, const QueueConfMap& a_queueInfo);
	

public:	
	VkEngineDevice() = delete;
	virtual ~VkEngineDevice();
	[[nodiscard]] constexpr bool isValid()const { return m_device != VK_NULL_HANDLE; }

	// check device compatibility
	static bool checkDeviceLayers(VkPhysicalDevice a_device, const std::vector<std::string>& a_desiredLayers);
	static bool checkDeviceExtension(VkPhysicalDevice a_device, const std::vector<std::string>& a_desiredExts);

	std::shared_ptr<VkSwapChain> createSwapChain(/*todo*/);

	// create command pool
	bool createCommandPool(const VkQueueFlags a_Queueflag);
	int createCommandsPool(const VkQueueFlags a_Queueflag, const int a_numToCreate);
	size_t commandPoolCount(const VkQueueFlags a_Queueflag) const;

	// create frame buffer

	//create image view

	// create image

	// create fence

	// create semaphore

	// wait device idle
	void waitForDeviceIdle();

};

using VkEngineDevicePtr = std::shared_ptr<VkEngineDevice>;