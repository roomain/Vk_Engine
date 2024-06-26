#include "pch.h"
#include "VkEngineFrameBuffer.h"

VkAttachmentReference& VkEngineRenderPass::colorAttachment(const uint32_t a_index)
{
	return m_colorAttachments[a_index];
}

void VkEngineRenderPass::appendColorAttachment(const uint32_t a_attachment, const VkImageLayout a_attachmentLayout)
{
	m_colorAttachments.push_back(VkAttachmentReference{
		.attachment = a_attachment,
		.layout = a_attachmentLayout });
}

void VkEngineRenderPass::removeColorAttachment(const uint32_t a_index)
{
	if (m_colorAttachments.size() > a_index)
		m_colorAttachments.erase(m_colorAttachments.begin() + a_index);
}


void VkEngineRenderPass::setDepthAttachment(const uint32_t a_attachment, const VkImageLayout a_attachmentLayout)
{
	m_depthAttachment = VkAttachmentReference{
		.attachment = a_attachment,
		.layout = a_attachmentLayout };
}

std::optional<VkAttachmentReference> VkEngineRenderPass::depthAttachment()const
{
	return m_depthAttachment;
}

void VkEngineRenderPass::update()
{
	// todo
}


VkEngineFrameBuffer::~VkEngineFrameBuffer()
{
	if (auto pDevice = m_device.lock())
	{
		if (m_frameBuffer != VK_NULL_HANDLE)
			vkDestroyFramebuffer(pDevice->device(), m_frameBuffer, nullptr);
	}
}


void VkEngineFrameBuffer::update()
{
	// release

	/*if (m_attachment.size() > 0 && m_renderPass != VK_NULL_HANDLE)
	{
		m_info = init_FrameBuffer();
		m_info.renderPass = m_renderPass;

		std::vector<VkImageView> attachments(m_attachment.size());
		int index = 0;
		for (const auto& [flag, image] : m_attachment)
		{
			attachments[index] = image->imageView();
			++index;
		}
		m_info.attachmentCount = static_cast<uint32_t>(attachments.size());
		m_info.pAttachments = attachments.data();

		m_info.width = m_attachment.begin()->second->width();
		m_info.height = m_attachment.begin()->second->height();
		m_info.layers = 1;

		VkDevice device = VK_NULL_HANDLE;
		if (auto pDevice = m_device.lock())
			device = pDevice->device();

		VK_CHECK(vkCreateFramebuffer(device, &m_info, nullptr, &m_frameBuffer));
	}*/
}
