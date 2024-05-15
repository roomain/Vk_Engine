#include "pch.h"
#include <ranges>
#include <algorithm>
#include "VkEngineDevice.h"
#include "vk_check.h"
#include "vk_parameters.h"
#include "vk_initializers.h"

VkEngineDevice::VkEngineDevice(const VkInstance a_vkInstanceHandle, const VkPhysicalDevice a_physical, const VkDevice a_logical, const QueueConfMap& a_queueInfo) :
    m_vulkanInstance{ a_vkInstanceHandle }, m_physical{ a_physical }, m_device{ a_logical }
{
    for (const auto& [flag, list] : a_queueInfo)
    {
        for (const auto& conf : list)
            m_queueMap[flag].emplace_back(QueueInfo{ conf.QueueFamily, conf.QueueCount });
    }
}

VkEngineDevice::~VkEngineDevice()
{
    vkDestroyDevice(m_device, nullptr);
}

std::shared_ptr<VkSwapChain> VkEngineDevice::createSwapChain(const uint32_t a_width, const uint32_t a_height, const bool a_vSync)
{
    std::shared_ptr<VkSwapChain> pSwapChain;
    //todo
    return pSwapChain;
}

bool VkEngineDevice::createCommandPool(const VkQueueFlags a_Queueflag)
{
    if (auto iter = m_queueMap.find(a_Queueflag); iter != m_queueMap.cend())
    {
        size_t CmdpoolCount = commandPoolCount(a_Queueflag);
        for (const auto& queueInfo : iter->second)
        {
            if (CmdpoolCount == 0)
            {
                VkCommandPoolCreateInfo cmdPoolInfo = gen_cmdPoolCreateInfo();
                cmdPoolInfo.queueFamilyIndex = queueInfo.QueueFamily;
                cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
                VkCommandPool cmdPool;
                VK_CHECK(vkCreateCommandPool(m_device, &cmdPoolInfo, nullptr, &cmdPool));
                m_cmdPools[a_Queueflag].emplace_back(cmdPool);
                return true;
            }
            else
            {
                CmdpoolCount -= queueInfo.QueueCount;
            }
        }
    }
    return false;
   
}

int VkEngineDevice::createCommandsPool(const VkQueueFlags a_Queueflag, const int a_numToCreate)
{
    if (auto iter = m_queueMap.find(a_Queueflag); iter != m_queueMap.cend())
    {
        int counter = 0;
        size_t CmdpoolCount = commandPoolCount(a_Queueflag);
        for (const auto& queueInfo : iter->second)
        {
            if (CmdpoolCount == 0 && counter < a_numToCreate)
            {
                VkCommandPoolCreateInfo cmdPoolInfo = gen_cmdPoolCreateInfo();
                cmdPoolInfo.queueFamilyIndex = queueInfo.QueueFamily;
                cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
                VkCommandPool cmdPool;
                VK_CHECK(vkCreateCommandPool(m_device, &cmdPoolInfo, nullptr, &cmdPool));
                m_cmdPools[a_Queueflag].emplace_back(cmdPool);
                ++counter;

                if (counter >= a_numToCreate)
                    return counter;
            }
            else
            {
                CmdpoolCount -= queueInfo.QueueCount;
            }
        }
    }
    return 0;
}

size_t VkEngineDevice::commandPoolCount(const VkQueueFlags a_Queueflag) const
{
    if (auto iter = m_cmdPools.find(a_Queueflag); iter != m_cmdPools.cend())
    {
        return iter->second.size();
    }
    return 0;
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