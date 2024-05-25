#pragma once
/***********************************************
* @headerfile VkEngineDevice.h
* @date 20 / 04 / 2024
* @author Roomain
************************************************/
#include <memory>
#include <vulkan/vulkan.hpp>
#include <unordered_map>
#include "VkQueueStack.h"
#include "vk_engine_globals.h"

#pragma warning(push)
#pragma warning(disable : 4251)

struct VkSwapChainConf;
struct VKDeviceSettings;
class VkApplication;
class VkSwapChain;

using QueueStackMap = std::unordered_map<uint32_t, VkQueueStack>;

/*@brief vulkan device*/
class ENGINE_EXPORT VkEngineDevice : public std::enable_shared_from_this<VkEngineDevice>
{
	friend VkApplication;
	friend VkSwapChain;

private:
	VkInstance m_vulkanInstance = VK_NULL_HANDLE;	/*!< vulkan instance*/
	VkPhysicalDevice m_physical = VK_NULL_HANDLE;	/*!< physical device that vulkan will use*/
	VkDevice m_device = VK_NULL_HANDLE;				/*!< vulkan logical device*/
	mutable QueueStackMap m_Queues;

	explicit VkEngineDevice(const VkInstance a_vkInstanceHandle, const VkPhysicalDevice a_physical, 
		const VkDevice a_logical, const QueueConfMap& a_queueConf);
	
public:	
	VkEngineDevice() = delete;
	virtual ~VkEngineDevice();
	[[nodiscard]] constexpr bool isValid()const { return m_device != VK_NULL_HANDLE; }

	// check device compatibility
	static bool checkDeviceLayers(VkPhysicalDevice a_device, const std::vector<std::string>& a_desiredLayers);
	static bool checkDeviceExtension(VkPhysicalDevice a_device, const std::vector<std::string>& a_desiredExts);
	
	/*@brief get queue having flag*/
	static void getQueueFamilies(const VKDeviceInfo& a_info, const VkQueueFlags a_flag, std::vector<uint32_t>& a_vFamily);

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