#pragma once
/***********************************************
* @headerfile VkSwapChain.h
* @date 04 / 05 / 2024
* @author Roomain
************************************************/
#include <functional>
#include <vulkan/vulkan.hpp>
#include "VkEngineDevice.h"
#include "vk_engine_globals.h"

#pragma warning(push)
#pragma warning(disable : 4251)

using VkCreateSurface = std::function<void (VkInstance, VkSurfaceKHR*)>;


struct VkSwapChainConf
{
	VkCreateSurface CreationCb;					/*!< surface creation callback*/
	VkExtent2D Extent{ 0,0 };					/*!< current window extent*/
	bool UseVSync = false;						/*!< use Vertical synchro*/
	VkFormat ColorFormat = VK_FORMAT_UNDEFINED;	/*!< desired color format*/
};


struct VkSwpaChainBuffer
{
	VkImage image;		/*!< link to swapchain image*/
	VkImageView view;	/*!< view of image*/
};

using ImgeBufferStack = std::vector<VkSwpaChainBuffer>;

class VkEngineDevice;

using VkEngineDeviceWPtr = std::weak_ptr<VkEngineDevice>;
using VkEngineDevicePtr = std::shared_ptr<VkEngineDevice>;

class ENGINE_EXPORT VkSwapChain
{
	friend class VkEngineDevice;

private:
	VkSwapchainKHR m_swapChain = VK_NULL_HANDLE;	/*!< vulkan swapchain*/
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;		/*!< vulkan surface*/
	VkEngineDeviceWPtr m_device;					/*!< associated device*/

	ImgeBufferStack m_bufferStack;					/*!< image buffer stack*/


	VkCreateSurface m_createFun;					/*!< vullkan surface creation callback*/
	bool m_useVSync = true;							/*!< use vsync*/

	static VkCompositeAlphaFlagBitsKHR findBestCompisiteAlphaFlag(const VkSurfaceCapabilitiesKHR& surfCaps);
	static void findBestColorFormat(const VkEngineDevicePtr& a_device, const VkSurfaceKHR& a_surface, VkFormat& a_colorFormat, VkColorSpaceKHR& a_colorSpace);
	static VkPresentModeKHR findBestPresentMode(const VkEngineDevicePtr& a_device, const VkSurfaceKHR& a_surface, const bool a_useVSync);
	void realeaseSwapchain(VkEngineDevicePtr a_device, VkSwapchainKHR& a_swapchain);
	
	explicit VkSwapChain(const VkEngineDeviceWPtr& a_device, const VkSwapChainConf& a_configuration);

public:
	VkSwapChain() = delete;
	~VkSwapChain();
	void update(const VkExtent2D& a_extent);

	/*@brief acquire next image of swapchain*/
	void aquireNextImage(VkSemaphore a_presentCompleteSemaphore, uint32_t& a_imageIndex, VkFence a_fence = nullptr)const;
	/*@brief enqueue present image*/
	VkResult queuePresentImage(VkQueue a_queue, const uint32_t a_imageIndex, VkSemaphore a_semaphore)const;
	uint32_t imageStackCount() const noexcept { return static_cast<uint32_t>(m_bufferStack.size()); }
};

using VkSwapChainPtr = std::shared_ptr<VkSwapChain>;

#pragma warning(pop)