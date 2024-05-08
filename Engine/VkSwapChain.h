#pragma once
/***********************************************
* @headerfile VkSwapChain.h
* @date 04 / 05 / 2024
* @author Roomain
************************************************/
#include <functional>
#include <vulkan/vulkan.hpp>
#include "vk_engine_globals.h"

using VkCreateSurface = std::function<void (VkInstance, VkSurfaceKHR*)>;

class ENGINE_EXPORT VkSwapChain
{
protected:
	VkSwapchainKHR m_swapChain = VK_NULL_HANDLE;	/*!< vulkan swapchain*/
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;		/*!< vulkan surface*/

public:
	void setup(VkCreateSurface a_create);
};

