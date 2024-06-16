#pragma once
/***********************************************
* @headerfile VkEngineFrameBufferAttachment.h
* @date 16 / 06 / 2024
* @author Roomain
************************************************/
#include "DataMatrix.h"
#include "vulkan/vulkan.hpp"

struct AttachmentOperator
{
	VkAttachmentLoadOp loadOperator = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	VkAttachmentStoreOp storeOperator = VK_ATTACHMENT_STORE_OP_DONT_CARE;
};

struct TransitionLayout
{
	VkImageLayout initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	VkImageLayout finalLayout = VK_IMAGE_LAYOUT_UNDEFINED;
};

struct AttachmentDesc
{
	TransitionLayout transition;
	AttachmentOperator colorOp;
	AttachmentOperator depthOp;
};

class VkEngineFrameBufferAttachment : public DataMatrix<VkImageView, VkAttachmentDescription, VkAttachmentReference>
{
public:
	void appendColorAttachment(const VkImageView a_imgView, const VkFormat a_imgFormat, const AttachmentDesc& a_imgAttachDesc);
	void appendDepthAttachment(const VkImageView a_imgView, const AttachmentDesc& a_imgAttachDesc);
};
