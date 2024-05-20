#pragma once
/***********************************************
* @headerfile VkEngineDevice.h
* @date 20 / 04 / 2024
* @author Roomain
************************************************/
#include <memory>
#include <vulkan/vulkan.hpp>
#include "vk_engine_globals.h"

#pragma warning(push)
#pragma warning(disable : 4251)

struct VKDeviceSettings;
class VkApplication;
class VkSwapChain;
class VkEngineCommandQueue;


struct QueueInfo
{
	uint32_t QueueFamily;
	uint32_t QueueCount;
};

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

/*@brief get queue having flag*/
void ENGINE_EXPORT getQueueFamilies(const VKDeviceInfo& a_info, const VkQueueFlags a_flag, std::vector<uint32_t>& a_vFamily);

struct VkSwapChainConf;

/*@brief vulkan device*/
class ENGINE_EXPORT VkEngineDevice : public std::enable_shared_from_this<VkEngineDevice>
{
	friend VkApplication;
	friend VkSwapChain;

private:
	VkInstance m_vulkanInstance = VK_NULL_HANDLE;	/*!< vulkan instance*/
	VkPhysicalDevice m_physical = VK_NULL_HANDLE;	/*!< physical device that vulkan will use*/
	VkDevice m_device = VK_NULL_HANDLE;				/*!< vulkan logical device*/


	explicit VkEngineDevice(const VkInstance a_vkInstanceHandle, const VkPhysicalDevice a_physical, const VkDevice a_logical);
	

public:	
	VkEngineDevice() = delete;
	virtual ~VkEngineDevice();
	[[nodiscard]] constexpr bool isValid()const { return m_device != VK_NULL_HANDLE; }

	// check device compatibility
	static bool checkDeviceLayers(VkPhysicalDevice a_device, const std::vector<std::string>& a_desiredLayers);
	static bool checkDeviceExtension(VkPhysicalDevice a_device, const std::vector<std::string>& a_desiredExts);

	std::shared_ptr<VkSwapChain> createSwapChain(const VkSwapChainConf& a_configuration);
	std::shared_ptr<VkEngineCommandQueue> createCommandQueue(const uint32_t a_familyIndex)const;
	// create frame buffer

	//create image view

	// create image

	// create fence

	// create semaphore

	// wait device idle
	void waitForDeviceIdle();

};

using VkEngineDevicePtr = std::shared_ptr<VkEngineDevice>;

#pragma warning(pop)