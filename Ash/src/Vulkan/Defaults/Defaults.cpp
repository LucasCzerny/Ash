#include "pch.h"
#include "Defaults.h"

#include "Core/Assert.h"

#include "Vulkan/Context/Context.h"

namespace Ash::Vulkan
{
	template <typename Type>
	Type Defaults()
	{
		Log::Warn(false, "That type does not have a default yet.");
		return Type{};
	}

	// CONTEXT

	// TODO: bit awkward
	template<>
	VkApplicationInfo Defaults()
	{
		static std::shared_ptr<Context> context = Context::Get();

		static VkApplicationInfo info;

		info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		info.pNext = nullptr;
		info.pApplicationName = ""; // REQUIRED
		info.applicationVersion = VK_MAKE_API_VERSION(0, 0, 1, 0); // REQUIRED;
		info.pEngineName = "Ash";
		info.engineVersion = VK_MAKE_API_VERSION(0, 0, 1, 0); // REQUIRED
		info.apiVersion = VK_API_VERSION_1_3;

		return info;
	}
	
	template<>
	VkInstanceCreateInfo Defaults()
	{
		static std::shared_ptr<Context> context = Context::Get();

		static VkInstanceCreateInfo info;

		info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		info.pNext = nullptr;
		info.flags = NULL;
		info.pApplicationInfo = nullptr; // REQUIRED
		info.enabledLayerCount = 0; // REQUIRED
		info.ppEnabledLayerNames = nullptr; // REQUIRED
		info.enabledExtensionCount = 0; // REQUIRED
		info.ppEnabledExtensionNames = nullptr; // REQUIRED

		return info;
	}

	template<>
	VkDebugUtilsMessengerCreateInfoEXT Defaults()
	{
		static std::shared_ptr<Context> context = Context::Get();

		static VkDebugUtilsMessengerCreateInfoEXT info;

		info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		info.pNext = nullptr;
		info.flags = NULL;
		info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;;
		info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT;;
		info.pfnUserCallback = nullptr; // REQUIRED
		info.pUserData = nullptr; // REQUIRED

		return info;
	}

	// DEVICE

	template<>
	VkDeviceCreateInfo Defaults()
	{
		static Config& config = Config::Get();

		static VkDeviceCreateInfo info;

		info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		info.pNext = nullptr;
		info.flags = NULL;
		info.queueCreateInfoCount = 0; // REQUIRED
		info.pQueueCreateInfos = nullptr; // REQUIRED

		info.enabledLayerCount = 0;
		info.ppEnabledLayerNames = nullptr;

		const std::vector<const char*>& deviceExtensions = Config::Get().DeviceExtensions;
		info.enabledExtensionCount = (uint32_t)deviceExtensions.size();
		info.ppEnabledExtensionNames = deviceExtensions.data();

		info.pEnabledFeatures = nullptr; // REQUIRED

		return info;
	}

	template<>
	VkDeviceQueueCreateInfo Defaults()
	{
		static VkDeviceQueueCreateInfo info;

		info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		info.pNext = nullptr;
		info.flags = NULL;
		info.queueFamilyIndex = 0; // REQUIRED
		info.queueCount = 0; // REQUIRED

		static constexpr float queuePriority = 1.0f;
		info.pQueuePriorities = &queuePriority;

		return info;
	}

	// COMMAND BUFFER

	template<>
	VkCommandBufferAllocateInfo Defaults()
	{
		static std::shared_ptr<Context> context = Context::Get();

		static VkCommandBufferAllocateInfo info;

		info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		info.pNext = nullptr;
		info.commandPool = context->CommandPool;
		info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		info.commandBufferCount = 0; // REQUIRED

		return info;
	}

	template<>
	VkCommandBufferBeginInfo Defaults()
	{
		static VkCommandBufferBeginInfo info;
		
		info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		info.pNext = nullptr;
		info.flags = NULL;
		info.pInheritanceInfo = nullptr;

		return info;
	}

	// IMAGE

	template<>
	VkImageCreateInfo Defaults()
	{
		static std::shared_ptr<Context> context = Context::Get();

		static VkImageCreateInfo info;

		info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		info.pNext = nullptr;
		info.flags = NULL;

		info.imageType = VK_IMAGE_TYPE_2D;
		info.format = VK_FORMAT_R8G8B8A8_UNORM;

		VkExtent2D extent = context->SwapChain.Extent2D;
		info.extent.width = extent.width;
		info.extent.height = extent.height;
		info.extent.depth = 1;

		info.mipLevels = 1;
		info.arrayLayers = 1;
		info.samples = VK_SAMPLE_COUNT_1_BIT;
		info.tiling = VK_IMAGE_TILING_OPTIMAL;
		info.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
		info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		std::array<uint32_t, 2> queueFamilies = { context->Device.GraphicsQueue.Family, context->Device.PresentQueue.Family };
		info.queueFamilyIndexCount = (uint32_t)queueFamilies.size();
		info.pQueueFamilyIndices = queueFamilies.data();

		info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

		return info;
	}

