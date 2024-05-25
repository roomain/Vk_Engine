#include "pch.h"
#include <ranges>
#include "vk_struct_display.h"
#include "VkApplication.h"
#include "IRHICapabilitiesDisplayer.h"
#include "vk_enumToString.h"
#include "stringUtils.h"

void VkApplication::createVulkanInstance(VkApplication* const a_this, const VKInstanceSettings& a_setting)
{
	if (a_setting.isValid())
	{
		VkApplicationInfo appInfo = gen_applicationInfo();
		appInfo.pApplicationName = a_setting.ApplicationName.c_str();
		appInfo.pEngineName = a_setting.EngineName.c_str();
		appInfo.applicationVersion = a_setting.AppVersion;

		VkInstanceCreateInfo instanceInfo = gen_instanceCreateInfo();
		instanceInfo.pApplicationInfo = &appInfo;

		std::vector<const char*> vLayers = vStringToChar(a_setting.Layers);
		instanceInfo.ppEnabledLayerNames = vLayers.data();
		instanceInfo.enabledLayerCount = static_cast<uint32_t>(vLayers.size());

		std::vector<const char*> vExtension = vStringToChar(a_setting.Extensions);
		instanceInfo.ppEnabledExtensionNames = vExtension.data();
		instanceInfo.enabledExtensionCount = static_cast<uint32_t>(vExtension.size());
		
		VK_CHECK(vkCreateInstance(&instanceInfo, nullptr, &(a_this->m_vulkanInstance)))
	}
}

bool VkApplication::getCompatibleQueues(std::vector<VkQueueFamilyProperties>& a_queueFamilies,
	const std::vector<VKQueueSettings>& a_vSettings, QueueConfMap& a_confMap)
{
	// for each queue settings
	for (const auto& queueSettings : a_vSettings)
	{
		uint32_t iNumDesired = queueSettings.Count;
		uint32_t queueFamilyIndex = 0;

		// for each family filtered property
		for (auto& familyProp : a_queueFamilies)
		{
			// filter queue property
			if (((familyProp.queueFlags & queueSettings.QueueFlag) == queueSettings.QueueFlag)
				&& (familyProp.queueCount > 0))
			{
				uint32_t usedQueueCount = std::min(familyProp.queueCount, iNumDesired);
				std::vector<float> vPriority(usedQueueCount, queueSettings.Priority);
				a_confMap[queueSettings.QueueFlag].emplace_back(
					QueueConfig{queueFamilyIndex, usedQueueCount, std::move(vPriority) });

				familyProp.queueCount -= usedQueueCount;
				iNumDesired -= usedQueueCount;

				if (iNumDesired == 0)
					break;
			}
			queueFamilyIndex++;
		}

		if (iNumDesired > 0)
			return false;
	}
	return true;
}

VkApplication::VkApplication(const VKInstanceSettings& a_settings)
{
	VkApplication::createVulkanInstance(this, a_settings);
	//
}

VkApplication::VkApplication()
{
	VKInstanceSettings settings;
	VkApplication::createVulkanInstance(this, settings);
	// todo
}

VkApplication::~VkApplication()
{
	release();
}

void VkApplication::release()
{
	// release all resources 

	// release all devices
	m_devices.clear();

	if (m_vulkanInstance != VK_NULL_HANDLE)
	{
		vkDestroyInstance(m_vulkanInstance, nullptr);
		m_vulkanInstance = VK_NULL_HANDLE;
		// todo
	}
}

