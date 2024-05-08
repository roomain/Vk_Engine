#include "pch.h"
#include <ranges>
#include <algorithm>
#include "VkEngineDevice.h"
#include "vk_check.h"
#include "vk_parameters.h"
#include "vk_initializers.h"

VkEngineDevice::VkEngineDevice(const VkInstance a_vkInstanceHandle, const VkPhysicalDevice a_physical, const VkDevice a_logical) :
    m_vulkanInstance{ a_vkInstanceHandle }, m_physical{ a_physical }, m_device{ a_logical }
{
	//
}

VkEngineDevice::~VkEngineDevice()
{
	//
}

void VkEngineDevice::waitForDeviceIdle()
{ 
	VK_CHECK(vkDeviceWaitIdle(m_device)) 
}

bool VkEngineDevice::checkDeviceLayers(VkPhysicalDevice a_device, const std::vector<std::string>& a_desiredLayers)
{
    uint32_t numLayers;
    vkEnumerateDeviceLayerProperties(a_device, &numLayers, nullptr);
    std::vector<VkLayerProperties> vLayers(numLayers);
    vkEnumerateDeviceLayerProperties(a_device, &numLayers, vLayers.data());
    for (const auto& layer : a_desiredLayers)
    {
        if (std::ranges::find_if(vLayers.cbegin(), vLayers.cend(), [&layer](const auto& layerProp) {
            return layerProp.layerName == layer;
            }) == vLayers.cend())
        {
            return false;
        }
    }
    return true;
}

bool VkEngineDevice::checkDeviceExtension(VkPhysicalDevice a_device, const std::vector<std::string>& a_desiredExts)
{
    uint32_t numExtension;
    vkEnumerateDeviceExtensionProperties(a_device, nullptr, &numExtension, nullptr);
    std::vector<VkExtensionProperties> vProperties(numExtension);
    vkEnumerateDeviceExtensionProperties(a_device, nullptr, &numExtension, vProperties.data());
    for (const auto& extension : a_desiredExts)
    {
        if (std::ranges::find_if(vProperties.cbegin(), vProperties.cend(), [&extension](const auto& extProp) {
            return extProp.extensionName == extension;
            }) == vProperties.cend())
        {
            return false;
        }
    }
    return true;
}