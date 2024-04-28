#include "pch.h"
#include "VkException.h"
#include <format>
#include "vk_enumToString.h"

std::string VkException::errorDescription(const VkResult& a_error)
{
	return to_string(a_error);
}

VkException::VkException(const VkResult& a_error, const std::source_location& a_loc) : 
	std::exception(VkException::errorDescription(a_error).c_str()), m_srcLoc{ a_loc }, m_vkError{ a_error }
{
	//
}

std::string VkException::message()const noexcept
{
	return std::format("Error: {}\nFile: {}\nLine: {}\nFunction: {}\nDescription: {}\n",
		to_string(m_vkError), m_srcLoc.file_name(), m_srcLoc.line(), m_srcLoc.function_name(),
		VkException::errorDescription(m_vkError));
}
