#pragma once
/***********************************************
* @headerfile VkEngineImage.h
* @date 26 / 05 / 2024
* @author Roomain
************************************************/
#include<vulkan/vulkan.hpp>

/*@brief represents an image*/
class VkEngineImage
{
private:
	VkImage m_image = VK_NULL_HANDLE;				/*!< image data*/
	VkDeviceMemory m_memory = VK_NULL_HANDLE;		/*!< image memory*/
	VkImageView m_imageView = VK_NULL_HANDLE;		/*!< image view*/
	VkImageCreateInfo m_createInfo;					/*!< image create info (contains size, format etc.)*/

	
public:
	VkEngineImage() = delete;
	virtual ~VkEngineImage();
	[[nodiscard]] constexpr uint32_t width() const noexcept { return m_createInfo.extent.width; }
	[[nodiscard]] constexpr uint32_t height() const noexcept { return m_createInfo.extent.height; }
	[[nodiscard]] constexpr uint32_t depth() const noexcept { return m_createInfo.extent.depth; }
	[[nodiscard]] constexpr uint32_t depth() const noexcept { return m_createInfo.extent.depth; }
	[[nodiscard]] constexpr VkFormat format() const noexcept { return m_createInfo.format; }
};
