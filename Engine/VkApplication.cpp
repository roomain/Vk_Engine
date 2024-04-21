#include "pch.h"
#include "VkApplication.h"
#include "vk_initializers.h"
#include "vk_check.h"
#include "IRHICapabilitiesDisplayer.h"
#include "vk_enumToString.h"


VkApplication::VkApplication(const std::string_view a_appName, const int a_version)
{
	VkApplicationInfo appInfo = gen_applicationInfo();
	appInfo.pApplicationName = a_appName.data();
	appInfo.pEngineName = "VulkanEngine";
	appInfo.applicationVersion = a_version;

	VkInstanceCreateInfo instanceInfo = gen_instanceCreateInfo();
	instanceInfo.pApplicationInfo = &appInfo;

	std::vector<const char*> vLayers;
	/*std::transform(a_conf.instanceExtProps.cbegin(), a_conf.instanceExtProps.cend(), std::back_inserter(vLayers),
		[](const auto& ext) {return ext.c_str(); });*/
	vLayers.emplace_back(VK_EXT_VALIDATION_FLAGS_EXTENSION_NAME);
	instanceInfo.ppEnabledLayerNames = vLayers.data();
	instanceInfo.enabledLayerCount = static_cast<uint32_t>(vLayers.size());

	std::vector<const char*> vExtension;
	/*std::transform(a_conf.instanceExtProps.cbegin(), a_conf.instanceExtProps.cend(), std::back_inserter(vExtension),
		[](const auto& ext) {return ext.c_str(); });*/
	vExtension.emplace_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	vExtension.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	instanceInfo.ppEnabledExtensionNames = vExtension.data();
	instanceInfo.enabledExtensionCount = static_cast<uint32_t>(vExtension.size());
	// todo
	//VK_CHECK(vkCreateInstance())
	// todo
}

VkApplication::~VkApplication()
{
	// release all resources 
	
	// release all devices
	m_devices.clear();

	if (m_vulkanInstance != VK_NULL_HANDLE)
	{
		vkDestroyInstance(m_vulkanInstance, nullptr);
		// todo
	}
}

VkEngineDevicePtr VkApplication::createDevice(const int a_devIndex)
{
	//todo
}

void VkApplication::displayInstanceCapabilities(IRHICapabilitiesDisplayer& a_displayer)
{
	uint32_t numLayer;
	vkEnumerateInstanceLayerProperties(&numLayer, nullptr);
	std::vector<VkLayerProperties> vLayers{ numLayer };
	vkEnumerateInstanceLayerProperties(&numLayer, vLayers.data());
	a_displayer.pushCategory("Instance layers");
	for (const auto& layer : vLayers)
	{
		a_displayer.pushCategory(layer.layerName);
		a_displayer.setCapability("description", layer.description);
		a_displayer.setCapability("version", layer.specVersion);
		a_displayer.popCategory();
	}
	a_displayer.popCategory();


	uint32_t numExtension;
	vkEnumerateInstanceExtensionProperties(nullptr, &numExtension, nullptr);
	std::vector<VkExtensionProperties> vExtensions{ numExtension };
	vkEnumerateInstanceExtensionProperties(nullptr, &numExtension, vExtensions.data());
	a_displayer.pushCategory("Instance extensions");
	for (const auto& extend : vExtensions)
	{
		a_displayer.pushCategory(extend.extensionName);
		a_displayer.setCapability("version", extend.specVersion);
		a_displayer.popCategory();
	}
	a_displayer.popCategory();
}