void getFeatures(const VKDeviceSettings& a_settings, VkPhysicalDeviceFeatures& a_features)
{
	a_features.robustBufferAccess = a_settings.RobustBufferAccess;
	a_features.fullDrawIndexUint32 = a_settings.FullDrawIndexUint32;
	a_features.imageCubeArray = a_settings.ImageCubeArray;
	a_features.independentBlend = a_settings.IndependentBlend;
	a_features.geometryShader = a_settings.GeometryShader;
	a_features.tessellationShader = a_settings.TessellationShader;
	a_features.sampleRateShading = a_settings.SampleRateShading;
	a_features.dualSrcBlend = a_settings.DualSrcBlend;
	a_features.logicOp = a_settings.LogicOp;
	a_features.multiDrawIndirect = a_settings.MultiDrawIndirect;
	a_features.drawIndirectFirstInstance = a_settings.DrawIndirectFirstInstance;
	a_features.depthClamp = a_settings.DepthClamp;
	a_features.depthBiasClamp = a_settings.DepthBiasClamp;
	a_features.fillModeNonSolid = a_settings.FillModeNonSolid;
	a_features.depthBounds = a_settings.DepthBounds;
	a_features.wideLines = a_settings.WideLines;
	a_features.largePoints = a_settings.LargePoints;
	a_features.alphaToOne = a_settings.AlphaToOne;
	a_features.multiViewport = a_settings.MultiViewport;
	a_features.samplerAnisotropy = a_settings.SamplerAnisotropy;
	a_features.textureCompressionETC2 = a_settings.TextureCompressionETC2;
	a_features.textureCompressionASTC_LDR = a_settings.TextureCompressionASTC_LDR;
	a_features.textureCompressionBC = a_settings.TextureCompressionBC;
	a_features.occlusionQueryPrecise = a_settings.OcclusionQueryPrecise;
	a_features.pipelineStatisticsQuery = a_settings.PipelineStatisticsQuery;
	a_features.vertexPipelineStoresAndAtomics = a_settings.VertexPipelineStoresAndAtomics;
	a_features.fragmentStoresAndAtomics = a_settings.FragmentStoresAndAtomics;
	a_features.shaderTessellationAndGeometryPointSize = a_settings.ShaderTessellationAndGeometryPointSize;
	a_features.shaderImageGatherExtended = a_settings.ShaderImageGatherExtended;
	a_features.shaderStorageImageExtendedFormats = a_settings.ShaderStorageImageExtendedFormats;
	a_features.shaderStorageImageMultisample = a_settings.ShaderStorageImageMultisample;
	a_features.shaderStorageImageReadWithoutFormat = a_settings.ShaderStorageImageReadWithoutFormat;
	a_features.shaderStorageImageWriteWithoutFormat = a_settings.ShaderStorageImageWriteWithoutFormat;
	a_features.shaderUniformBufferArrayDynamicIndexing = a_settings.ShaderUniformBufferArrayDynamicIndexing;
	a_features.shaderSampledImageArrayDynamicIndexing = a_settings.ShaderSampledImageArrayDynamicIndexing;
	a_features.shaderStorageBufferArrayDynamicIndexing = a_settings.ShaderStorageBufferArrayDynamicIndexing;
	a_features.shaderStorageImageArrayDynamicIndexing = a_settings.ShaderStorageImageArrayDynamicIndexing;
	a_features.shaderClipDistance = a_settings.ShaderClipDistance;
	a_features.shaderCullDistance = a_settings.ShaderCullDistance;
	a_features.shaderFloat64 = a_settings.ShaderFloat64;
	a_features.shaderInt64 = a_settings.ShaderInt64;
	a_features.shaderInt16 = a_settings.ShaderInt16;
	a_features.shaderResourceResidency = a_settings.ShaderResourceResidency;
	a_features.shaderResourceMinLod = a_settings.ShaderResourceMinLod;
	a_features.sparseBinding = a_settings.SparseBinding;
	a_features.sparseResidencyBuffer = a_settings.SparseResidencyBuffer;
	a_features.sparseResidencyImage2D = a_settings.SparseResidencyImage2D;
	a_features.sparseResidencyImage3D = a_settings.SparseResidencyImage3D;
	a_features.sparseResidency2Samples = a_settings.SparseResidency2Samples;
	a_features.sparseResidency4Samples = a_settings.SparseResidency4Samples;
	a_features.sparseResidency8Samples = a_settings.SparseResidency8Samples;
	a_features.sparseResidency16Samples = a_settings.SparseResidency16Samples;
	a_features.sparseResidencyAliased = a_settings.SparseResidencyAliased;
	a_features.variableMultisampleRate = a_settings.VariableMultisampleRate;
	a_features.inheritedQueries = a_settings.InheritedQueries;
}

