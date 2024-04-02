#include "vk_Exception.h"
#include <format>

std::string VkException::toString(const VkResult& a_error)
{
	std::string message{ "Unknown" };
	switch (a_error)
	{
#define VK_ERROR_DESC(error, desc) \
		case error:\
			message = #error;\
		break;

#include "vk_enumToString.h"
#undef VK_ERROR_DESC
	default:
		break;
	}
	return message;
}

std::string VkException::errorDescription(const VkResult& a_error)
{
	std::string message{ "Unknown" };
	switch (a_error)
	{
#define VK_ERROR_DESC(error, desc) \
		case error:\
			message = desc;\
		break;

#include "vk_enumToString.h"
#undef VK_ERROR_DESC
	default:
		break;
	}
	return message;
}

VkException::VkException(const VkResult& a_error, const std::source_location& a_loc) : 
	std::exception(VkException::errorDescription(a_error).c_str()), m_vkError{ a_error }, m_srcLoc{ a_loc }
{
	//
}

std::string VkException::message()const noexcept
{
	return std::format("Error: {}\nFile: {}\nLine: {}\nFunction: {}\nDescription: {}\n",
		VkException::toString(m_vkError), m_srcLoc.file_name(), m_srcLoc.line(), m_srcLoc.function_name(),
		VkException::errorDescription(m_vkError));
}