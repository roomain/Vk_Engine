#include "pch.h"
#include "vk_struct_display.h"
#include <vulkan/vulkan.hpp>
#include "vk_enumToString.h"
#include "IRHICapabilitiesDisplayer.h"

void display(IRHICapabilitiesDisplayer& a_displayer, const VkExtent2D& a_prop)
{
	a_displayer.setCapability("width", a_prop.width);
	a_displayer.setCapability("height", a_prop.height);
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkExtent3D& a_prop)
{
	a_displayer.setCapability("width", a_prop.width);
	a_displayer.setCapability("height", a_prop.height);
	a_displayer.setCapability("depth", a_prop.depth);
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkOffset2D& a_prop)
{
	a_displayer.setCapability("x", a_prop.x);
	a_displayer.setCapability("y", a_prop.y);
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkOffset3D& a_prop)
{
	a_displayer.setCapability("x", a_prop.x);
	a_displayer.setCapability("y", a_prop.y);
	a_displayer.setCapability("z", a_prop.z);
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkRect2D& a_prop)
{
	a_displayer.pushCategory("offset");
	display(a_displayer, a_prop.offset);
	a_displayer.popCategory();
	a_displayer.pushCategory("extent");
	display(a_displayer, a_prop.extent);
	a_displayer.popCategory();
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkFormatProperties& a_prop)
{
	a_displayer.setCapability("linear Tiling Features", Flag<VkFormatFeatureFlagBits>::to_string(a_prop.linearTilingFeatures));
	a_displayer.setCapability("optimal Tiling Features", Flag<VkFormatFeatureFlagBits>::to_string(a_prop.optimalTilingFeatures));
	a_displayer.setCapability("buffer Features", Flag<VkFormatFeatureFlagBits>::to_string(a_prop.bufferFeatures));
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkImageFormatProperties& a_prop)
{
	a_displayer.pushCategory("max Extent");
	display(a_displayer, a_prop.maxExtent);
	a_displayer.popCategory();
	a_displayer.setCapability("max Mip Levels", a_prop.maxMipLevels);
	a_displayer.setCapability("max Array Layers", a_prop.maxArrayLayers);
	a_displayer.setCapability("sample Counts", Flag<VkSampleCountFlagBits>::to_string(a_prop.sampleCounts));
	a_displayer.setCapability("max Resource Size", a_prop.maxResourceSize);
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkMemoryHeap& a_prop)
{
	a_displayer.setCapability("size", a_prop.size);
	a_displayer.setCapability("flags", Flag<VkMemoryHeapFlagBits>::to_string(a_prop.flags));
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkMemoryType& a_prop)
{
	a_displayer.setCapability("property Flags", Flag<VkMemoryPropertyFlagBits>::to_string(a_prop.propertyFlags));
	a_displayer.setCapability("heap Index", a_prop.heapIndex);
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkPhysicalDeviceFeatures& a_prop)
{
	a_displayer.setCapability("robust Buffer Access", a_prop.robustBufferAccess);
	a_displayer.setCapability("full Draw Index Uint32", a_prop.fullDrawIndexUint32);
	a_displayer.setCapability("image Cube Array", a_prop.imageCubeArray);
	a_displayer.setCapability("independent Blend", a_prop.independentBlend);
	a_displayer.setCapability("geometry Shader", a_prop.geometryShader);
	a_displayer.setCapability("tessellation Shader", a_prop.tessellationShader);
	a_displayer.setCapability("sample Rate Shading", a_prop.sampleRateShading);
	a_displayer.setCapability("dual Src Blend", a_prop.dualSrcBlend);
	a_displayer.setCapability("logic Op", a_prop.logicOp);
	a_displayer.setCapability("multi Draw Indirect", a_prop.multiDrawIndirect);
	a_displayer.setCapability("draw Indirect First Instance", a_prop.drawIndirectFirstInstance);
	a_displayer.setCapability("depth Clamp", a_prop.depthClamp);
	a_displayer.setCapability("depth Bias Clamp", a_prop.depthBiasClamp);
	a_displayer.setCapability("fill Mode Non Solid", a_prop.fillModeNonSolid);
	a_displayer.setCapability("depth Bounds", a_prop.depthBounds);
	a_displayer.setCapability("wide Lines", a_prop.wideLines);
	a_displayer.setCapability("large Points", a_prop.largePoints);
	a_displayer.setCapability("alpha To One", a_prop.alphaToOne);
	a_displayer.setCapability("multi Viewport", a_prop.multiViewport);
	a_displayer.setCapability("sampler Anisotropy", a_prop.samplerAnisotropy);
	a_displayer.setCapability("texture Compression ET C2", a_prop.textureCompressionETC2);
	a_displayer.setCapability("texture CompressionA ST C_L DR", a_prop.textureCompressionASTC_LDR);
	a_displayer.setCapability("texture Compression BC", a_prop.textureCompressionBC);
	a_displayer.setCapability("occlusion Query Precise", a_prop.occlusionQueryPrecise);
	a_displayer.setCapability("pipeline Statistics Query", a_prop.pipelineStatisticsQuery);
	a_displayer.setCapability("vertex Pipeline Stores And Atomics", a_prop.vertexPipelineStoresAndAtomics);
	a_displayer.setCapability("fragment Stores And Atomics", a_prop.fragmentStoresAndAtomics);
	a_displayer.setCapability("shader Tessellation And Geometry Point Size", a_prop.shaderTessellationAndGeometryPointSize);
	a_displayer.setCapability("shader Image Gather Extended", a_prop.shaderImageGatherExtended);
	a_displayer.setCapability("shader Storage Image Extended Formats", a_prop.shaderStorageImageExtendedFormats);
	a_displayer.setCapability("shader Storage Image Multisample", a_prop.shaderStorageImageMultisample);
	a_displayer.setCapability("shader Storage Image Read Without Format", a_prop.shaderStorageImageReadWithoutFormat);
	a_displayer.setCapability("shader Storage Image Write Without Format", a_prop.shaderStorageImageWriteWithoutFormat);
	a_displayer.setCapability("shader Uniform Buffer Array Dynamic Indexing", a_prop.shaderUniformBufferArrayDynamicIndexing);
	a_displayer.setCapability("shader Sampled Image Array Dynamic Indexing", a_prop.shaderSampledImageArrayDynamicIndexing);
	a_displayer.setCapability("shader Storage Buffer Array Dynamic Indexing", a_prop.shaderStorageBufferArrayDynamicIndexing);
	a_displayer.setCapability("shader Storage Image Array Dynamic Indexing", a_prop.shaderStorageImageArrayDynamicIndexing);
	a_displayer.setCapability("shader Clip Distance", a_prop.shaderClipDistance);
	a_displayer.setCapability("shader Cull Distance", a_prop.shaderCullDistance);
	a_displayer.setCapability("shader Float64", a_prop.shaderFloat64);
	a_displayer.setCapability("shader Int64", a_prop.shaderInt64);
	a_displayer.setCapability("shader Int16", a_prop.shaderInt16);
	a_displayer.setCapability("shader Resource Residency", a_prop.shaderResourceResidency);
	a_displayer.setCapability("shader Resource Min Lod", a_prop.shaderResourceMinLod);
	a_displayer.setCapability("sparse Binding", a_prop.sparseBinding);
	a_displayer.setCapability("sparse Residency Buffer", a_prop.sparseResidencyBuffer);
	a_displayer.setCapability("sparse Residency Image2D", a_prop.sparseResidencyImage2D);
	a_displayer.setCapability("sparse Residency Image3D", a_prop.sparseResidencyImage3D);
	a_displayer.setCapability("sparse Residency2 Samples", a_prop.sparseResidency2Samples);
	a_displayer.setCapability("sparse Residency4 Samples", a_prop.sparseResidency4Samples);
	a_displayer.setCapability("sparse Residency8 Samples", a_prop.sparseResidency8Samples);
	a_displayer.setCapability("sparse Residency16 Samples", a_prop.sparseResidency16Samples);
	a_displayer.setCapability("sparse Residency Aliased", a_prop.sparseResidencyAliased);
	a_displayer.setCapability("variable Multisample Rate", a_prop.variableMultisampleRate);
	a_displayer.setCapability("inherited Queries", a_prop.inheritedQueries);
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkPhysicalDeviceLimits& a_prop)
{
	a_displayer.setCapability("max Image Dimension1D", a_prop.maxImageDimension1D);
	a_displayer.setCapability("max Image Dimension2D", a_prop.maxImageDimension2D);
	a_displayer.setCapability("max Image Dimension3D", a_prop.maxImageDimension3D);
	a_displayer.setCapability("max Image Dimension Cube", a_prop.maxImageDimensionCube);
	a_displayer.setCapability("max Image Array Layers", a_prop.maxImageArrayLayers);
	a_displayer.setCapability("max Texel Buffer Elements", a_prop.maxTexelBufferElements);
	a_displayer.setCapability("max Uniform Buffer Range", a_prop.maxUniformBufferRange);
	a_displayer.setCapability("max Storage Buffer Range", a_prop.maxStorageBufferRange);
	a_displayer.setCapability("max Push Constants Size", a_prop.maxPushConstantsSize);
	a_displayer.setCapability("max Memory Allocation Count", a_prop.maxMemoryAllocationCount);
	a_displayer.setCapability("max Sampler Allocation Count", a_prop.maxSamplerAllocationCount);
	a_displayer.setCapability("buffer Image Granularity", a_prop.bufferImageGranularity);
	a_displayer.setCapability("sparse Address Space Size", a_prop.sparseAddressSpaceSize);
	a_displayer.setCapability("max Bound Descriptor Sets", a_prop.maxBoundDescriptorSets);
	a_displayer.setCapability("max Per Stage Descriptor Samplers", a_prop.maxPerStageDescriptorSamplers);
	a_displayer.setCapability("max Per Stage Descriptor Uniform Buffers", a_prop.maxPerStageDescriptorUniformBuffers);
	a_displayer.setCapability("max Per Stage Descriptor Storage Buffers", a_prop.maxPerStageDescriptorStorageBuffers);
	a_displayer.setCapability("max Per Stage Descriptor Sampled Images", a_prop.maxPerStageDescriptorSampledImages);
	a_displayer.setCapability("max Per Stage Descriptor Storage Images", a_prop.maxPerStageDescriptorStorageImages);
	a_displayer.setCapability("max Per Stage Descriptor Input Attachments", a_prop.maxPerStageDescriptorInputAttachments);
	a_displayer.setCapability("max Per Stage Resources", a_prop.maxPerStageResources);
	a_displayer.setCapability("max Descriptor Set Samplers", a_prop.maxDescriptorSetSamplers);
	a_displayer.setCapability("max Descriptor Set Uniform Buffers", a_prop.maxDescriptorSetUniformBuffers);
	a_displayer.setCapability("max Descriptor Set Uniform Buffers Dynamic", a_prop.maxDescriptorSetUniformBuffersDynamic);
	a_displayer.setCapability("max Descriptor Set Storage Buffers", a_prop.maxDescriptorSetStorageBuffers);
	a_displayer.setCapability("max Descriptor Set Storage Buffers Dynamic", a_prop.maxDescriptorSetStorageBuffersDynamic);
	a_displayer.setCapability("max Descriptor Set Sampled Images", a_prop.maxDescriptorSetSampledImages);
	a_displayer.setCapability("max Descriptor Set Storage Images", a_prop.maxDescriptorSetStorageImages);
	a_displayer.setCapability("max Descriptor Set Input Attachments", a_prop.maxDescriptorSetInputAttachments);
	a_displayer.setCapability("max Vertex Input Attributes", a_prop.maxVertexInputAttributes);
	a_displayer.setCapability("max Vertex Input Bindings", a_prop.maxVertexInputBindings);
	a_displayer.setCapability("max Vertex Input Attribute Offset", a_prop.maxVertexInputAttributeOffset);
	a_displayer.setCapability("max Vertex Input Binding Stride", a_prop.maxVertexInputBindingStride);
	a_displayer.setCapability("max Vertex Output Components", a_prop.maxVertexOutputComponents);
	a_displayer.setCapability("max Tessellation Generation Level", a_prop.maxTessellationGenerationLevel);
	a_displayer.setCapability("max Tessellation Patch Size", a_prop.maxTessellationPatchSize);
	a_displayer.setCapability("max Tessellation Control Per Vertex Input Components", a_prop.maxTessellationControlPerVertexInputComponents);
	a_displayer.setCapability("max Tessellation Control Per Vertex Output Components", a_prop.maxTessellationControlPerVertexOutputComponents);
	a_displayer.setCapability("max Tessellation Control Per Patch Output Components", a_prop.maxTessellationControlPerPatchOutputComponents);
	a_displayer.setCapability("max Tessellation Control Total Output Components", a_prop.maxTessellationControlTotalOutputComponents);
	a_displayer.setCapability("max Tessellation Evaluation Input Components", a_prop.maxTessellationEvaluationInputComponents);
	a_displayer.setCapability("max Tessellation Evaluation Output Components", a_prop.maxTessellationEvaluationOutputComponents);
	a_displayer.setCapability("max Geometry Shader Invocations", a_prop.maxGeometryShaderInvocations);
	a_displayer.setCapability("max Geometry Input Components", a_prop.maxGeometryInputComponents);
	a_displayer.setCapability("max Geometry Output Components", a_prop.maxGeometryOutputComponents);
	a_displayer.setCapability("max Geometry Output Vertices", a_prop.maxGeometryOutputVertices);
	a_displayer.setCapability("max Geometry Total Output Components", a_prop.maxGeometryTotalOutputComponents);
	a_displayer.setCapability("max Fragment Input Components", a_prop.maxFragmentInputComponents);
	a_displayer.setCapability("max Fragment Output Attachments", a_prop.maxFragmentOutputAttachments);
	a_displayer.setCapability("max Fragment Dual Src Attachments", a_prop.maxFragmentDualSrcAttachments);
	a_displayer.setCapability("max Fragment Combined Output Resources", a_prop.maxFragmentCombinedOutputResources);
	a_displayer.setCapability("max Compute Shared Memory Size", a_prop.maxComputeSharedMemorySize);
	for (const auto propVal : a_prop.maxComputeWorkGroupCount)
	{
		a_displayer.setCapability("max Compute Work Group Count", propVal);
	}

	a_displayer.setCapability("max Compute Work Group Invocations", a_prop.maxComputeWorkGroupInvocations);
	for (const auto propVal : a_prop.maxComputeWorkGroupSize)
	{
		a_displayer.setCapability("max Compute Work Group Size", propVal);
	}

	a_displayer.setCapability("sub Pixel Precision Bits", a_prop.subPixelPrecisionBits);
	a_displayer.setCapability("sub Texel Precision Bits", a_prop.subTexelPrecisionBits);
	a_displayer.setCapability("mipmap Precision Bits", a_prop.mipmapPrecisionBits);
	a_displayer.setCapability("max Draw Indexed Index Value", a_prop.maxDrawIndexedIndexValue);
	a_displayer.setCapability("max Draw Indirect Count", a_prop.maxDrawIndirectCount);
	a_displayer.setCapability("max Sampler Lod Bias", a_prop.maxSamplerLodBias);
	a_displayer.setCapability("max Sampler Anisotropy", a_prop.maxSamplerAnisotropy);
	a_displayer.setCapability("max Viewports", a_prop.maxViewports);
	for (const auto propVal : a_prop.maxViewportDimensions)
	{
		a_displayer.setCapability("max Viewport Dimensions", propVal);
	}

	for (const auto propVal : a_prop.viewportBoundsRange)
	{
		a_displayer.setCapability("viewport Bounds Range", propVal);
	}

	a_displayer.setCapability("viewport Sub Pixel Bits", a_prop.viewportSubPixelBits);
	a_displayer.setCapability("min Memory Map Alignment", a_prop.minMemoryMapAlignment);
	a_displayer.setCapability("min Texel Buffer Offset Alignment", a_prop.minTexelBufferOffsetAlignment);
	a_displayer.setCapability("min Uniform Buffer Offset Alignment", a_prop.minUniformBufferOffsetAlignment);
	a_displayer.setCapability("min Storage Buffer Offset Alignment", a_prop.minStorageBufferOffsetAlignment);
	a_displayer.setCapability("min Texel Offset", a_prop.minTexelOffset);
	a_displayer.setCapability("max Texel Offset", a_prop.maxTexelOffset);
	a_displayer.setCapability("min Texel Gather Offset", a_prop.minTexelGatherOffset);
	a_displayer.setCapability("max Texel Gather Offset", a_prop.maxTexelGatherOffset);
	a_displayer.setCapability("min Interpolation Offset", a_prop.minInterpolationOffset);
	a_displayer.setCapability("max Interpolation Offset", a_prop.maxInterpolationOffset);
	a_displayer.setCapability("sub Pixel Interpolation Offset Bits", a_prop.subPixelInterpolationOffsetBits);
	a_displayer.setCapability("max Framebuffer Width", a_prop.maxFramebufferWidth);
	a_displayer.setCapability("max Framebuffer Height", a_prop.maxFramebufferHeight);
	a_displayer.setCapability("max Framebuffer Layers", a_prop.maxFramebufferLayers);
	a_displayer.setCapability("framebuffer Color Sample Counts", Flag<VkSampleCountFlagBits>::to_string(a_prop.framebufferColorSampleCounts));
	a_displayer.setCapability("framebuffer Depth Sample Counts", Flag<VkSampleCountFlagBits>::to_string(a_prop.framebufferDepthSampleCounts));
	a_displayer.setCapability("framebuffer Stencil Sample Counts", Flag<VkSampleCountFlagBits>::to_string(a_prop.framebufferStencilSampleCounts));
	a_displayer.setCapability("framebuffer No Attachments Sample Counts", Flag<VkSampleCountFlagBits>::to_string(a_prop.framebufferNoAttachmentsSampleCounts));
	a_displayer.setCapability("max Color Attachments", a_prop.maxColorAttachments);
	a_displayer.setCapability("sampled Image Color Sample Counts", Flag<VkSampleCountFlagBits>::to_string(a_prop.sampledImageColorSampleCounts));
	a_displayer.setCapability("sampled Image Integer Sample Counts", Flag<VkSampleCountFlagBits>::to_string(a_prop.sampledImageIntegerSampleCounts));
	a_displayer.setCapability("sampled Image Depth Sample Counts", Flag<VkSampleCountFlagBits>::to_string(a_prop.sampledImageDepthSampleCounts));
	a_displayer.setCapability("sampled Image Stencil Sample Counts", Flag<VkSampleCountFlagBits>::to_string(a_prop.sampledImageStencilSampleCounts));
	a_displayer.setCapability("storage Image Sample Counts", Flag<VkSampleCountFlagBits>::to_string(a_prop.storageImageSampleCounts));
	a_displayer.setCapability("max Sample Mask Words", a_prop.maxSampleMaskWords);
	a_displayer.setCapability("timestamp Compute And Graphics", a_prop.timestampComputeAndGraphics);
	a_displayer.setCapability("timestamp Period", a_prop.timestampPeriod);
	a_displayer.setCapability("max Clip Distances", a_prop.maxClipDistances);
	a_displayer.setCapability("max Cull Distances", a_prop.maxCullDistances);
	a_displayer.setCapability("max Combined Clip And Cull Distances", a_prop.maxCombinedClipAndCullDistances);
	a_displayer.setCapability("discrete Queue Priorities", a_prop.discreteQueuePriorities);
	for (const auto propVal : a_prop.pointSizeRange)
	{
		a_displayer.setCapability("point Size Range", propVal);
	}

	for (const auto propVal : a_prop.lineWidthRange)
	{
		a_displayer.setCapability("line Width Range", propVal);
	}

	a_displayer.setCapability("point Size Granularity", a_prop.pointSizeGranularity);
	a_displayer.setCapability("line Width Granularity", a_prop.lineWidthGranularity);
	a_displayer.setCapability("strict Lines", a_prop.strictLines);
	a_displayer.setCapability("standard Sample Locations", a_prop.standardSampleLocations);
	a_displayer.setCapability("optimal Buffer Copy Offset Alignment", a_prop.optimalBufferCopyOffsetAlignment);
	a_displayer.setCapability("optimal Buffer Copy Row Pitch Alignment", a_prop.optimalBufferCopyRowPitchAlignment);
	a_displayer.setCapability("non Coherent Atom Size", a_prop.nonCoherentAtomSize);
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkPhysicalDeviceMemoryProperties& a_prop)
{
	a_displayer.setCapability("memory Type Count", a_prop.memoryTypeCount);
	for (const auto propVal : a_prop.memoryTypes)
	{
		a_displayer.pushCategory("memory Types");
		display(a_displayer, propVal);
		a_displayer.popCategory();
	}

	a_displayer.setCapability("memory Heap Count", a_prop.memoryHeapCount);
	for (const auto propVal : a_prop.memoryHeaps)
	{
		a_displayer.pushCategory("memory Heaps");
		display(a_displayer, propVal);
		a_displayer.popCategory();
	}

}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkPhysicalDeviceSparseProperties& a_prop)
{
	a_displayer.setCapability("residency Standard2D Block Shape", a_prop.residencyStandard2DBlockShape);
	a_displayer.setCapability("residency Standard2D Multisample Block Shape", a_prop.residencyStandard2DMultisampleBlockShape);
	a_displayer.setCapability("residency Standard3D Block Shape", a_prop.residencyStandard3DBlockShape);
	a_displayer.setCapability("residency Aligned Mip Size", a_prop.residencyAlignedMipSize);
	a_displayer.setCapability("residency Non Resident Strict", a_prop.residencyNonResidentStrict);
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkPhysicalDeviceProperties& a_prop)
{
	a_displayer.setCapability("api Version", a_prop.apiVersion);
	a_displayer.setCapability("driver Version", a_prop.driverVersion);
	a_displayer.setCapability("vendor ID", a_prop.vendorID);
	a_displayer.setCapability("device ID", a_prop.deviceID);
	a_displayer.setCapability("device Type", to_string(a_prop.deviceType));
	for (const auto propVal : a_prop.deviceName)
	{
		a_displayer.setCapability("device Name", propVal);
	}

	for (const auto propVal : a_prop.pipelineCacheUUID)
	{
		a_displayer.setCapability("pipeline Cache UU ID", propVal);
	}

	a_displayer.pushCategory("limits");
	display(a_displayer, a_prop.limits);
	a_displayer.popCategory();
	a_displayer.pushCategory("sparse Properties");
	display(a_displayer, a_prop.sparseProperties);
	a_displayer.popCategory();
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkQueueFamilyProperties& a_prop)
{
	a_displayer.setCapability("queue Flags", Flag<VkQueueFlagBits>::to_string(a_prop.queueFlags));
	a_displayer.setCapability("queue Count", a_prop.queueCount);
	a_displayer.setCapability("timestamp Valid Bits", a_prop.timestampValidBits);
	a_displayer.pushCategory("min Image Transfer Granularity");
	display(a_displayer, a_prop.minImageTransferGranularity);
	a_displayer.popCategory();
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkExtensionProperties& a_prop)
{
	for (const auto propVal : a_prop.extensionName)
	{
		a_displayer.setCapability("extension Name", propVal);
	}

	a_displayer.setCapability("spec Version", a_prop.specVersion);
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkLayerProperties& a_prop)
{
	for (const auto propVal : a_prop.layerName)
	{
		a_displayer.setCapability("layer Name", propVal);
	}

	a_displayer.setCapability("spec Version", a_prop.specVersion);
	a_displayer.setCapability("implementation Version", a_prop.implementationVersion);
	for (const auto propVal : a_prop.description)
	{
		a_displayer.setCapability("description", propVal);
	}

}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkMemoryRequirements& a_prop)
{
	a_displayer.setCapability("size", a_prop.size);
	a_displayer.setCapability("alignment", a_prop.alignment);
	a_displayer.setCapability("memory Type Bits", a_prop.memoryTypeBits);
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkSparseMemoryBind& a_prop)
{
	a_displayer.setCapability("resource Offset", a_prop.resourceOffset);
	a_displayer.setCapability("size", a_prop.size);
	a_displayer.setCapability("memory", a_prop.memory);
	a_displayer.setCapability("memory Offset", a_prop.memoryOffset);
	a_displayer.setCapability("flags", Flag<VkSparseMemoryBindFlagBits>::to_string(a_prop.flags));
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkImageSubresource& a_prop)
{
	a_displayer.setCapability("aspect Mask", Flag<VkImageAspectFlagBits>::to_string(a_prop.aspectMask));
	a_displayer.setCapability("mip Level", a_prop.mipLevel);
	a_displayer.setCapability("array Layer", a_prop.arrayLayer);
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkSparseImageMemoryBind& a_prop)
{
	a_displayer.pushCategory("subresource");
	display(a_displayer, a_prop.subresource);
	a_displayer.popCategory();
	a_displayer.pushCategory("offset");
	display(a_displayer, a_prop.offset);
	a_displayer.popCategory();
	a_displayer.pushCategory("extent");
	display(a_displayer, a_prop.extent);
	a_displayer.popCategory();
	a_displayer.setCapability("memory", a_prop.memory);
	a_displayer.setCapability("memory Offset", a_prop.memoryOffset);
	a_displayer.setCapability("flags", Flag<VkSparseMemoryBindFlagBits>::to_string(a_prop.flags));
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkSparseImageFormatProperties& a_prop)
{
	a_displayer.setCapability("aspect Mask", Flag<VkImageAspectFlagBits>::to_string(a_prop.aspectMask));
	a_displayer.pushCategory("image Granularity");
	display(a_displayer, a_prop.imageGranularity);
	a_displayer.popCategory();
	a_displayer.setCapability("flags", Flag<VkSparseImageFormatFlagBits>::to_string(a_prop.flags));
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkSparseImageMemoryRequirements& a_prop)
{
	a_displayer.pushCategory("format Properties");
	display(a_displayer, a_prop.formatProperties);
	a_displayer.popCategory();
	a_displayer.setCapability("image Mip Tail First Lod", a_prop.imageMipTailFirstLod);
	a_displayer.setCapability("image Mip Tail Size", a_prop.imageMipTailSize);
	a_displayer.setCapability("image Mip Tail Offset", a_prop.imageMipTailOffset);
	a_displayer.setCapability("image Mip Tail Stride", a_prop.imageMipTailStride);
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkSubresourceLayout& a_prop)
{
	a_displayer.setCapability("offset", a_prop.offset);
	a_displayer.setCapability("size", a_prop.size);
	a_displayer.setCapability("row Pitch", a_prop.rowPitch);
	a_displayer.setCapability("array Pitch", a_prop.arrayPitch);
	a_displayer.setCapability("depth Pitch", a_prop.depthPitch);
}

void display(IRHICapabilitiesDisplayer& a_displayer, const VkComponentMapping& a_prop)
{
	a_displayer.setCapability("r", to_string(a_prop.r));
	a_displayer.setCapability("g", to_string(a_prop.g));
	a_displayer.setCapability("b", to_string(a_prop.b));
	a_displayer.setCapability("a", to_string(a_prop.a));
}
