#pragma once
/***********************************************
* @headerfile VkSwapChainImage.h
* @date 26 / 05 / 2024
* @author Roomain
************************************************/
#include <memory>
#include "VkImageInterface.h"

class VkSwapChain;
using VkSwapChainWPtr = std::weak_ptr<VkSwapChain>;

#pragma warning(push)
#pragma warning(disable : 4251)

class ENGINE_EXPORT VkSwapChainImage : public VkImageInterface
{
	friend VkSwapChain;
private:
	uint32_t m_imageIndex;			/*!< image index in swapchain*/
	VkSwapChainWPtr m_swapChain;	/*!< parent swapchain*/

	void update(const VkImage a_image, VkImageView a_imageView);
	VkSwapChainImage(const VkImage a_image, VkImageView a_imageView, const uint32_t a_index, const VkSwapChainWPtr& a_swapchain);

public:
	VkSwapChainImage() = delete;
	~VkSwapChainImage()override = default;
	[[nodiscard]] uint32_t width() const noexcept final;
	[[nodiscard]] uint32_t height() const noexcept final;
	[[nodiscard]] uint32_t depth() const noexcept final;
	[[nodiscard]] VkFormat format() const noexcept final;
};