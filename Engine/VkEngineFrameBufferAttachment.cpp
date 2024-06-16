#include "pch.h"
#include "VkEngineFrameBufferAttachment.h"


void VkEngineFrameBufferAttachment::appendColorAttachment(const VkImageView a_imgView, const VkFormat a_imgFormat, const AttachmentDesc& a_imgAttachDesc)
{
	auto& vImgView = row<VkImageView>();
	vImgView.emplace_back(a_imgView);

}

void VkEngineFrameBufferAttachment::appendDepthAttachment(const VkImageView a_imgView, const AttachmentDesc& a_imgAttachDesc)
{
	//
}