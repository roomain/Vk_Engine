#pragma once
/***********************************************
* @headerfile VkApplication.h
* @date 18 / 04 / 2024
* @author Roomain
************************************************/
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <vulkan/vulkan.hpp>
#include "VkEngineDevice.h"
#include "vk_engine_globals.h"


#pragma warning(push)
#pragma warning(disable : 4251)

class IRHICapabilitiesDisplayer;
struct VKInstanceSettings;



class ENGINE_EXPORT VkApplication
{
private:
	VkInstance m_vulkanInstance = VK_NULL_HANDLE;	/*!< vulkan instance*/
	std::vector<VkEngineDevicePtr> m_devices;		/*!< engine device list*/
	static void createVulkanInstance(VkApplication* const a_this, const VKInstanceSettings& a_setting);
	static bool findQueue(const std::vector<VkQueueFamilyProperties>& a_queueFamilies, const VKDeviceSettings& a_settings, VKDeviceInfo& a_devInfo);
	
public:
	explicit VkApplication(const VKInstanceSettings& a_settings);
	VkApplication();
	~VkApplication();
	void release();

	constexpr VkInstance vulkanInstance()const noexcept { return m_vulkanInstance; }
	using device_const_iterator = std::vector<VkEngineDevicePtr>::const_iterator;
	[[nodiscard]] constexpr device_const_iterator cbegin()const { return m_devices.cbegin(); }
	[[nodiscard]] constexpr device_const_iterator cend()const { return m_devices.cend(); }
	[[nodiscard]] constexpr size_t numDevices()const { return m_devices.size(); }
	[[nodiscard]] VkEngineDevicePtr operator[](const size_t& a_index)const { return m_devices[a_index]; }
	VkEngineDevicePtr createDevice(const VKDeviceSettings& a_settings, const VKDeviceInfo& a_devInfo);

	/*@brief display instance capabilities*/
	static void displayInstanceCapabilities(IRHICapabilitiesDisplayer& a_displayer);
	/*@brief display capabilities of all devices (Vulkan instance must be instanciated)*/
	void displayDevicesCapabilities(IRHICapabilitiesDisplayer& a_displayer)const;
	// todo

	/*@brief find compatible devices with desired settings*/
	bool findCompatibleDevices(const VKDeviceSettings& a_settings, std::vector<VKDeviceInfo>& a_vCompatibeDevices)const;
};


#pragma warning(pop)