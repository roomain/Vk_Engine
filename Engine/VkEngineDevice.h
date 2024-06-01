#pragma once
/***********************************************
* @headerfile VkEngineDevice.h
* @date 20 / 04 / 2024
* @author Roomain
************************************************/
#include <memory>
#include <unordered_map>
#include <vulkan/vulkan.hpp>
#include "VkQueueStack.h"
#include "vk_deviceInfo.h"
#include "VkEngineObject.h"
#include "vk_engine_globals.h"

#pragma warning(push)
#pragma warning(disable : 4251)

struct VkSwapChainConf;
struct VKDeviceSettings;
class VkApplication;
class VkSwapChain;
class VkEngineImage;

using QueueStackMap = std::unordered_map<uint32_t, VkQueueStack>;

/*@brief vulkan device*/
class ENGINE_EXPORT VkEngineDevice : public VkEngineObject, public std::enable_shared_from_this<VkEngineDevice>
{
	friend VkApplication;
	friend VkSwapChain;

private:
	VkPhysicalDevice m_physical = VK_NULL_HANDLE;	/*!< physical device that vulkan will use*/
	VkPhysicalDeviceMemoryProperties m_memProp;		/*!< device memory properties*/
	mutable QueueStackMap m_Queues;

	explicit VkEngineDevice(const VkInstance a_vkInstanceHandle, const VkPhysicalDevice a_physical, 
		const VkDevice a_logical, const QueueConfMap& a_queueConf);
	
public:	
	VkEngineDevice() = delete;
	~VkEngineDevice() override;
	[[nodiscard]] constexpr bool isValid()const { return m_device != VK_NULL_HANDLE; }

	// check device compatibility
	static [[nodiscard]] bool checkDeviceLayers(VkPhysicalDevice a_device, const std::vector<std::string>& a_desiredLayers);
	static [[nodiscard]] bool checkDeviceExtension(VkPhysicalDevice a_device, const std::vector<std::string>& a_desiredExts);

	//Get the index of a memory type that has all the requested property bits set
	[[nodiscard]] uint32_t getMemoryType(const uint32_t typeBits, const VkMemoryPropertyFlags properties, VkBool32* memTypeFound = nullptr)const;
	
	/*@brief get queue having flag*/
	static void getQueueFamilies(const VKDeviceInfo& a_info, const VkQueueFlags a_flag, std::vector<uint32_t>& a_vFamily);

	[[nodiscard]] std::shared_ptr<VkSwapChain> createSwapChain(const VkSwapChainConf& a_configuration);
	[[nodiscard]] std::shared_ptr<VkEngineCommandQueue> createCommandQueue(const uint32_t a_familyIndex)const;

	// create frame buffer

	//create image
	[[nodiscard]] std::shared_ptr<VkEngineImage> createImage(const VkImageCreateInfo& a_imageInfo);
	 

	// create fence

	// create semaphore

	// wait device idle
	void waitForDeviceIdle();

};

using VkEngineDevicePtr = std::shared_ptr<VkEngineDevice>;

#pragma warning(pop)