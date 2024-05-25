#include "pch.h"
#include <algorithm>
#include "VkQueueStack.h"
#include "VkEngineCommandQueue.h"

VkQueueStack::VkQueueStack(const unsigned int a_queueCount) : m_queueStack(a_queueCount)
{
	//
}

bool VkQueueStack::isFull()const noexcept
{
	return !std::any_of(m_queueStack.cbegin(), m_queueStack.cend(), 
		[](const auto& cmdQueue) {return cmdQueue.expired(); });
}

void VkQueueStack::addQueue(const uint32_t a_appendCount)
{
	m_queueStack.resize(m_queueStack.size() + a_appendCount);
}

VkEngineCommandQueuePtr VkQueueStack::createCommandQueue(const VkDevice a_device, const uint32_t a_familyIndex)
{
	for (auto& cmdQueue : m_queueStack)
	{
		if (cmdQueue.expired())
		{
			// use new instead of std::make_shared because ctor is private
			std::shared_ptr<VkEngineCommandQueue> newQueue(new VkEngineCommandQueue(a_device, a_familyIndex));
			cmdQueue = newQueue;
			return newQueue;
		}
	}
	return VkEngineCommandQueuePtr();
}
