#include "pch.h"
#include "VkEngineDevice.h"
#include "vk_check.h"

void VkEngineDevice::waitForDeviceIdle()
{ 
	VK_CHECK(vkDeviceWaitIdle(m_device)) 
}