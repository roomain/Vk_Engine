#include "pch.h"
#include "VkSwapChainImage.h"
#include "VkSwapChain.h"

void VkSwapChainImage::update(const VkImage a_image, VkImageView a_imageView)
{
	m_image = a_image;
	m_imageView = a_imageView;
}

VkSwapChainImage::VkSwapChainImage(const VkImage a_image, VkImageView a_imageView, const uint32_t a_index, const VkSwapChainWPtr& a_swapchain) :
	VkImageInterface{ a_image, a_imageView },
	m_imageIndex{ a_index }, m_swapChain{ a_swapchain }
{
	//
}

uint32_t VkSwapChainImage::width() const noexcept
{
	uint32_t width = 0;
	if (auto swapChain = m_swapChain.lock())
		width = swapChain->imageExtent().width;
	return width;
}

uint32_t VkSwapChainImage::height() const noexcept
{
	uint32_t height = 0;
	if (auto swapChain = m_swapChain.lock())
		height = swapChain->imageExtent().height;
	return height;
}

uint32_t VkSwapChainImage::depth() const noexcept
{
	return 1;
}

VkFormat VkSwapChainImage::format() const noexcept
{
	if (auto swapChain = m_swapChain.lock())
		return swapChain->imageFormat();
	return VkFormat::VK_FORMAT_UNDEFINED;
}
