#include "pch.h"
#include "VkSwapChain.h"
#include "VkEngineDevice.h"
#include "vk_initializers.h"

VkSwapChain::VkSwapChain(const VkEngineDeviceWPtr& a_device, const VkSwapChainConf& a_configuration) : m_device{ a_device }, m_createFun { a_configuration.CreationCb }, m_useVSync{ a_configuration.UseVSync }
{
	update(a_configuration.Extent);
}

VkSwapChain::~VkSwapChain()
{
	auto pDevice = m_device.lock();
	if (m_surface && pDevice)
	{
		realeaseSwapchain(pDevice, m_swapChain);

		// release surface
		vkDestroySurfaceKHR(pDevice->m_vulkanInstance, m_surface, nullptr);
	}
}

void VkSwapChain::realeaseSwapchain(VkEngineDevicePtr a_device, VkSwapchainKHR& a_swapchain)
{
	if (a_swapchain != VK_NULL_HANDLE)
	{
		for(auto& buffer : m_bufferStack)
			vkDestroyImageView(a_device->m_device, buffer.view, nullptr);
		vkDestroySwapchainKHR(a_device->m_device, a_swapchain, nullptr);
	}
}

VkPresentModeKHR VkSwapChain::findBestPresentMode(const VkEngineDevicePtr& a_device, const VkSurfaceKHR& a_surface, const bool a_useVSync)
{
	uint32_t modeCount = 0;
	VK_CHECK(vkGetPhysicalDeviceSurfacePresentModesKHR(a_device->m_physical, a_surface, &modeCount, nullptr));
	std::vector<VkPresentModeKHR> presentModes(modeCount);
	VK_CHECK(vkGetPhysicalDeviceSurfacePresentModesKHR(a_device->m_physical, a_surface, &modeCount, presentModes.data()));

	// The VK_PRESENT_MODE_FIFO_KHR mode must always be present as per spec
		// This mode waits for the vertical blank ("v-sync")
	VkPresentModeKHR swapchainPresentMode = VK_PRESENT_MODE_FIFO_KHR;

	// If v-sync is not requested, try to find a mailbox mode
	// It's the lowest latency non-tearing present mode available
	if (!a_useVSync)
	{
		for (const auto& presentMode : presentModes)
		{
			if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				swapchainPresentMode = VK_PRESENT_MODE_MAILBOX_KHR;
				break;
			}

			if (presentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
			{
				swapchainPresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
			}
		}
	}
	return swapchainPresentMode;
}

void VkSwapChain::findBestColorFormat(const VkEngineDevicePtr& a_device, const VkSurfaceKHR& a_surface, VkFormat& a_colorFormat, VkColorSpaceKHR& a_colorSpace)
{
	uint32_t formatCount = 0;
	VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(a_device->m_physical, a_surface, &formatCount, nullptr));
	std::vector<VkSurfaceFormatKHR> presentFormat(formatCount);
	VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(a_device->m_physical, a_surface, &formatCount, presentFormat.data()));

	// If the surface format list only includes one entry with VK_FORMAT_UNDEFINED,
	// there is no preferred format, so we assume VK_FORMAT_B8G8R8A8_UNORM
	if (formatCount == 1 && presentFormat[0].format == VK_FORMAT_UNDEFINED)
	{
		a_colorFormat = VK_FORMAT_B8G8R8A8_UNORM;
		a_colorSpace = presentFormat[0].colorSpace;
	}
	else
	{
		bool foundUnorm = false;
		for (const auto& surfaceFormat : presentFormat)
		{
			if (surfaceFormat.format == VK_FORMAT_B8G8R8A8_UNORM)
			{
				a_colorFormat = surfaceFormat.format;
				a_colorSpace = surfaceFormat.colorSpace;
				foundUnorm = true;
				break;
			}
		}

		if (!foundUnorm)
		{
			// use first as default
			a_colorFormat = presentFormat[0].format;
			a_colorSpace = presentFormat[0].colorSpace;
		}
	}
}

VkCompositeAlphaFlagBitsKHR VkSwapChain::findBestCompisiteAlphaFlag(const VkSurfaceCapabilitiesKHR& surfCaps)
{
	VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	// Simply select the first composite alpha format available
	static const std::vector<VkCompositeAlphaFlagBitsKHR> compositeAlphaFlags = {
		VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
		VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
		VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
	};

	for (auto& compositeAlphaFlag : compositeAlphaFlags)
	{
		if (surfCaps.supportedCompositeAlpha & compositeAlphaFlag)
		{
			compositeAlpha = compositeAlphaFlag;
			break;
		};
	}

	return compositeAlpha;
}


