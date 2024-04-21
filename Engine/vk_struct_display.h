#pragma once
/***********************************************
* @headerfile vk_struct_display.h
* @date 21 / 04 / 2024
* @author Roomain
************************************************/
class IRHICapabilitiesDisplayer;
struct VkExtent2D;
struct VkExtent3D;
struct VkOffset2D;
struct VkOffset3D;
struct VkRect2D;
struct VkFormatProperties;
struct VkImageFormatProperties;
struct VkMemoryHeap;
struct VkMemoryType;
struct VkPhysicalDeviceFeatures;
struct VkPhysicalDeviceLimits;
struct VkPhysicalDeviceMemoryProperties;
struct VkPhysicalDeviceSparseProperties;
struct VkPhysicalDeviceProperties;
struct VkQueueFamilyProperties;
struct VkExtensionProperties;
struct VkLayerProperties;
struct VkMemoryRequirements;
struct VkSparseMemoryBind;
struct VkImageSubresource;
struct VkSparseImageMemoryBind;
struct VkSparseImageFormatProperties;
struct VkSparseImageMemoryRequirements;
struct VkSubresourceLayout;
struct VkComponentMapping;

void display(IRHICapabilitiesDisplayer& a_displayer, const VkExtent2D& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkExtent3D& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkOffset2D& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkOffset3D& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkRect2D& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkFormatProperties& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkImageFormatProperties& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkMemoryHeap& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkMemoryType& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkPhysicalDeviceFeatures& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkPhysicalDeviceLimits& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkPhysicalDeviceMemoryProperties& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkPhysicalDeviceSparseProperties& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkPhysicalDeviceProperties& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkQueueFamilyProperties& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkExtensionProperties& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkLayerProperties& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkMemoryRequirements& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkSparseMemoryBind& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkImageSubresource& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkSparseImageMemoryBind& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkSparseImageFormatProperties& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkSparseImageMemoryRequirements& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkSubresourceLayout& a_prop);

void display(IRHICapabilitiesDisplayer& a_displayer, const VkComponentMapping& a_prop);
