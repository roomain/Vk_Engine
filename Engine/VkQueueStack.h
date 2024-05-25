#pragma once
/***********************************************
* @headerfile VkQueueStack.h
* @date 25 / 05 / 2024
* @author Roomain
************************************************/
#include <memory>
#include <vector>
#include "vulkan/vulkan.hpp"

class VkEngineCommandQueue;
using VkEngineCommandQueuePtr = std::shared_ptr<VkEngineCommandQueue>;
using VkEngineCommandQueueWPtr = std::weak_ptr<VkEngineCommandQueue>;

/*@brief queue stack*/
class VkQueueStack
{
private:
	std::vector<VkEngineCommandQueueWPtr> m_queueStack;	/*!< stack of used queue*/
public:
	VkQueueStack() = delete;
	explicit VkQueueStack(const unsigned int a_queueCount);
	~VkQueueStack() = default;
	void addQueue(const uint32_t a_appendCount);
	bool isFull()const noexcept;
	VkEngineCommandQueuePtr createCommandQueue(const VkDevice a_device, const uint32_t a_familyIndex);
};