#pragma once
/***********************************************
* @headerfile vk_check.h
* @date 21 / 03 / 2024
* @author Roomain
************************************************/
#include "VkException.h"

#define VK_CHECK(CALLING_FUN) \
if(VkResult result = CALLING_FUN; result != VK_SUCCESS) \
	throw VkException(result, std::source_location::current());
