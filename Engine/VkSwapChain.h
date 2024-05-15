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

using VkCreateSurface = std::function<void (VkInstance, VkSurfaceKHR*)>;


struct VkSwapChainConf
{
	VkCreateSurface CreationCb;					/*!< surface creation callback*/
	VkExtent2D Extent{ 0,0 };					/*!< current window extent*/
	bool UseVSync = false;						/*!< use Vertical synchro*/
	VkFormat ColorFormat = VK_FORMAT_UNDEFINED;	/*!< desired color format*/
};

class VkEngineDevice;

using VkEngineDeviceWPtr = std::weak_ptr<VkEngineDevice>;
using VkEngineDevicePtr = std::shared_ptr<VkEngineDevice>;

class ENGINE_EXPORT VkSwapChain
{
protected:
	VkSwapchainKHR m_swapChain = VK_NULL_HANDLE;	/*!< vulkan swapchain*/
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;		/*!< vulkan surface*/
	VkEngineDeviceWPtr m_device;			/*!< associated device*/

	VkCreateSurface m_createFun;					/*!< vullkan surface creation callback*/
	bool m_useVSync = true;							/*!< use vsync*/

	static VkCompositeAlphaFlagBitsKHR findBestCompisiteAlphaFlag(const VkSurfaceCapabilitiesKHR& surfCaps);
	static void findBestColorFormat(const VkEngineDevicePtr& a_device, const VkSurfaceKHR& a_surface, VkFormat& a_colorFormat, VkColorSpaceKHR& a_colorSpace);
	static VkPresentModeKHR findBestPresentMode(const VkEngineDevicePtr& a_device, const VkSurfaceKHR& a_surface, const bool a_useVSync);

	VkSwapChain(const VkEngineDeviceWPtr& a_device, const VkSwapChainConf& a_configuration);
public:
	~VkSwapChain();
	void update(const VkExtent2D& a_extent);
};

