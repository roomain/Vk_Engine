#pragma once
/***********************************************
* @headerfile VkCapabilityNode.h
* @date 19 / 03 / 2024
* @author Roomain
************************************************/
#include <source_location>
#include <exception>
#include <string>
#include "vulkan/vulkan_core.h"
#include "vk_engine_globals.h"


/*@brief Provides exception for vulkan*/
class ENGINE_EXPORT VkException : public std::exception
{
private:
	std::source_location m_srcLoc;
	VkResult m_vkError;

	static std::string errorDescription(const VkResult& a_error);

public:
	VkException() = delete;
	explicit VkException(const VkResult& a_error, const std::source_location& a_loc);
	std::string message()const noexcept;
};

#define check_vulkan(a_fun)\
if(VkResult result = a_fun; result != VK_SUCCESS) \
	throw VkException(result, std::source_location::current());