void VkApplication::displayDevicesCapabilities(IRHICapabilitiesDisplayer& a_displayer)const
{
	if (m_vulkanInstance != VK_NULL_HANDLE)
	{
		uint32_t numDevices;
		vkEnumeratePhysicalDevices(m_vulkanInstance, &numDevices, nullptr);
		std::vector<VkPhysicalDevice> vDevices{ numDevices };
		vkEnumeratePhysicalDevices(m_vulkanInstance, &numDevices, vDevices.data());
		for (const auto& device : vDevices)
		{	
			VkPhysicalDeviceProperties prop;
			vkGetPhysicalDeviceProperties(device, &prop);
			a_displayer.pushCategory(prop.deviceName);
			a_displayer.setCapability("device type", to_string(prop.deviceType));
			a_displayer.setCapability("device id", prop.deviceID);
			a_displayer.setCapability("vendor id", prop.vendorID);
			a_displayer.setCapability("api version", prop.apiVersion);
			a_displayer.setCapability("driver version", prop.driverVersion);

			a_displayer.pushCategory("Sparse properties");
			a_displayer.setCapability("residency standard 2D block shape", prop.sparseProperties.residencyStandard2DBlockShape);
			a_displayer.setCapability("residency standard 2D multisample block", prop.sparseProperties.residencyStandard2DMultisampleBlockShape);
			a_displayer.setCapability("residency standard 3D block shape", prop.sparseProperties.residencyStandard3DBlockShape);
			a_displayer.setCapability("residency aligned mip size", prop.sparseProperties.residencyAlignedMipSize);
			a_displayer.setCapability("residency non resident strict", prop.sparseProperties.residencyNonResidentStrict);
			a_displayer.popCategory();

			a_displayer.pushCategory("limits");
            a_displayer.setCapability("max image dimension 1D", prop.limits.maxImageDimension1D);
            a_displayer.setCapability("max image dimension 2D", prop.limits.maxImageDimension2D);
            a_displayer.setCapability("max image dimension 3D", prop.limits.maxImageDimension3D);
            a_displayer.setCapability("max image dimension cube", prop.limits.maxImageDimensionCube);
            a_displayer.setCapability("max image array layers", prop.limits.maxImageArrayLayers);
            a_displayer.setCapability("max texel buffer elements", prop.limits.maxTexelBufferElements);
            a_displayer.setCapability("max uniform buffer range", prop.limits.maxUniformBufferRange);
            a_displayer.setCapability("max storage buffer range", prop.limits.maxStorageBufferRange);
            a_displayer.setCapability("max push constant size", prop.limits.maxPushConstantsSize);
            a_displayer.setCapability("max memory allocation count", prop.limits.maxMemoryAllocationCount);
            a_displayer.setCapability("max sampler allocation count", prop.limits.maxSamplerAllocationCount);
            a_displayer.setCapability("buffer image granularityt", prop.limits.bufferImageGranularity);
            a_displayer.setCapability("sparse address space size", prop.limits.sparseAddressSpaceSize);
            a_displayer.setCapability("rmax bound descriptor sets", prop.limits.maxBoundDescriptorSets);
            a_displayer.setCapability("max per stage descriptor samplers", prop.limits.maxPerStageDescriptorSamplers);
            a_displayer.setCapability("max Per Stage Descriptor Uniform Buffers", prop.limits.maxPerStageDescriptorUniformBuffers);
            a_displayer.setCapability("max Per Stage Descriptor Storage Buffers", prop.limits.maxPerStageDescriptorStorageBuffers);
            a_displayer.setCapability("max Per Stage Descriptor Sampled Images", prop.limits.maxPerStageDescriptorSampledImages);
            a_displayer.setCapability("max Per Stage Descriptor Storage Images", prop.limits.maxPerStageDescriptorStorageImages);
            a_displayer.setCapability("max Per Stage Descriptor Input Attachments", prop.limits.maxPerStageDescriptorInputAttachments);
            a_displayer.setCapability("max Per Stage Resources", prop.limits.maxPerStageResources);
            a_displayer.setCapability("max Descriptor Set Samplers", prop.limits.maxDescriptorSetSamplers);
            a_displayer.setCapability("max Descriptor Set Uniform Buffers", prop.limits.maxDescriptorSetUniformBuffers);
            a_displayer.setCapability("max Descriptor Set Uniform Buffers Dynamic", prop.limits.maxDescriptorSetUniformBuffersDynamic);
            a_displayer.setCapability("max Descriptor Set Storage Buffers", prop.limits.maxDescriptorSetStorageBuffers);
            a_displayer.setCapability("", prop.limits.maxDescriptorSetStorageBuffersDynamic);
            a_displayer.setCapability("", prop.limits.maxDescriptorSetSampledImages);
            a_displayer.setCapability("", prop.limits.maxDescriptorSetStorageImages);
            a_displayer.setCapability("", prop.limits.maxDescriptorSetInputAttachments);
            a_displayer.setCapability("", prop.limits.maxVertexInputAttributes);
            a_displayer.setCapability("", prop.limits.maxVertexInputBindings);
            a_displayer.setCapability("", prop.limits.maxVertexInputAttributeOffset);
            a_displayer.setCapability("", prop.limits.maxVertexInputBindingStride);
            a_displayer.setCapability("", prop.limits.maxVertexOutputComponents);
            a_displayer.setCapability("", prop.limits.maxTessellationGenerationLevel);
            a_displayer.setCapability("", prop.limits.maxTessellationPatchSize);
            a_displayer.setCapability("", prop.limits.maxTessellationControlPerVertexInputComponents);
            a_displayer.setCapability("", prop.limits.maxTessellationControlPerVertexOutputComponents);
            a_displayer.setCapability("", prop.limits.maxTessellationControlPerPatchOutputComponents);
            a_displayer.setCapability("", prop.limits.maxTessellationControlTotalOutputComponents);
            a_displayer.setCapability("", prop.limits.maxTessellationEvaluationInputComponents);
            a_displayer.setCapability("", prop.limits.maxTessellationEvaluationOutputComponents);
            a_displayer.setCapability("", prop.limits.maxGeometryShaderInvocations);
            a_displayer.setCapability("", prop.limits.maxGeometryInputComponents);
            a_displayer.setCapability("", prop.limits.maxGeometryOutputComponents);
            a_displayer.setCapability("", prop.limits.maxGeometryOutputVertices);
            a_displayer.setCapability("", prop.limits.maxGeometryTotalOutputComponents);
            a_displayer.setCapability("", prop.limits.maxFragmentInputComponents);
            a_displayer.setCapability("", prop.limits.maxFragmentOutputAttachments);
            a_displayer.setCapability("", prop.limits.maxFragmentDualSrcAttachments);
            a_displayer.setCapability("", prop.limits.maxFragmentCombinedOutputResources);
            a_displayer.setCapability("", prop.limits.maxComputeSharedMemorySize);
            a_displayer.setCapability("max Compute Work Group Count [0]", prop.limits.maxComputeWorkGroupCount[0]);
            a_displayer.setCapability("max Compute Work Group Count [1]", prop.limits.maxComputeWorkGroupCount[1]);
            a_displayer.setCapability("max Compute Work Group Count [2]", prop.limits.maxComputeWorkGroupCount[2]);
            a_displayer.setCapability("", prop.limits.maxComputeWorkGroupInvocations);
            a_displayer.setCapability("max Compute Work Group Size [0]", prop.limits.maxComputeWorkGroupSize[0]);
            a_displayer.setCapability("max Compute Work Group Size [1]", prop.limits.maxComputeWorkGroupSize[1]);
            a_displayer.setCapability("max Compute Work Group Size [2]", prop.limits.maxComputeWorkGroupSize[2]);
            a_displayer.setCapability("", prop.limits.subPixelPrecisionBits);
            a_displayer.setCapability("", prop.limits.subTexelPrecisionBits);
            a_displayer.setCapability("", prop.limits.mipmapPrecisionBits);
            a_displayer.setCapability("", prop.limits.maxDrawIndexedIndexValue);
            a_displayer.setCapability("", prop.limits.maxDrawIndirectCount);
            a_displayer.setCapability("", prop.limits.maxSamplerLodBias);
            a_displayer.setCapability("", prop.limits.maxSamplerAnisotropy);
            a_displayer.setCapability("", prop.limits.maxViewports);
            a_displayer.setCapability("", prop.limits.maxViewportDimensions[0]);
            a_displayer.setCapability("", prop.limits.maxViewportDimensions[1]);
            a_displayer.setCapability("", prop.limits.viewportBoundsRange[0]);
            a_displayer.setCapability("", prop.limits.viewportBoundsRange[1]);
            a_displayer.setCapability("", prop.limits.viewportSubPixelBits);
            a_displayer.setCapability("", prop.limits.minMemoryMapAlignment);
            a_displayer.setCapability("", prop.limits.minTexelBufferOffsetAlignment);
            a_displayer.setCapability("", prop.limits.minUniformBufferOffsetAlignment);
            a_displayer.setCapability("", prop.limits.minStorageBufferOffsetAlignment);
            a_displayer.setCapability("", prop.limits.minTexelOffset);
            a_displayer.setCapability("", prop.limits.maxTexelOffset);
            a_displayer.setCapability("", prop.limits.minTexelGatherOffset);
            a_displayer.setCapability("", prop.limits.maxTexelGatherOffset);
            a_displayer.setCapability("", prop.limits.minInterpolationOffset);
            a_displayer.setCapability("", prop.limits.maxInterpolationOffset);
            a_displayer.setCapability("", prop.limits.subPixelInterpolationOffsetBits);
            a_displayer.setCapability("", prop.limits.maxFramebufferWidth);
            a_displayer.setCapability("", prop.limits.maxFramebufferHeight);
            a_displayer.setCapability("", prop.limits.maxFramebufferLayers);
            a_displayer.setCapability("", Flag<VkSampleCountFlagBits>::to_string(prop.limits.framebufferColorSampleCounts));
            a_displayer.setCapability("", Flag<VkSampleCountFlagBits>::to_string(prop.limits.framebufferDepthSampleCounts));
            a_displayer.setCapability("", Flag<VkSampleCountFlagBits>::to_string(prop.limits.framebufferStencilSampleCounts));
            a_displayer.setCapability("", Flag<VkSampleCountFlagBits>::to_string(prop.limits.framebufferNoAttachmentsSampleCounts));
            a_displayer.setCapability("", prop.limits.maxColorAttachments);
            a_displayer.setCapability("", Flag<VkSampleCountFlagBits>::to_string(prop.limits.sampledImageColorSampleCounts));
            a_displayer.setCapability("", Flag<VkSampleCountFlagBits>::to_string(prop.limits.sampledImageIntegerSampleCounts));
            a_displayer.setCapability("", Flag<VkSampleCountFlagBits>::to_string(prop.limits.sampledImageDepthSampleCounts));
            a_displayer.setCapability("", Flag<VkSampleCountFlagBits>::to_string(prop.limits.sampledImageStencilSampleCounts));
            a_displayer.setCapability("", Flag<VkSampleCountFlagBits>::to_string(prop.limits.storageImageSampleCounts));
            a_displayer.setCapability("", prop.limits.maxSampleMaskWords);
            a_displayer.setCapability("", prop.limits.timestampComputeAndGraphics);
            a_displayer.setCapability("", prop.limits.timestampPeriod);
            a_displayer.setCapability("", prop.limits.maxClipDistances);
            a_displayer.setCapability("", prop.limits.maxCullDistances);
            a_displayer.setCapability("", prop.limits.maxCombinedClipAndCullDistances);
            a_displayer.setCapability("", prop.limits.discreteQueuePriorities);
            a_displayer.setCapability("", prop.limits.pointSizeRange[2]);
            a_displayer.setCapability("", prop.limits.lineWidthRange[2]);
            a_displayer.setCapability("", prop.limits.pointSizeGranularity);
            a_displayer.setCapability("", prop.limits.lineWidthGranularity);
            a_displayer.setCapability("", prop.limits.strictLines);
            a_displayer.setCapability("", prop.limits.standardSampleLocations);
            a_displayer.setCapability("", prop.limits.optimalBufferCopyOffsetAlignment);
            a_displayer.setCapability("", prop.limits.optimalBufferCopyRowPitchAlignment);
            a_displayer.setCapability("", prop.limits.nonCoherentAtomSize);
			//a_displayer.setCapability("", prop.);
			//a_displayer.setCapability("", prop.);
			//a_displayer.setCapability("", prop.);
			a_displayer.popCategory();

			VkPhysicalDeviceFeatures feature;
			vkGetPhysicalDeviceFeatures(device, &feature);
			//a_displayer.pushCategory(feature.);
			// todo
			a_displayer.popCategory();
		}
	}	
}