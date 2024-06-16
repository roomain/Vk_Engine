#pragma once
/***********************************************
* @headerfile VkEngineFrameBufferAttachment.h
* @date 16 / 06 / 2024
* @author Roomain
************************************************/
#include "vk_engine_globals.h"
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
	VkFormat imgFormat;
	TransitionLayout transition;
	AttachmentOperator colorOp;
	AttachmentOperator depthOp;
};

class ENGINE_EXPORT VkEngineFrameBufferAttachment : public DataMatrix<VkImageView, VkAttachmentDescription, VkAttachmentReference>
{
public:
	void appendColorAttachment(const VkImageView a_imgView, const AttachmentDesc& a_imgAttachDesc, const VkImageLayout a_refLayout);
	void update(const VkImageView a_imgView, const size_t& a_index);
};
