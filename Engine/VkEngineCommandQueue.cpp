#include "pch.h"
#include "VkEngineCommandQueue.h"
#include "vk_initializers.h"

void VkEngineCommandQueue::createCommandPool()
{
    if (m_cmdPool == VK_NULL_HANDLE)
    {
        VkCommandPoolCreateInfo cmdPoolInfo = gen_cmdPoolCreateInfo();
        cmdPoolInfo.queueFamilyIndex = m_queueFamily;
        cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        VK_CHECK(vkCreateCommandPool(m_device, &cmdPoolInfo, nullptr, &m_cmdPool));
    }
}

uint32_t VkEngineCommandQueue::createCommandBuffer(const uint32_t a_numCmdBuffer)
{
    auto index = static_cast<uint32_t>(m_cmdCmdBuffers.size());
    m_cmdCmdBuffers.resize(index + a_numCmdBuffer);
    VkCommandBufferAllocateInfo cmdBufAllocateInfo = gen_allocCmdBufferInfo(m_cmdPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, a_numCmdBuffer);
    VK_CHECK(vkAllocateCommandBuffers(m_device, &cmdBufAllocateInfo, m_cmdCmdBuffers.data() + index));
    return index;
}

void VkEngineCommandQueue::cleanup()
{
    if (m_cmdPool != VK_NULL_HANDLE)
    {
        if(!m_cmdCmdBuffers.empty())
            vkFreeCommandBuffers(m_device, m_cmdPool, static_cast<uint32_t>(m_cmdCmdBuffers.size()), m_cmdCmdBuffers.data());
        vkDestroyCommandPool(m_device, m_cmdPool, nullptr);
    }
}

VkEngineCommandQueue::VkEngineCommandQueue(VkDevice a_device, const uint32_t a_family, const uint32_t a_queueIndex) : m_device{ a_device }, m_queueFamily{ a_family }
{
    vkGetDeviceQueue(a_device, a_family, a_queueIndex, &m_queue);
}

VkEngineCommandQueue::~VkEngineCommandQueue()
{
    cleanup();
}