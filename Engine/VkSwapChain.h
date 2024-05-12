#pragma once
/***********************************************
* @headerfile VkSwapChain.h
* @date 04 / 05 / 2024
* @author Roomain
************************************************/
#include <functional>
#include <vulkan/vulkan.hpp>
#include "VkEngineDevice.h"
#include "vk_engine_globals.h"

using VkCreateSurface = std::function<void (VkInstance, VkSurfaceKHR*)>;

class ENGINE_EXPORT VkSwapChain
{
protected:
	VkInstance m_vulkanInstance = VK_NULL_HANDLE;	/*!< vulkan instance*/
	VkSwapchainKHR m_swapChain = VK_NULL_HANDLE;	/*!< vulkan swapchain*/
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;		/*!< vulkan surface*/
	VkPhysicalDevice m_physical = VK_NULL_HANDLE;	/*!< physical device*/
	VkCreateSurface m_createFun;					/*!< vullkan surface creation callback*/

	VkSwapChain(const VkInstance a_vkInstance, const VkPhysicalDevice a_device, const VkCreateSurface& a_createFun);
public:
	~VkSwapChain();
	void update(const uint32_t a_width, const uint32_t a_height);
};