void VkSwapChain::update(const VkExtent2D& a_extent)
{
	auto pDevice = m_device.lock();
	if (!pDevice)
		return;

	if (m_createFun && (m_surface == VK_NULL_HANDLE) )
		m_createFun(pDevice->m_vulkanInstance, &m_surface);

	VkSwapchainKHR oldSwapchain = m_swapChain;

	// Get physical device surface properties and formats
	VkSurfaceCapabilitiesKHR surfCaps;
	VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pDevice->m_physical, m_surface, &surfCaps));
	

	VkExtent2D swapchainExtent = a_extent;
	// If width (and height) equals the special value 0xFFFFFFFF, the size of the surface will be set by the swapchain
	if (surfCaps.currentExtent.width != (uint32_t)-1)
	{
		// If the surface size is defined, the swap chain size must match
		swapchainExtent = surfCaps.currentExtent;

		// Select a present mode for the swapchain
		
		// get present mode
		VkPresentModeKHR swapchainPresentMode = findBestPresentMode(pDevice, m_surface, m_useVSync);


		// Determine the number of images
		uint32_t desiredNumberOfSwapchainImages = surfCaps.minImageCount + 1;
		if ((surfCaps.maxImageCount > 0) && (desiredNumberOfSwapchainImages > surfCaps.maxImageCount))
			desiredNumberOfSwapchainImages = surfCaps.maxImageCount;

		// Find the transformation of the surface
		VkSurfaceTransformFlagsKHR preTransform;
		if (surfCaps.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
		{
			// We prefer a non-rotated transform
			preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		}
		else
		{
			preTransform = surfCaps.currentTransform;
		}

		// Find a supported composite alpha format (not all devices support alpha opaque)
		VkCompositeAlphaFlagBitsKHR compositeAlpha = VkSwapChain::findBestCompisiteAlphaFlag(surfCaps);

		VkFormat colorFormat;
		VkColorSpaceKHR colorSpace;
		findBestColorFormat(pDevice, m_surface, colorFormat, colorSpace);

		VkSwapchainCreateInfoKHR swapchainCI = gen_swapChainCreateInfo();
		swapchainCI.surface = m_surface;
		swapchainCI.minImageCount = desiredNumberOfSwapchainImages;
		swapchainCI.imageFormat = colorFormat;
		swapchainCI.imageColorSpace = colorSpace;
		swapchainCI.imageExtent = { swapchainExtent.width, swapchainExtent.height };
		swapchainCI.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		swapchainCI.preTransform = (VkSurfaceTransformFlagBitsKHR)preTransform;
		swapchainCI.imageArrayLayers = 1;
		swapchainCI.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		swapchainCI.queueFamilyIndexCount = 0;
		swapchainCI.presentMode = swapchainPresentMode;
		// Setting oldSwapChain to the saved handle of the previous swapchain aids in resource reuse and makes sure that we can still present already acquired images
		swapchainCI.oldSwapchain = oldSwapchain;
		// Setting clipped to VK_TRUE allows the implementation to discard rendering outside of the surface area
		swapchainCI.clipped = VK_TRUE;
		swapchainCI.compositeAlpha = compositeAlpha;

		// Enable transfer source on swap chain images if supported
		if (surfCaps.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_SRC_BIT) {
			swapchainCI.imageUsage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
		}

		// Enable transfer destination on swap chain images if supported
		if (surfCaps.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_DST_BIT) {
			swapchainCI.imageUsage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
		}

		VK_CHECK(vkCreateSwapchainKHR(pDevice->m_device, &swapchainCI, nullptr, &m_swapChain));

		// release old swapchain
		realeaseSwapchain(pDevice, oldSwapchain);

		// get swapchain images
		uint32_t imageCount = 0;
		VK_CHECK(vkGetSwapchainImagesKHR(pDevice->m_device, m_swapChain, &imageCount, nullptr));
		std::vector<VkImage> imageStack(imageCount);
		VK_CHECK(vkGetSwapchainImagesKHR(pDevice->m_device, m_swapChain, &imageCount, imageStack.data()));
		m_bufferStack.resize(imageCount);
		int bufferIndex = 0;
		for (auto image : imageStack)
		{
			VkImageViewCreateInfo info = gen_imageViewCreateInfo(colorFormat, image);
			m_bufferStack[bufferIndex].image = image;
			VK_CHECK(vkCreateImageView(pDevice->m_device, &info, nullptr, &m_bufferStack[bufferIndex].view));
			++bufferIndex;
		}
	}
}

void VkSwapChain::aquireNextImage(VkSemaphore a_presentCompleteSemaphore, uint32_t& a_imageIndex, VkFence a_fence)const
{
	VK_CHECK(vkAcquireNextImageKHR(m_device.lock()->m_device, m_swapChain, UINT64_MAX, a_presentCompleteSemaphore, a_fence, &a_imageIndex));
}

VkResult VkSwapChain::queuePresentImage(VkQueue a_queue, const uint32_t a_imageIndex, VkSemaphore a_semaphore)const
{
	VkPresentInfoKHR presentInfo = gen_presentInfo();
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &m_swapChain;
	presentInfo.pImageIndices = &a_imageIndex;
	// Check if a wait semaphore has been specified to wait for before presenting the image
	if (a_semaphore != VK_NULL_HANDLE)
	{
		presentInfo.pWaitSemaphores = &a_semaphore;
		presentInfo.waitSemaphoreCount = 1;
	}
	return vkQueuePresentKHR(a_queue, &presentInfo);
}