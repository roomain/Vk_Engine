#include "pch.h"
#include <ranges>
#include "vk_struct_display.h"
#include "VkApplication.h"
#include "vk_initializers.h"
#include "vk_check.h"
#include "IRHICapabilitiesDisplayer.h"
#include "vk_parameters.h"
#include "vk_enumToString.h"

void VkApplication::createVulkanInstance(VkApplication* const a_this, const VKInstanceSettings& a_setting)
{
	if (a_setting.isValid())
	{
		VkApplicationInfo appInfo = gen_applicationInfo();
		appInfo.pApplicationName = a_setting.ApplicationName.c_str();
		appInfo.pEngineName = a_setting.EngineName.c_str();
		appInfo.applicationVersion = a_setting.AppVersion;

		VkInstanceCreateInfo instanceInfo = gen_instanceCreateInfo();
		instanceInfo.pApplicationInfo = &appInfo;

		std::vector<const char*> vLayers;
		std::ranges::transform(a_setting.Layers.cbegin(), a_setting.Layers.cend(), std::back_inserter(vLayers),
			[](const auto& ext) {return ext.c_str(); });
		vLayers.emplace_back(VK_EXT_VALIDATION_FLAGS_EXTENSION_NAME);
		instanceInfo.ppEnabledLayerNames = vLayers.data();
		instanceInfo.enabledLayerCount = static_cast<uint32_t>(vLayers.size());

		std::vector<const char*> vExtension;
		std::ranges::transform(a_setting.Extensions.cbegin(), a_setting.Extensions.cend(), std::back_inserter(vExtension),
			[](const auto& ext) {return ext.c_str(); });
		vExtension.emplace_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		vExtension.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		instanceInfo.ppEnabledExtensionNames = vExtension.data();
		instanceInfo.enabledExtensionCount = static_cast<uint32_t>(vExtension.size());
		// todo
		VK_CHECK(vkCreateInstance(&instanceInfo, nullptr, &(a_this->m_vulkanInstance)))
	}
}

VkApplication::VkApplication()
{
	VKInstanceSettings settings;
	VkApplication::createVulkanInstance(this, settings);
	// todo
}

VkApplication::~VkApplication()
{
	release();
}

void VkApplication::release()
{
	// release all resources 

	// release all devices
	m_devices.clear();

	if (m_vulkanInstance != VK_NULL_HANDLE)
	{
		vkDestroyInstance(m_vulkanInstance, nullptr);
		m_vulkanInstance = VK_NULL_HANDLE;
		// todo
	}
}

VkEngineDevicePtr VkApplication::createDevice(const int a_devIndex)
{
	VkEngineDevicePtr device;
	//todo
	return device;
}

void VkApplication::displayInstanceCapabilities(IRHICapabilitiesDisplayer& a_displayer)
{
	uint32_t numLayer;
	vkEnumerateInstanceLayerProperties(&numLayer, nullptr);
	std::vector<VkLayerProperties> vLayers{ numLayer };
	vkEnumerateInstanceLayerProperties(&numLayer, vLayers.data());
	a_displayer.pushCategory("Instance layers");
	for (const auto& layer : vLayers)
	{
		a_displayer.pushCategory(layer.layerName);
		a_displayer.setCapability("description", layer.description);
		a_displayer.setCapability("version", layer.specVersion);
		a_displayer.popCategory();
	}
	a_displayer.popCategory();


	uint32_t numExtension;
	vkEnumerateInstanceExtensionProperties(nullptr, &numExtension, nullptr);
	std::vector<VkExtensionProperties> vExtensions{ numExtension };
	vkEnumerateInstanceExtensionProperties(nullptr, &numExtension, vExtensions.data());
	a_displayer.pushCategory("Instance extensions");
	for (const auto& extend : vExtensions)
	{
		a_displayer.pushCategory(extend.extensionName);
		a_displayer.setCapability("version", extend.specVersion);
		a_displayer.popCategory();
	}
	a_displayer.popCategory();
}

void VkApplication::displayDevicesCapabilities(IRHICapabilitiesDisplayer& a_displayer)const
{
	if (m_vulkanInstance != VK_NULL_HANDLE)
	{
		uint32_t numDevices;
		vkEnumeratePhysicalDevices(m_vulkanInstance, &numDevices, nullptr);
		std::vector<VkPhysicalDevice> vDevices{ numDevices };
		vkEnumeratePhysicalDevices(m_vulkanInstance, &numDevices, vDevices.data());
		for (const auto& device : vDevices)
		{	
			VkPhysicalDeviceProperties prop;
			vkGetPhysicalDeviceProperties(device, &prop);
			a_displayer.pushCategory(prop.deviceName);
			a_displayer.setCapability("device type", to_string(prop.deviceType));
			a_displayer.setCapability("device id", prop.deviceID);
			a_displayer.setCapability("vendor id", prop.vendorID);
			a_displayer.setCapability("api version", prop.apiVersion);
			a_displayer.setCapability("driver version", prop.driverVersion);

			a_displayer.pushCategory("Sparse properties");
            display(a_displayer, prop.sparseProperties);
			a_displayer.popCategory();

			a_displayer.pushCategory("limits");
            display(a_displayer, prop.limits);
			a_displayer.popCategory();

			VkPhysicalDeviceFeatures feature;
			vkGetPhysicalDeviceFeatures(device, &feature);
			a_displayer.pushCategory("features");
			display(a_displayer, feature);
			a_displayer.popCategory();
		}
	}	
}