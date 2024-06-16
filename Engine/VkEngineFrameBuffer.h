#pragma once
/***********************************************
* @headerfile VkEngineFrameBuffer.h
* @date 26 / 05 / 2024
* @author Roomain
************************************************/
#include <map>
#include <optional>
#include "VkImageInterface.h"

using VkImageMap = std::map< VkImageUsageFlags, VkImageInterfacePtr>;

class VkEngineDevice;
using VkEngineDeviceWPtr = std::weak_ptr<VkEngineDevice>;

using VkAttachmentVector = std::vector<VkAttachmentReference>;
using VkAttachmentDescVector = std::vector<VkAttachmentDescription>;

class ENGINE_EXPORT VkEngineRenderPass
{
private:
	VkRenderPass m_renderPass = VK_NULL_HANDLE;				/*!< vulkan render pass*/
	VkAttachmentVector m_colorAttachments;					/*!< color attachments*/
	std::optional<VkAttachmentReference> m_depthAttachment;

public:
	[[nodiscard]] constexpr VkAttachmentVector::iterator beginColorAttachment() 
	{
		return m_colorAttachments.begin();
	}
	[[nodiscard]] constexpr VkAttachmentVector::iterator endColorAttachment()
	{
		return m_colorAttachments.end();
	}
	[[nodiscard]] VkAttachmentReference& colorAttachment(const uint32_t a_index);
	void appendColorAttachment(const uint32_t a_attachment, const VkImageLayout a_attachmentLayout);
	void removeColorAttachment(const uint32_t a_index);
	[[nodiscard]] constexpr size_t colorAttachmentCount()const noexcept { return m_colorAttachments.size(); }
	void setDepthAttachment(const uint32_t a_attachment, const VkImageLayout a_attachmentLayout);
	[[nodiscard]] std::optional<VkAttachmentReference> depthAttachment()const;
	void update();

};

// A REFAIRE !!!!!!!

/*@brief vulkan engine frame buffer*/
class ENGINE_EXPORT VkEngineFrameBuffer
{
private:
	VkFramebuffer m_frameBuffer = VK_NULL_HANDLE;	/*!< vulkan frame buffer*/
	VkImageMap m_attachment;						/*!< image attachment*/
	VkFramebufferCreateInfo m_info;					/*!< frame buffer create info*/
	VkEngineDeviceWPtr m_device;					/*!< associated device*/
	VkAttachmentDescVector m_attachDesc;			/*!< attachment description*/

public:
	~VkEngineFrameBuffer();
	void attach(const VkImageUsageFlags& a_flag, const VkImageInterfacePtr& a_image);
	void update();
	[[nodiscard]] VkImageInterfacePtr attachment(const VkImageUsageFlags& a_flag)const noexcept;
	[[nodiscard]] constexpr VkFramebuffer frameBuffer()const { return m_frameBuffer; }
	/*Attachement iteration*/
	VkImageMap::const_iterator cbegin()const noexcept { return m_attachment.cbegin(); }
	VkImageMap::const_iterator cend()const noexcept { return m_attachment.cend(); }

	// attachment descriptor
	// add
	// remove
	// update
	// count
	// iterator
};

