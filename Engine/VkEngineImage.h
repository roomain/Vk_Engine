#pragma once
/***********************************************
* @headerfile VkEngineImage.h
* @date 26 / 05 / 2024
* @author Roomain
************************************************/
#include <memory>
#include "VkImageInterface.h"

class VkEngineDevice;

#pragma warning(push)
#pragma warning(disable : 4251)



/*@brief represents an image manually created*/
class ENGINE_EXPORT VkEngineImage : public VkImageInterface
{
	friend VkEngineDevice;
private:
	VkDeviceMemory m_memory = VK_NULL_HANDLE;			/*!< image memory*/
	VkImageCreateInfo m_createInfo;						/*!< image create info (contains size, format etc.)*/
	std::weak_ptr<VkEngineDevice> m_device;				/*!< device which belong image*/
	VkImageAspectFlags m_aspect = VK_IMAGE_ASPECT_NONE;	/*!< image view aspect*/

	VkEngineImage(const std::weak_ptr<VkEngineDevice>& a_device, const VkImageCreateInfo& a_imageInfo);

	static void release(VkEngineImage& a_image);
	static void createImage(VkEngineImage& a_image);
	static bool createView(VkEngineImage& a_image, const VkImageAspectFlags a_aspectFlag);

public:
	VkEngineImage() = delete;
	virtual ~VkEngineImage();
	void reset();
	[[nodiscard]] bool createView(const VkImageAspectFlags a_aspectFlag);
	[[nodiscard]] constexpr uint32_t width() const noexcept final { return m_createInfo.extent.width; }
	[[nodiscard]] constexpr uint32_t height() const noexcept final { return m_createInfo.extent.height; }
	[[nodiscard]] constexpr uint32_t depth() const noexcept final { return m_createInfo.extent.depth; }
	[[nodiscard]] constexpr VkFormat format() const noexcept final { return m_createInfo.format; }
};

#pragma warning(pop)