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
	friend class VkQueueStack;

private:
	VkQueue m_queue = VK_NULL_HANDLE;				/*!< device queue*/
	VkDevice m_device = VK_NULL_HANDLE;				/*!< vulkan logical device*/
	VkCommandPool m_cmdPool = VK_NULL_HANDLE;		/*!< command pool*/
	uint32_t m_queueFamily;							/*!< index of queue family*/
	std::vector<VkCommandBuffer> m_cmdCmdBuffers;	/*!< command buffers*/

	explicit VkEngineCommandQueue(VkDevice a_device, const uint32_t a_family, const uint32_t a_queueIndex);
	void cleanup();

public:
	VkEngineCommandQueue() = delete;
	~VkEngineCommandQueue();
	void createCommandPool();
	// @return fist index of the new command buffers
	uint32_t createCommandBuffer(const uint32_t a_numCmdBuffer);
};

using VkEngineCommandQueuePtr = std::shared_ptr<VkEngineCommandQueue>;

#pragma warning(pop)