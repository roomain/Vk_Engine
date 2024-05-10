#pragma once
/***********************************************
* @headerfile vk_parameters.h
* @date 23 / 04 / 2024
* @author Roomain
************************************************/
#include "vk_From_string.h"
#include "RHI_macros.h"
#include <vector>
#include <string>
#include "vk_engine_globals.h"

#pragma warning(push)
#pragma warning(disable : 4251)

struct ENGINE_EXPORT VKSettings
{
	virtual bool isValid()const noexcept = 0;
};

REFLECT_CLASS(VKInstanceSettings)
struct ENGINE_EXPORT VKInstanceSettings : VKSettings
{
	REFLECT_MEMBER
	std::string ApplicationName;
	
	REFLECT_MEMBER
	std::string EngineName;

	REFLECT_MEMBER
	int AppVersion = 0;

	REFLECT_MEMBER
	std::vector<std::string> Layers;

	REFLECT_MEMBER
	std::vector<std::string> Extensions;

	[[nodiscard]] bool isValid()const noexcept override
	{
		return !ApplicationName.empty() && !EngineName.empty() && AppVersion > 0;
	}
private:
	DECLARE_REFLECT_CLASS(VKInstanceSettings)
};


REFLECT_CLASS(VKQueueSettings)
struct VKQueueSettings
{
	REFLECT_MEMBER
	int Count = 1;

	REFLECT_FLAG(VkQueueFlagBits)
	VkQueueFlags QueueFlag = 0;
private:
	DECLARE_REFLECT_CLASS(VKQueueSettings)
};


REFLECT_CLASS(VKDeviceSettings)
struct ENGINE_EXPORT VKDeviceSettings : VKSettings
{
	REFLECT_MEMBER
	int DeviceIndex = -1;

	REFLECT_MEMBER
	std::vector<std::string> Layers;

	REFLECT_MEMBER
	std::vector<std::string> Extensions;

	REFLECT_MEMBER
	std::vector<VKQueueSettings> QueuesSettings;

    REFLECT_MEMBER
    bool RobustBufferAccess = false;

    REFLECT_MEMBER
    bool FullDrawIndexUint32 = false;

    REFLECT_MEMBER
    bool ImageCubeArray = false;

    REFLECT_MEMBER
    bool IndependentBlend = false;

    REFLECT_MEMBER
    bool GeometryShader = false;

    REFLECT_MEMBER
    bool TessellationShader = false;

    REFLECT_MEMBER
    bool SampleRateShading = false;

    REFLECT_MEMBER
    bool DualSrcBlend = false;

    REFLECT_MEMBER
    bool LogicOp = false;

    REFLECT_MEMBER
    bool MultiDrawIndirect = false;

    REFLECT_MEMBER
    bool DrawIndirectFirstInstance = false;

    REFLECT_MEMBER
    bool DepthClamp = false;

    REFLECT_MEMBER
    bool DepthBiasClamp = false;

    REFLECT_MEMBER
    bool FillModeNonSolid = false;

    REFLECT_MEMBER
    bool DepthBounds = false;

    REFLECT_MEMBER
    bool WideLines = false;

    REFLECT_MEMBER
    bool LargePoints = false;

    REFLECT_MEMBER
    bool AlphaToOne = false;

    REFLECT_MEMBER
    bool MultiViewport = false;

    REFLECT_MEMBER
    bool SamplerAnisotropy = false;

    REFLECT_MEMBER
    bool TextureCompressionETC2 = false;

    REFLECT_MEMBER
    bool TextureCompressionASTC_LDR = false;

    REFLECT_MEMBER
    bool TextureCompressionBC = false;

    REFLECT_MEMBER
    bool OcclusionQueryPrecise = false;

    REFLECT_MEMBER
    bool PipelineStatisticsQuery = false;

    REFLECT_MEMBER
    bool VertexPipelineStoresAndAtomics = false;

    REFLECT_MEMBER
    bool FragmentStoresAndAtomics = false;

    REFLECT_MEMBER
    bool ShaderTessellationAndGeometryPointSize = false;

    REFLECT_MEMBER
    bool ShaderImageGatherExtended = false;

    REFLECT_MEMBER
    bool ShaderStorageImageExtendedFormats = false;

    REFLECT_MEMBER
    bool ShaderStorageImageMultisample = false;

    REFLECT_MEMBER
    bool ShaderStorageImageReadWithoutFormat = false;

    REFLECT_MEMBER
    bool ShaderStorageImageWriteWithoutFormat = false;

    REFLECT_MEMBER
    bool ShaderUniformBufferArrayDynamicIndexing = false;

    REFLECT_MEMBER
    bool ShaderSampledImageArrayDynamicIndexing = false;

    REFLECT_MEMBER
    bool ShaderStorageBufferArrayDynamicIndexing = false;

    REFLECT_MEMBER
    bool ShaderStorageImageArrayDynamicIndexing = false;

    REFLECT_MEMBER
    bool ShaderClipDistance = false;

    REFLECT_MEMBER
    bool ShaderCullDistance = false;

    REFLECT_MEMBER
    bool ShaderFloat64 = false;

    REFLECT_MEMBER
    bool ShaderInt64 = false;

    REFLECT_MEMBER
    bool ShaderInt16 = false;

    REFLECT_MEMBER
    bool ShaderResourceResidency = false;

    REFLECT_MEMBER
    bool ShaderResourceMinLod = false;

    REFLECT_MEMBER
    bool SparseBinding = false;

    REFLECT_MEMBER
    bool SparseResidencyBuffer = false;

    REFLECT_MEMBER
    bool SparseResidencyImage2D = false;

    REFLECT_MEMBER
    bool SparseResidencyImage3D = false;

    REFLECT_MEMBER
    bool SparseResidency2Samples = false;

    REFLECT_MEMBER
    bool SparseResidency4Samples = false;

    REFLECT_MEMBER
    bool SparseResidency8Samples = false;

    REFLECT_MEMBER
    bool SparseResidency16Samples = false;

    REFLECT_MEMBER
    bool SparseResidencyAliased = false;

    REFLECT_MEMBER
    bool VariableMultisampleRate = false;

    REFLECT_MEMBER
    bool InheritedQueries = false;

	inline bool isValid()const noexcept override
	{
		return DeviceIndex >= 0 && !QueuesSettings.empty();

	}
private:
	DECLARE_REFLECT_CLASS(VKDeviceSettings)
};

#pragma warning(pop)