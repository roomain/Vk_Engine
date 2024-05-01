#include "pch.h"
#include "VkEngineDevice.h"
#include "vk_check.h"
#include "vk_parameters.h"
#include "vk_initializers.h"

VkEngineDevice::VkEngineDevice(const VkInstance a_vkInstanceHandle, const VKDeviceSettings& a_settings)
{
	auto deviceCreateInfo = gen_deviceCreateInfo();
    deviceCreateInfo.flags;
    deviceCreateInfo.queueCreateInfoCount;
    deviceCreateInfo.pQueueCreateInfos;
    deviceCreateInfo.enabledLayerCount;
    deviceCreateInfo.ppEnabledLayerNames;
    deviceCreateInfo.enabledExtensionCount;
    deviceCreateInfo.ppEnabledExtensionNames;
    deviceCreateInfo.pEnabledFeatures;
}

VkEngineDevice::~VkEngineDevice()
{
	//
}

void VkEngineDevice::waitForDeviceIdle()
{ 
	VK_CHECK(vkDeviceWaitIdle(m_device)) 
}