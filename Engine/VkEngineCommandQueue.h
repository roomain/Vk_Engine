#pragma once
/***********************************************
* @headerfile VkEngineCommandQueue.h
* @date 19 / 05 / 2024
* @author Roomain
************************************************/
#include <memory>
#include <vulkan/vulkan.hpp>
#include "vk_engine_globals.h"

#pragma warning(push)
#pragma warning(disable : 4251)


/*@brief Queue management*/
class ENGINE_EXPORT VkEngineCommandQueue
{
	friend class VkEngineDevice;

private:
	VkDevice m_device = VK_NULL_HANDLE;				/*!< vulkan logical device*/
	uint32_t m_queueFamily;							/*!< index of queue family*/
	VkCommandPool m_cmdPool = VK_NULL_HANDLE;		/*!< command pool*/
	std::vector<VkCommandBuffer> m_cmdCmdBuffers;	/*!< command buffers*/

	explicit VkEngineCommandQueue(VkDevice a_device, const uint32_t a_family);
	void cleanup();

public:
	VkEngineCommandQueue() = delete;
	~VkEngineCommandQueue();
	void createCommandPool();
	// @return fist index of the new commansd buffers
	uint32_t createCommandBuffer(const uint32_t a_numCmdBuffer);
};

using VkEngineCommandQueuePtr = std::shared_ptr<VkEngineCommandQueue>;

#pragma warning(pop)