#include "pch.h"
#include "VkEngineFrameBuffer.h"

VkEngineFrameBuffer::~VkEngineFrameBuffer()
{
	if (auto pDevice = m_device.lock())
	{
		if (m_frameBuffer != VK_NULL_HANDLE)
			vkDestroyFramebuffer(pDevice->device(), m_frameBuffer, nullptr);
	}
}

void VkEngineFrameBuffer::attach(const VkImageUsageFlags& a_flag, const VkImageInterfacePtr& a_image)
{
	m_attachment[a_flag] = a_image;
}

void VkEngineFrameBuffer::update()
{
	// release

	if (m_attachment.size() > 0)
	{
		m_info = init_FrameBuffer();
		m_info.renderPass = renderPass;

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
	}
}

VkImageInterfacePtr VkEngineFrameBuffer::attachment(const VkImageUsageFlags& a_flag)const noexcept
{
	if (auto iter = m_attachment.find(a_flag); iter != m_attachment.cend())
		return iter->second;
	return nullptr;
}
