#pragma once
/***********************************************
* @headerfile VkEngineObject.h
* @date 26 / 05 / 2024
* @author Roomain
************************************************/
#include <vector>
#include <vulkan/vulkan.hpp>
#include "vk_engine_globals.h"

/*@brief base engine object*/
class ENGINE_EXPORT VkEngineObject
{
protected:
	VkInstance m_vulkanInstance = VK_NULL_HANDLE;	/*!< vulkan instance*/
	VkDevice m_device = VK_NULL_HANDLE;				/*!< vulkan logical device*/

public:
	VkEngineObject() = delete;
	explicit VkEngineObject(const VkInstance a_vkInstanceHandle, const VkDevice a_device);
	virtual ~VkEngineObject() = default;
	[[nodiscard]] VkFence createFence()const;
	[[nodiscard]] std::vector<VkFence> createFences(const uint32_t a_count)const;
	[[nodiscard]] VkSemaphore createSemaphore()const;
	[[nodiscard]] std::vector<VkSemaphore> createSemaphores(const uint32_t a_count)const;
	[[nodiscard]] constexpr VkDevice device()const noexcept { return m_device; }
	[[nodiscard]] constexpr VkInstance instance()const noexcept { return m_vulkanInstance; }
};