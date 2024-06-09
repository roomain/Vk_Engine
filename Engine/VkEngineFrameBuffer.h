#pragma once
/***********************************************
* @headerfile VkEngineFrameBuffer.h
* @date 26 / 05 / 2024
* @author Roomain
************************************************/
#include <map>
#include "VkImageInterface.h"

using VkImageMap = std::map< VkImageUsageFlags, VkImageInterfacePtr>;

class VkEngineDevice;
using VkEngineDeviceWPtr = std::weak_ptr<VkEngineDevice>;

/*@brief vulkan engine frame buffer*/
class VkEngineFrameBuffer
{
private:
	VkFramebuffer m_frameBuffer = VK_NULL_HANDLE;	/*!< vulkan frame buffer*/
	VkImageMap m_attachment;						/*!< image attachment*/
	VkFramebufferCreateInfo m_info;					/*!< frame buffer create info*/
	VkEngineDeviceWPtr m_device;					/*!< associated device*/

public:
	~VkEngineFrameBuffer();
	void attach(const VkImageUsageFlags& a_flag, const VkImageInterfacePtr& a_image);
	void update();
	[[nodiscard]] VkImageInterfacePtr attachment(const VkImageUsageFlags& a_flag)const noexcept;
	[[nodiscard]] constexpr VkFramebuffer frameBuffer()const { return m_frameBuffer; }
	/*Attachement iteration*/
	VkImageMap::const_iterator cbegin()const noexcept { return m_attachment.cbegin(); }
	VkImageMap::const_iterator cend()const noexcept { return m_attachment.cend(); }
};

