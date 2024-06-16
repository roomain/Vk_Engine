#include "pch.h"
#include "VkEngineFrameBufferAttachment.h"


void VkEngineFrameBufferAttachment::appendColorAttachment(const VkImageView a_imgView, const AttachmentDesc& a_imgAttachDesc, const VkImageLayout a_refLayout)
{
	auto& vImgView = row<VkImageView>();
	vImgView.emplace_back(a_imgView);

	auto& vDesc = row<VkAttachmentDescription>();
	vDesc.emplace_back(VkAttachmentDescription{
		.flags = 0,
		.format = a_imgAttachDesc.imgFormat,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.loadOp = a_imgAttachDesc.colorOp.loadOperator,
		.storeOp = a_imgAttachDesc.colorOp.storeOperator,
		.stencilLoadOp = a_imgAttachDesc.depthOp.loadOperator,
		.stencilStoreOp = a_imgAttachDesc.depthOp.storeOperator,
		.initialLayout = a_imgAttachDesc.transition.initialLayout,
		.finalLayout = a_imgAttachDesc.transition.finalLayout
	});


	auto& vRef = row<VkAttachmentReference>();
	vRef.emplace_back(VkAttachmentReference{
		.attachment = static_cast<uint32_t>(vDesc.size() - 1),
		.layout = a_refLayout
	});
}

void VkEngineFrameBufferAttachment::update(const VkImageView a_imgView, const size_t& a_index)
{
	auto& vImgView = row<VkImageView>();
	vImgView[a_index] = a_imgView;
}
