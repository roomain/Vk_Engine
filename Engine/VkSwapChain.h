#pragma once
/***********************************************
* @headerfile VkSwapChain.h
* @date 04 / 05 / 2024
* @author Roomain
************************************************/
#include <functional>
#include <vulkan/vulkan.hpp>
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



class VkSwapChainImage;
using VkSwapChainImagePtr = std::shared_ptr<VkSwapChainImage>;
using SwapChainImageBuffer = std::vector<VkSwapChainImagePtr>;

class VkEngineDevice;

using VkEngineDeviceWPtr = std::weak_ptr<VkEngineDevice>;
using VkEngineDevicePtr = std::shared_ptr<VkEngineDevice>;

class ENGINE_EXPORT VkSwapChain : public std::enable_shared_from_this<VkSwapChain>
{
	friend class VkEngineDevice;

private:
	VkSwapchainKHR m_swapChain = VK_NULL_HANDLE;			/*!< vulkan swapchain*/
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;				/*!< vulkan surface*/
	VkEngineDeviceWPtr m_device;							/*!< associated device*/
	VkExtent2D m_imageSize;									/*!< swapchain image size*/
	VkFormat m_imageFormat = VkFormat::VK_FORMAT_UNDEFINED;	/*!< swapchain image format*/
	SwapChainImageBuffer m_imageStack;						/*!< swapchain image stack*/

	VkCreateSurface m_createFun;							/*!< vullkan surface creation callback*/
	bool m_useVSync = true;									/*!< use vsync*/

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
	[[nodiscard]] VkResult queuePresentImage(VkQueue a_queue, const uint32_t a_imageIndex, VkSemaphore a_semaphore)const;
	[[nodiscard]] uint32_t imageStackCount() const noexcept { return static_cast<uint32_t>(m_imageStack.size()); }
	[[nodiscard]] constexpr VkExtent2D imageExtent()const noexcept { return m_imageSize; }
	[[nodiscard]] constexpr VkFormat imageFormat()const noexcept { return m_imageFormat; }
	[[nodiscard]] VkSwapChainImagePtr image(const uint32_t a_index)const noexcept;
};

using VkSwapChainPtr = std::shared_ptr<VkSwapChain>;

#pragma warning(pop)