	template<>
	VkImageViewCreateInfo Defaults()
	{
		static VkImageViewCreateInfo info;

		info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		info.pNext = nullptr;
		info.flags = NULL;

		info.image = VK_NULL_HANDLE; // REQUIRED
		info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		info.format = VK_FORMAT_R8G8B8A8_UNORM; // REQUIRED
		info.components = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A };
		info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		info.subresourceRange.baseArrayLayer = 0;
		info.subresourceRange.baseMipLevel = 0;
		info.subresourceRange.layerCount = 1;
		info.subresourceRange.levelCount = 1;

		return info;
	}

	template<>
	VkMemoryAllocateInfo Defaults()
	{
		static std::shared_ptr<Context> context = Context::Get();

		static VkMemoryAllocateInfo info;
		info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		info.pNext = nullptr;
		info.allocationSize = 0; // REQUIRED
		info.memoryTypeIndex = 0; // REQUIRED

		return info;
	}

	template<>
	VkImageMemoryBarrier Defaults()
	{
		static VkImageMemoryBarrier info;

		info.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		info.pNext = nullptr;
		info.srcAccessMask;
		info.dstAccessMask;
		info.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED; // REQUIRED
		info.newLayout = VK_IMAGE_LAYOUT_UNDEFINED; // REQUIRED
		info.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		info.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		info.image = VK_NULL_HANDLE; // REQUIRED
		
		info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		info.subresourceRange.baseMipLevel = 0;
		info.subresourceRange.levelCount = 1;
		info.subresourceRange.baseArrayLayer = 0;
		info.subresourceRange.layerCount = 1;

		return info;
	}

	template<>
	VkBufferImageCopy Defaults()
	{
		static VkBufferImageCopy info;

		info.bufferOffset = 0;
		info.bufferRowLength = 0;
		info.bufferImageHeight = 0;

		info.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		info.imageSubresource.mipLevel = 0;
		info.imageSubresource.baseArrayLayer = 0;
		info.imageSubresource.layerCount = 1;

		info.imageOffset = { 0, 0, 0 };
		info.imageExtent = VkExtent3D{ 0, 0, 0, }; // REQUIRED

		return info;
	}

	// SWAP CHAIN

	template<>
	VkSwapchainCreateInfoKHR Defaults()
	{
		static VkSwapchainCreateInfoKHR info;

		info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		info.pNext = nullptr;
		info.flags = NULL;
		info.surface = VK_NULL_HANDLE; // REQUIRED 
		info.minImageCount = 0; // REQUIRED 
		info.imageFormat = VK_FORMAT_UNDEFINED; // REQUIRED 
		info.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR; // REQUIRED 
		info.imageExtent = VkExtent2D{ 0, 0 }; // REQUIRED 
		info.imageArrayLayers = 1;
		info.imageUsage = VK_IMAGE_USAGE_SAMPLED_BIT; // LIKELY NEEDS TO BE CHANGED
		info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;

		info.queueFamilyIndexCount = 0;
		info.pQueueFamilyIndices = nullptr;

		info.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR; // REQUIRED
		info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		info.presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR; // REQUIRED
		info.clipped = VK_TRUE;
		info.oldSwapchain = nullptr; // LIKELY NEEDS TO BE SET

		return info;
	}

	// RENDER SYSTEM
	
	template<>
	VkSemaphoreCreateInfo Defaults()
	{
		static VkSemaphoreCreateInfo info;

		info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		info.pNext = nullptr;
		info.flags = NULL;
		
		return info;
	}

	template<>
	VkFramebufferCreateInfo Defaults()
	{
		static std::shared_ptr<Context> context = Context::Get();

		static VkFramebufferCreateInfo info;

		info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		info.pNext = nullptr;
		info.flags = NULL;
		info.renderPass = VK_NULL_HANDLE; // REQUIRED
		info.attachmentCount = 0;
		info.pAttachments = nullptr;
		info.width = context->SwapChain.Extent2D.width;
		info.height = context->SwapChain.Extent2D.height;
		info.layers = 1;

		return info;
	}

	template<>
	VkFenceCreateInfo Defaults()
	{
		static VkFenceCreateInfo info;
		
		info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		info.pNext = nullptr;
		info.flags = NULL;
		
		return info;
	}

	template<>
	VkSubmitInfo Defaults()
	{
		static VkSubmitInfo info;

		info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		info.pNext = nullptr;
		info.waitSemaphoreCount = 0; // OPTIONAL
		info.pWaitSemaphores = nullptr; // OPTIONAL

		static VkPipelineStageFlags stageFlags = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		info.pWaitDstStageMask = &stageFlags;
		
		info.commandBufferCount = 0; // REQUIRED
		info.pCommandBuffers = nullptr; // REQUIRED
		info.signalSemaphoreCount = 0; // OPTIONAL
		info.pSignalSemaphores = 0; // OPTIONAL

		return info;
	}

	template<>
	VkPresentInfoKHR Defaults()
	{
		static std::shared_ptr<Context> context = Context::Get();

		static VkPresentInfoKHR info;

		info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		info.pNext = nullptr;
		info.waitSemaphoreCount = 0; // REQUIRED
		info.pWaitSemaphores = nullptr; // REQUIRED
		info.swapchainCount = 1;
		info.pSwapchains = context->SwapChain.Pointer();
		info.pImageIndices = 0; // REQUIRED
		info.pResults = nullptr;

		return info;
	}

	template<>
	VkRenderPassCreateInfo Defaults()
	{
		static VkRenderPassCreateInfo info;

		info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		info.pNext = nullptr;
		info.flags = NULL;
		info.attachmentCount = 0; // REQUIRED
		info.pAttachments = nullptr; // REQUIRED
		info.subpassCount = 0; // REQUIRED
		info.pSubpasses = nullptr; // REQUIRED
		info.dependencyCount = 0; // REQUIRED
		info.pDependencies = nullptr; // REQUIRED

		return info;
	}

	template<>
	VkPipelineLayoutCreateInfo Defaults()
	{
		static VkPipelineLayoutCreateInfo info;

		info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		info.pNext = nullptr;
		info.flags = NULL;
		info.setLayoutCount = 0; // REQUIRED
		info.pSetLayouts = nullptr; // REQUIRED
		info.pushConstantRangeCount = 0; // REQUIRED
		info.pPushConstantRanges = nullptr; // REQUIRED

		return info;
	}

	template<>
	VkAttachmentDescription Defaults()
	{
		static std::shared_ptr<Context> context = Context::Get();
		
		static VkAttachmentDescription info;

		info.flags = NULL;
		info.format = context->SwapChain.SurfaceFormat.format; // REQUIRED
		info.samples = VK_SAMPLE_COUNT_1_BIT;
		info.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		info.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		info.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		info.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		info.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR; // REQUIRED

		return info;
	}

	template<>
	VkAttachmentReference Defaults()
	{
		static VkAttachmentReference info;

		info.attachment = 0; // REQUIRED
		info.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		return info;
	}

	template<>
	VkSubpassDescription Defaults()
	{
		static VkSubpassDescription info;

		info.flags = NULL;
		info.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS; // REQUIRED
		info.inputAttachmentCount = 0; // REQUIRED
		info.pInputAttachments = nullptr; // REQUIRED
		info.colorAttachmentCount = 0; // REQUIRED
		info.pColorAttachments = nullptr; // REQUIRED
		info.pResolveAttachments = nullptr; // REQUIRED
		info.pDepthStencilAttachment = nullptr; // REQUIRED
		info.preserveAttachmentCount = 0; // REQUIRED
		info.pPreserveAttachments = nullptr; // REQUIRED

		return info;
	}

	template<>
	VkSubpassDependency Defaults()
	{
		static VkSubpassDependency info;

		info.srcSubpass = 0; // REQUIRED
		info.dstSubpass = 0; // REQUIRED
		info.srcStageMask = NULL; // REQUIRED
		info.dstStageMask = NULL; // REQUIRED
		info.srcAccessMask = NULL; // REQUIRED
		info.dstAccessMask = NULL; // REQUIRED

		return info;
	}

	template<>
	VkDescriptorSetLayoutCreateInfo Defaults()
	{
		static VkDescriptorSetLayoutCreateInfo info;

		info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		info.pNext = nullptr;
		info.flags = NULL;
		info.bindingCount = 0; // REQUIRED
		info.pBindings = nullptr; // REQUIRED
		
		return info;
	}

	template<>
	VkDescriptorSetLayoutBinding Defaults()
	{
		static VkDescriptorSetLayoutBinding info;

		info.binding = 0; // REQUIRED
		info.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; // REQUIRED
		info.descriptorCount = 1;
		info.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT; // REQUIRED
		info.pImmutableSamplers = nullptr;

		return info;
	}

	// DESCRIPTOR

	template<>
	VkDescriptorBufferInfo Defaults()
	{
		static VkDescriptorBufferInfo info;

		info.buffer = VK_NULL_HANDLE; // REQUIRED
		info.offset = 0;
		info.range = 0; // REQUIRED

		return info;
	}

	template<>
	VkWriteDescriptorSet Defaults()
	{
		static VkWriteDescriptorSet info;

		info.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		info.pNext = nullptr;
		info.dstSet = VK_NULL_HANDLE; // REQUIRED
		info.dstBinding = 0; // REQUIRED
		info.dstArrayElement = 0;
		info.descriptorCount = 0; // REQUIRED
		info.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; // REQUIRED

		// REQUIRED (one of these three)
		info.pImageInfo = nullptr;
		info.pBufferInfo = nullptr;
		info.pTexelBufferView = nullptr;

		return info;
	}

	template<>
	VkPushConstantRange Defaults()
	{
		static VkPushConstantRange info;
		info.stageFlags = VK_SHADER_STAGE_VERTEX_BIT; // REQUIRED
		info.offset = 0;
		info.size = 0; // REQUIRED

		return info;
	}
}

