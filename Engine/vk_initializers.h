#pragma once
/***********************************************
* @headerfile vk_initializers.h
* @date 20 / 04 / 2024
* @author Roomain
************************************************/
#include <vulkan/vulkan.hpp>

/*@brief initialize structure of application*/
[[nodiscard]] constexpr VkApplicationInfo gen_applicationInfo()
{
	return VkApplicationInfo{ .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO, .pNext = nullptr, .applicationVersion = 1, .engineVersion = 1, .apiVersion = VK_API_VERSION_1_3 };
}

/*@brief initialize structure of instance*/
[[nodiscard]] constexpr VkInstanceCreateInfo gen_instanceCreateInfo()
{
	return VkInstanceCreateInfo{ .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, .pNext = nullptr, .flags = 0 };
}

/*@brief initialize debug callback create info*/
[[nodiscard]] constexpr VkDebugReportCallbackCreateInfoEXT gen_debugCallbackCreateInfo()
{
	return VkDebugReportCallbackCreateInfoEXT{ .sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT };
}

/*@brief initialize debug callback create info*/
[[nodiscard]] constexpr VkDebugUtilsMessengerCreateInfoEXT gen_messageCallbackCreateInfo()
{
	return VkDebugUtilsMessengerCreateInfoEXT{ .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT, .pNext = nullptr , .pUserData = nullptr };
}

/*@brief initialize create device*/
[[nodiscard]] constexpr VkDeviceCreateInfo gen_deviceCreateInfo()
{
	return VkDeviceCreateInfo{ .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, .pNext = nullptr };
}
