#include "pch.h"
#include <ranges>
#include <algorithm>
#include "VkEngineDevice.h"
#include "VkSwapChain.h"
#include "VkEngineCommandQueue.h"
#include "VkEngineImage.h"

void VkEngineDevice::getQueueFamilies(const VKDeviceInfo& a_info, const VkQueueFlags a_flag, std::vector<uint32_t>& a_vFamily)
{
    for (const auto& [flag, queuelist] : a_info.Queues)
    {
        if ((flag & a_flag) == a_flag)
        {
            for (const auto& queue : queuelist)
                a_vFamily.emplace_back(queue.QueueFamily);
        }
    }
}

VkEngineDevice::VkEngineDevice(const VkInstance a_vkInstanceHandle, const VkPhysicalDevice a_physical, 
    const VkDevice a_logical, const QueueConfMap& a_queueConf) : VkEngineObject{ a_vkInstanceHandle, a_logical }
    , m_physical{ a_physical }
{
    // Memory properties are used regularly for creating all kinds of buffers
    vkGetPhysicalDeviceMemoryProperties(a_physical, &m_memProp);
    for (const auto& [flag, list] : a_queueConf)
    {
        for (const auto& queueConf : list)
        {
            if (const auto iter = m_Queues.find(queueConf.QueueFamily); iter != m_Queues.cend())
            {
                iter->second.addQueue(queueConf.QueueCount);
            }
            else
            {
                m_Queues.emplace(queueConf.QueueFamily, queueConf.QueueCount);
            }
        }
    }
}

VkEngineDevice::~VkEngineDevice()
{
    vkDestroyDevice(m_device, nullptr);
}

std::shared_ptr<VkSwapChain> VkEngineDevice::createSwapChain(const VkSwapChainConf& a_configuration)
{
    // use new instead of std::make_shared because ctor is private
   return std::shared_ptr<VkSwapChain>(new VkSwapChain(weak_from_this(), a_configuration));
}

std::shared_ptr<VkEngineCommandQueue>  VkEngineDevice::createCommandQueue(const uint32_t a_familyIndex)const
{
    if(const auto iter = m_Queues.find(a_familyIndex); iter != m_Queues.cend())
        return m_Queues.at(a_familyIndex).createCommandQueue(m_device, a_familyIndex);
    return nullptr;
}

std::shared_ptr<VkEngineImage> VkEngineDevice::createImage(const VkImageCreateInfo& a_imageInfo)
{
    // use new instead of std::make_shared because ctor is private
    return std::shared_ptr<VkEngineImage>(new VkEngineImage(weak_from_this(), a_imageInfo));
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


uint32_t VkEngineDevice::getMemoryType(const uint32_t a_typeBits, const VkMemoryPropertyFlags a_properties, VkBool32* a_memTypeFound) const
{
    for (uint32_t iMemIndex = 0; iMemIndex < m_memProp.memoryTypeCount; iMemIndex++)
    {
        uint32_t mask = 1 << iMemIndex;
        if ((a_typeBits & mask) == mask && 
            (m_memProp.memoryTypes[iMemIndex].propertyFlags & a_properties) == a_properties)
        {
            if (a_memTypeFound)
            {
                *a_memTypeFound = true;
            }
            return iMemIndex;
        }
    }

    if (a_memTypeFound)
    {
        *a_memTypeFound = false;
        return 0;
    }
    else
    {
        throw std::runtime_error("Could not find a matching memory type");
    }
}
