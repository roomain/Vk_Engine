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



#include "VkEngineFrameBufferAttachment.h"

class ENGINE_EXPORT VkEngineFrameBuffer : public VkEngineFrameBufferAttachment
{
private:
	VkFramebuffer m_frameBuffer = VK_NULL_HANDLE;	/*!< vulkan frame buffer*/
	VkFramebufferCreateInfo m_info;					/*!< frame buffer create info*/
	VkEngineDeviceWPtr m_device;					/*!< associated device*/

public:
	~VkEngineFrameBuffer();
	void update();
	[[nodiscard]] constexpr VkFramebuffer frameBuffer()const { return m_frameBuffer; }

};