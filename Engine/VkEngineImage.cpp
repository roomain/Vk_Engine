#include "pch.h"
#include "VkEngineImage.h"
#include "VkEngineDevice.h"

VkEngineImage::VkEngineImage(const std::weak_ptr<VkEngineDevice>& a_device, const VkImageCreateInfo& a_imageInfo)
	: m_createInfo{ a_imageInfo }, m_device{ a_device }
{
	VkEngineImage::createImage(*this);
}

void VkEngineImage::release(VkEngineImage& a_image)
{
	if (auto pDevice = a_image.m_device.lock(); pDevice)
	{
		auto vkDev = pDevice->device();
		vkDestroyImageView(vkDev, a_image.m_imageView, nullptr);
		vkDestroyImage(vkDev, a_image.m_image, nullptr);
		vkFreeMemory(vkDev, a_image.m_memory, nullptr);
	}
}

void VkEngineImage::createImage(VkEngineImage& a_image)
{
	if (auto pDevice = a_image.m_device.lock(); pDevice)
	{
		auto vkDev = pDevice->device();
		VK_CHECK(vkCreateImage(vkDev, &a_image.m_createInfo, nullptr, &a_image.m_image));
		VkMemoryRequirements memReqs{};
		vkGetImageMemoryRequirements(vkDev, a_image.m_image, &memReqs);

		VkMemoryAllocateInfo memAllloc{};
		memAllloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		memAllloc.allocationSize = memReqs.size;
		memAllloc.memoryTypeIndex = pDevice->getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		VK_CHECK(vkAllocateMemory(vkDev, &memAllloc, nullptr, &a_image.m_memory));
		VK_CHECK(vkBindImageMemory(vkDev, a_image.m_image, a_image.m_memory, 0));
	}
}

VkEngineImage::~VkEngineImage()
{
	VkEngineImage::release(*this);
}

void VkEngineImage::reset()
{
	bool needView = m_imageView != VK_NULL_HANDLE;
	VkEngineImage::release(*this);
	VkEngineImage::createImage(*this);
	if (needView)
		VkEngineImage::createView(*this, m_aspect);
}

bool VkEngineImage::createView(VkEngineImage& a_image, const VkImageAspectFlags a_aspectFlag)
{
	bool bRet = a_image.m_imageView != VK_NULL_HANDLE;
	if (auto pDevice = a_image.m_device.lock(); pDevice && !bRet)
	{
		a_image.m_aspect = a_aspectFlag;
		VkImageViewCreateInfo viewInfo{};
		viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		viewInfo.image = a_image.m_image;
		viewInfo.format = a_image.m_createInfo.format;
		viewInfo.subresourceRange.baseMipLevel = 0;
		viewInfo.subresourceRange.levelCount = 1;
		viewInfo.subresourceRange.baseArrayLayer = 0;
		viewInfo.subresourceRange.layerCount = 1;
		viewInfo.subresourceRange.aspectMask = a_image.m_aspect;
		VK_CHECK(vkCreateImageView(pDevice->device(), &viewInfo, nullptr, &a_image.m_imageView));
		bRet = true;
	}
	return bRet;
}

bool VkEngineImage::createView(const VkImageAspectFlags a_aspectFlag)
{
	return VkEngineImage::createView(*this, a_aspectFlag);
}