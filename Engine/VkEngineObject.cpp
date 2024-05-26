#include "pch.h"
#include "VkEngineObject.h"
#include "vk_initializers.h"

VkEngineObject::VkEngineObject(const VkInstance a_vkInstanceHandle, const VkDevice a_device) : m_vulkanInstance{ a_vkInstanceHandle }, m_device{ a_device } {}

VkFence VkEngineObject::createFence()const
{
	VkFence fence;
	VkFenceCreateInfo fenceCreateInfo = init_fence(VK_FENCE_CREATE_SIGNALED_BIT);
	VK_CHECK(vkCreateFence(m_device, &fenceCreateInfo, nullptr, &fence));
	return fence;
}

std::vector<VkFence> VkEngineObject::createFences(const uint32_t a_count)const
{
	VkFenceCreateInfo fenceCreateInfo = init_fence(VK_FENCE_CREATE_SIGNALED_BIT);
	std::vector<VkFence> vFences(a_count);
	for(auto& fence : vFences)
		VK_CHECK(vkCreateFence(m_device, &fenceCreateInfo, nullptr, &fence));
	return std::move(vFences);
}

VkSemaphore VkEngineObject::createSemaphore()const
{
	VkSemaphoreCreateInfo semaphoreCreate = init_semaphore(VK_EVENT_CREATE_DEVICE_ONLY_BIT);
	VkSemaphore semaphore;
	VK_CHECK(vkCreateSemaphore(m_device, &semaphoreCreate, nullptr, &semaphore));
	return semaphore;
}

std::vector<VkSemaphore> VkEngineObject::createSemaphores(const uint32_t a_count)const
{
	VkSemaphoreCreateInfo semaphoreCreate = init_semaphore(VK_EVENT_CREATE_DEVICE_ONLY_BIT);
	std::vector<VkSemaphore> vSemaphore(a_count);
	for (auto& semaphore : vSemaphore)
		VK_CHECK(vkCreateSemaphore(m_device, &semaphoreCreate, nullptr, &semaphore));
	return std::move(vSemaphore);
}
