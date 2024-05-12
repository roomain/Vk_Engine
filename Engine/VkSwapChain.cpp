#include "pch.h"
#include "VkSwapChain.h"

VkSwapChain::VkSwapChain(const VkInstance a_vkInstance, const VkPhysicalDevice a_device, const VkCreateSurface& a_createFun) : m_vulkanInstance{ a_vkInstance }, m_physical{ a_device }, m_createFun{ a_createFun }
{
	//
}

VkSwapChain::~VkSwapChain()
{
	if (m_surface)
	{
		// release surface
		vkDestroySurfaceKHR(m_vulkanInstance, m_surface, nullptr);
	}
}

void VkSwapChain::update(const uint32_t a_width, const uint32_t a_height)
{
	if (m_createFun && (m_surface == VK_NULL_HANDLE))
	{
		m_createFun(m_vulkanInstance, &m_surface);
		// todo
	}
}