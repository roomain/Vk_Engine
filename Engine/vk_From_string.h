#pragma once
/***********************************************
* @headerfile vk_From_string.h
* @date 27 / 04 / 2024
* @author Roomain
************************************************/
#include "From_string.h"
#include "vk_stringToEnum.h"

template<>
inline bool from_string(VkObjectType& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkPipelineCacheHeaderVersion& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkVendorId& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkSystemAllocationScope& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkInternalAllocationType& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkFormat& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkImageTiling& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkImageType& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkPhysicalDeviceType& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkQueryType& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkSharingMode& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkComponentSwizzle& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkImageViewType& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkBlendFactor& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkBlendOp& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkCompareOp& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkDynamicState& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkFrontFace& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkVertexInputRate& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkPrimitiveTopology& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkPolygonMode& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkStencilOp& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkLogicOp& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkBorderColor& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkFilter& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkSamplerAddressMode& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkSamplerMipmapMode& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkDescriptorType& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkAttachmentLoadOp& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkAttachmentStoreOp& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkPipelineBindPoint& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkCommandBufferLevel& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkIndexType& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkSubpassContents& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

template<>
inline bool from_string(VkQueueFlagBits& a_data, const std::string& a_value)
{
	return string_to_enum(a_value, a_data);
}

/*template<>
inline bool from_string(VkAccessFlags& a_data, const std::string& a_value)
{
	return FlagInput<VkAccessFlagBits>::string_to_flag(a_value, a_data);
}

template<>
inline bool from_string(VkImageAspectFlags& a_data, const std::string& a_value)
{
	return FlagInput<VkImageAspectFlagBits>::string_to_flag(a_value, a_data);
}

template<>
inline bool from_string(VkFormatFeatureFlags& a_data, const std::string& a_value)
{
	return FlagInput<VkFormatFeatureFlagBits>::string_to_flag(a_value, a_data);
}

template<>
inline bool from_string(VkImageCreateFlags& a_data, const std::string& a_value)
{
	return FlagInput<VkImageCreateFlagBits>::string_to_flag(a_value, a_data);
}

template<>
inline bool from_string(VkSampleCountFlags& a_data, const std::string& a_value)
{
	return FlagInput<VkSampleCountFlagBits>::string_to_flag(a_value, a_data);
}

template<>
inline bool from_string(VkImageUsageFlags& a_data, const std::string& a_value)
{
	return FlagInput<VkImageUsageFlagBits>::string_to_flag(a_value, a_data);
}

*/