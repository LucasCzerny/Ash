#include "pch.h"
#include "CubePipeline.h"

#include "Vulkan/Defaults.h"
#include "Vulkan/Context/Context.h"
#include "Vulkan/Utility/Shapes/Cube.h"

namespace SpinningCube
{
	CubePipelineData CubePipeline::s_Data;

	void CubePipeline::Init()
	{
		s_Data.VertexBuffer = Vulkan::Utility::CreateCubeVertexBuffer();
		s_Data.IndexBuffer = Vulkan::Utility::CreateCubeIndexBuffer();
	}

	Vulkan::PipelineConfig CubePipeline::CreatePipelineConfig()
	{
		// TODO: Maybe also use Vulkan::Defaults Syntax
		Vulkan::PipelineConfig config{};

        config.PipelineLayoutInfo = CreateCubePipelineLayoutInfo();
		config.RenderPassInfo = CreateCubePipelineRenderPassInfo();

		config.VertexShaderPath = "";
		config.FragmentShaderPath = "";

		return config;
	}

	void CubePipeline::Record(const Vulkan::Pipeline& pipeline, VkCommandBuffer commandBuffer, uint32_t imageIndex)
	{
		static Vulkan::Context& context = Vulkan::Context::Get();

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		VkResult result = vkBeginCommandBuffer(commandBuffer, &beginInfo);
		ASSERT(result == VK_SUCCESS, "Failed to start recording a command buffer.");

		VkExtent2D swapChainExtent = context.SwapChain.Extent;

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;

		renderPassInfo.framebuffer = pipeline.Framebuffers[imageIndex];
		renderPassInfo.renderPass = pipeline.RenderPass;

		renderPassInfo.renderArea.extent = swapChainExtent;
		renderPassInfo.renderArea.offset = { 0, 0 };

		std::array<VkClearValue, 2> clearValues = { {
			{ 0.1f, 0.1f, 0.1f, 1.0f },
			{ 1.0f, 0 }
		} };

		renderPassInfo.clearValueCount = (uint32_t)clearValues.size();
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport viewport{};

		viewport.x = 0.0f;
		viewport.width = (float)swapChainExtent.width;

		// Flipping the viewport
		viewport.y = (float)swapChainExtent.height;
		viewport.height = -(float)swapChainExtent.height;

		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		VkRect2D scissor{};

		scissor.offset = { 0, 0 };
		scissor.extent = swapChainExtent;

		vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
		vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

		static VkDeviceSize offset = 0;
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, s_Data.VertexBuffer.Pointer(), &offset);
		vkCmdBindIndexBuffer(commandBuffer, s_Data.IndexBuffer, 0, VK_INDEX_TYPE_UINT32);

		vkCmdDrawIndexed(commandBuffer, (uint32_t)(s_Data.IndexBuffer.Size / sizeof(uint32_t)), 1, 0, 0, 0);

		vkCmdEndRenderPass(commandBuffer);

		result = vkEndCommandBuffer(commandBuffer);
		ASSERT(result == VK_SUCCESS, "Failed to record a command buffer.");
	}

	VkPipelineLayoutCreateInfo CubePipeline::CreateCubePipelineLayoutInfo()
	{
        VkPipelineLayoutCreateInfo layoutInfo = Vulkan::Defaults<VkPipelineLayoutCreateInfo>();
		{
			std::vector<VkDescriptorSetLayout> layouts = {};

			layoutInfo.setLayoutCount = (uint32_t)layouts.size();
			layoutInfo.pSetLayouts = layouts.data();
		}

		return layoutInfo;
	}

	VkRenderPassCreateInfo CubePipeline::CreateCubePipelineRenderPassInfo()
	{
		static Vulkan::Context& context = Vulkan::Context::Get();

		VkAttachmentDescription colorAttachment = Vulkan::Defaults<VkAttachmentDescription>();
		VkAttachmentReference colorReference = Vulkan::Defaults<VkAttachmentReference>();
		colorReference.attachment = 0;

		VkAttachmentDescription depthAttachment = Vulkan::Defaults<VkAttachmentDescription>();;
		depthAttachment.format = context.SwapChain.DepthFormat;
		depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkAttachmentReference depthReference = Vulkan::Defaults<VkAttachmentReference>();
		depthReference.attachment = 1;
		depthReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpassDescription = Vulkan::Defaults<VkSubpassDescription>();
		{
			subpassDescription.colorAttachmentCount = 1;
			subpassDescription.pColorAttachments = &colorReference;

			subpassDescription.pDepthStencilAttachment = &depthReference;
		}

		VkSubpassDependency subpassDependency = Vulkan::Defaults<VkSubpassDependency>();
		{
			subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
			subpassDependency.dstSubpass = 0;

			subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
			subpassDependency.srcAccessMask = NULL;

			subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
			subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		}

		VkRenderPassCreateInfo renderPassInfo = Vulkan::Defaults<VkRenderPassCreateInfo>();
		{
			std::array<VkAttachmentDescription, 2> attachments = { colorAttachment, depthAttachment };

			renderPassInfo.attachmentCount = (uint32_t)attachments.size();
			renderPassInfo.pAttachments = attachments.data();

			renderPassInfo.dependencyCount = 1;
			renderPassInfo.pDependencies = &subpassDependency;

			renderPassInfo.subpassCount = 1;
			renderPassInfo.pSubpasses = &subpassDescription;
		}

		return renderPassInfo;
	}
}
