#include "pch.h"
#include "VkApplication.h"
#include "vk_initializers.h"
#include "vk_check.h"
#include "IRHICapabilitiesDisplayer.h"
#include "vk_enumToString.h"
#include "vk_struct_display.h"


VkApplication::VkApplication(const std::string_view a_appName, const int a_version)
{
	VkApplicationInfo appInfo = gen_applicationInfo();
	appInfo.pApplicationName = a_appName.data();
	appInfo.pEngineName = "VulkanEngine";
	appInfo.applicationVersion = a_version;

	VkInstanceCreateInfo instanceInfo = gen_instanceCreateInfo();
	instanceInfo.pApplicationInfo = &appInfo;

	std::vector<const char*> vLayers;
	/*std::transform(a_conf.instanceExtProps.cbegin(), a_conf.instanceExtProps.cend(), std::back_inserter(vLayers),
		[](const auto& ext) {return ext.c_str(); });*/
	vLayers.emplace_back(VK_EXT_VALIDATION_FLAGS_EXTENSION_NAME);
	instanceInfo.ppEnabledLayerNames = vLayers.data();
	instanceInfo.enabledLayerCount = static_cast<uint32_t>(vLayers.size());

	std::vector<const char*> vExtension;
	/*std::transform(a_conf.instanceExtProps.cbegin(), a_conf.instanceExtProps.cend(), std::back_inserter(vExtension),
		[](const auto& ext) {return ext.c_str(); });*/
	vExtension.emplace_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	vExtension.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	instanceInfo.ppEnabledExtensionNames = vExtension.data();
	instanceInfo.enabledExtensionCount = static_cast<uint32_t>(vExtension.size());
	// todo
	//VK_CHECK(vkCreateInstance())
	// todo
}

VkApplication::~VkApplication()
{
	// release all resources 
	
	// release all devices
	m_devices.clear();

	if (m_vulkanInstance != VK_NULL_HANDLE)
	{
		vkDestroyInstance(m_vulkanInstance, nullptr);
		// todo
	}
}

VkEngineDevicePtr VkApplication::createDevice(const int a_devIndex)
{
	//todo
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