VkEngineDevicePtr VkApplication::createDevice(const VKDeviceSettings& a_settings, const VKDeviceInfo& a_devInfo)
{
	VkEngineDevicePtr device;
	std::vector<VkDeviceQueueCreateInfo> vQueueInfo;
	for (const auto& [flag, indexList] : a_devInfo.Queues)
	{
		for (const auto& queueInfo : indexList)
		{
			VkDeviceQueueCreateInfo queueCreateInfo = gen_queueCreateInfo();
			queueCreateInfo.flags = 0;// VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT;
			queueCreateInfo.queueFamilyIndex = queueInfo.QueueFamily;
			queueCreateInfo.queueCount = queueInfo.QueueCount;
			queueCreateInfo.pQueuePriorities = queueInfo.Priorities.data();
			vQueueInfo.emplace_back(std::move(queueCreateInfo));
		}
	}

	VkPhysicalDeviceFeatures devFeatures;
	getFeatures(a_settings, devFeatures);


	auto vExtension = vStringToChar(a_settings.Extensions);
	auto vLayers = vStringToChar(a_settings.Layers);

	VkDeviceCreateInfo deviceCreateInfo = gen_deviceCreateInfo();
	deviceCreateInfo.flags = a_devInfo.Flag;
	deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(vQueueInfo.size());
	deviceCreateInfo.pQueueCreateInfos = vQueueInfo.data();;
	deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(vLayers.size());
	deviceCreateInfo.ppEnabledLayerNames = vLayers.data();
	deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(vExtension.size());
	deviceCreateInfo.ppEnabledExtensionNames = vExtension.data();
	deviceCreateInfo.pEnabledFeatures = &devFeatures;

	VkDevice logical;
	VK_CHECK(vkCreateDevice(a_devInfo.PhysicalDeviceHandle, &deviceCreateInfo, nullptr, &logical));
	// use new instead of std::make_shared because ctor is private
	return m_devices.emplace_back(new VkEngineDevice(m_vulkanInstance, a_devInfo.PhysicalDeviceHandle, 
		logical, a_devInfo.Queues));
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
		a_displayer.setCapability("description", std::string(layer.description));
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
		uint32_t numDevices = 0;
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

			uint32_t numExtension = 0;
			vkEnumerateDeviceExtensionProperties(device, nullptr, &numExtension, nullptr);
			std::vector<VkExtensionProperties> vProperties(numExtension);
			vkEnumerateDeviceExtensionProperties(device, nullptr, &numExtension, vProperties.data());
			a_displayer.pushCategory("Extensions");
			for (const auto& extProp : vProperties)
				display(a_displayer, extProp);
			a_displayer.popCategory();

			uint32_t numLayers = 0;
			vkEnumerateDeviceLayerProperties(device, &numLayers, nullptr);
			std::vector<VkLayerProperties> vLayers(numLayers);
			vkEnumerateDeviceLayerProperties(device, &numLayers, vLayers.data());
			a_displayer.pushCategory("Layers");
			for (const auto& layersProp : vLayers)
				display(a_displayer, layersProp);
			a_displayer.popCategory();

			a_displayer.pushCategory("Sparse properties");
            display(a_displayer, prop.sparseProperties);
			a_displayer.popCategory();

			a_displayer.pushCategory("limits");
            display(a_displayer, prop.limits);
			a_displayer.popCategory();

			VkPhysicalDeviceFeatures feature;
			vkGetPhysicalDeviceFeatures(device, &feature);
			a_displayer.pushCategory("features");
			display(a_displayer, feature);
			a_displayer.popCategory();

			uint32_t queueFamilyCount;
			vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
			std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyProperties.data());
			a_displayer.pushCategory("Queues");
			for (const auto& queueFamily : queueFamilyProperties)
				display(a_displayer, queueFamily);			
			a_displayer.popCategory();
		}
	}	
}

bool VkApplication::findCompatibleDevices(const VKDeviceSettings& a_settings, std::vector<VKDeviceInfo>& a_vCompatibeDevices)const
{
	if(m_vulkanInstance == VK_NULL_HANDLE)
		return false;
		
	uint32_t numDevices = 0;
	vkEnumeratePhysicalDevices(m_vulkanInstance, &numDevices, nullptr);
	std::vector<VkPhysicalDevice> vDevices{ numDevices };
	vkEnumeratePhysicalDevices(m_vulkanInstance, &numDevices, vDevices.data());
	int deviceIndex = 0;
	VKDeviceInfo devInfo;

	for (const auto& device : vDevices)
	{	
		// init device info
		devInfo.Queues.clear();			
		devInfo.PhysicalDeviceHandle = device;
		if (VkEngineDevice::checkDeviceLayers(device, a_settings.Layers) &&
			VkEngineDevice::checkDeviceExtension(device, a_settings.Extensions))
		{
			VkPhysicalDeviceProperties prop;
			vkGetPhysicalDeviceProperties(device, &prop);
			devInfo.DeviceType = prop.deviceType;
			devInfo.DeviceName = prop.deviceName;

			uint32_t queueFamilyCount;
			vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
			std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyProperties.data());

			if (VkApplication::getCompatibleQueues(queueFamilyProperties, a_settings.QueuesSettings, devInfo.Queues))
				a_vCompatibeDevices.emplace_back(std::move(devInfo));
		}
		deviceIndex++;
	}
	return true;
}