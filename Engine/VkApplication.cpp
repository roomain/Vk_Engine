#include "pch.h"
#include <ranges>
#include "vk_struct_display.h"
#include "VkApplication.h"
#include "vk_initializers.h"
#include "vk_check.h"
#include "IRHICapabilitiesDisplayer.h"
#include "vk_parameters.h"
#include "vk_enumToString.h"
#include "stringUtils.h"

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

		std::vector<const char*> vLayers = vStringToChar(a_setting.Layers);		
		//vLayers.emplace_back(VK_EXT_VALIDATION_FLAGS_EXTENSION_NAME);
		instanceInfo.ppEnabledLayerNames = vLayers.data();
		instanceInfo.enabledLayerCount = static_cast<uint32_t>(vLayers.size());

		std::vector<const char*> vExtension = vStringToChar(a_setting.Extensions);
		//vExtension.emplace_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		//vExtension.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		instanceInfo.ppEnabledExtensionNames = vExtension.data();
		instanceInfo.enabledExtensionCount = static_cast<uint32_t>(vExtension.size());
		
		VK_CHECK(vkCreateInstance(&instanceInfo, nullptr, &(a_this->m_vulkanInstance)))
	}
}

bool VkApplication::findQueue(const std::vector<VkQueueFamilyProperties>& a_queueFamilies, const VkQueueFlags a_queueFlag, VKDeviceInfo& a_devInfo)
{
	uint32_t queueIndex = 0;
	for (const auto& properties : a_queueFamilies)
	{
		if ((properties.queueFlags & a_queueFlag) == a_queueFlag)
		{
			a_devInfo.Queues[a_queueFlag] = queueIndex;
			return true;
		}
		++queueIndex;
	}
	return false;
}

VkApplication::VkApplication(const VKInstanceSettings& a_settings)
{
	VkApplication::createVulkanInstance(this, a_settings);
	//
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
		a_displayer.setCapability("description", std::string(layer.description));
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

			uint32_t queueFamilyCount;
			vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
			std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyProperties.data());
			a_displayer.pushCategory("Queues");
			for (const auto& queueFamily : queueFamilyProperties)
				display(a_displayer, queueFamily);			
			a_displayer.popCategory();
		}
	}	
}

bool VkApplication::findCompatibleDevices(const VKDeviceSettings& a_settings, std::vector<VKDeviceInfo>& a_vCompatibeDevices)const
{
	if (m_vulkanInstance != VK_NULL_HANDLE)
	{
		uint32_t numDevices;
		vkEnumeratePhysicalDevices(m_vulkanInstance, &numDevices, nullptr);
		std::vector<VkPhysicalDevice> vDevices{ numDevices };
		vkEnumeratePhysicalDevices(m_vulkanInstance, &numDevices, vDevices.data());
		int deviceIndex = 0;
		for (const auto& device : vDevices)
		{			
			VKDeviceInfo devInfo{ .DeviceId = deviceIndex };
			VkPhysicalDeviceProperties prop;
			uint32_t queueFamilyCount;
			vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
			std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyProperties.data());

			if (VkApplication::findQueue(queueFamilyProperties, a_settings.QueueFlag, devInfo))
			{
				// todo
			}
			deviceIndex++;
		}
		return true;
	}
	return false;
}