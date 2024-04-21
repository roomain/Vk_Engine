#pragma once
/***********************************************
* @headerfile VkApplication.h
* @date 18 / 04 / 2024
* @author Roomain
************************************************/
#include <string>
#include <memory>
#include <vector>
#include <vulkan/vulkan.hpp>
#include "VkEngineDevice.h"

class IRHICapabilitiesDisplayer;

class VkApplication
{
private:
	VkInstance m_vulkanInstance = VK_NULL_HANDLE;	/*!< vulkan instance*/
	std::vector<VkEngineDevicePtr> m_devices;		/*!< engine device list*/
	//

public:
	VkApplication(const std::string_view a_appName, const int a_version);
	~VkApplication();

	using device_const_iterator = std::vector<VkEngineDevicePtr>::const_iterator;
	[[nodiscard]] constexpr device_const_iterator cbegin()const { return m_devices.cbegin(); }
	[[nodiscard]] constexpr device_const_iterator cend()const { return m_devices.cend(); }
	[[nodiscard]] constexpr size_t numDevices()const { return m_devices.size(); }
	[[nodiscard]] VkEngineDevicePtr operator[](const size_t& a_index)const { return m_devices[a_index]; }
	VkEngineDevicePtr createDevice(const int a_devIndex);

	static void displayInstanceCapabilities(IRHICapabilitiesDisplayer& a_displayer);
	void displayDevicesCapabilities(IRHICapabilitiesDisplayer& a_displayer)const;
	// todo
};

