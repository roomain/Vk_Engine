#pragma once
/***********************************************
* @headerfile VkEngineDevice.h
* @date 20 / 04 / 2024
* @author Roomain
************************************************/
#include <memory>
#include <vulkan/vulkan.hpp>

struct VKDeviceSettings;

class VkApplication;

/*@brief vulkan device*/
class VkEngineDevice
{
	friend VkApplication;

protected:
	VkInstance m_vulkanInstance = VK_NULL_HANDLE;	/*!< vulkan instance*/
	VkPhysicalDevice m_physical = VK_NULL_HANDLE;	/*!< physical device that vulkan will use*/
	VkDevice m_device = VK_NULL_HANDLE;				/*!< vulkan logical device*/

public:
	explicit VkEngineDevice(const VkInstance a_vkInstanceHandle, const VkPhysicalDevice a_physical, const VkDevice a_logical);
	VkEngineDevice() = delete;
	virtual ~VkEngineDevice();
	[[nodiscard]] constexpr bool isValid()const { return m_device != VK_NULL_HANDLE; }

	// check device compatibility
	static bool checkDeviceLayers(VkPhysicalDevice a_device, const std::vector<std::string>& a_desiredLayers);
	static bool checkDeviceExtension(VkPhysicalDevice a_device, const std::vector<std::string>& a_desiredExts);

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