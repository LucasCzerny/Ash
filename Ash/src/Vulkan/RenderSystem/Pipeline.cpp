#include "pch.h"
#include "Pipeline.h"

#include "Core/Assert.h"

#include "Vulkan/Context/Context.h"
#include "Vulkan/Defaults/Defaults.h"

#include "Utility/File.h"

namespace Ash::Vulkan
{
	Pipeline::Pipeline(const PipelineConfig& config, std::function<void(const Pipeline&, VkCommandBuffer, uint32_t, uint32_t)> recordFunction)
		: m_RecordWithoutScene(recordFunction)
	{
		CreateGraphicsPipeline(config);
		CreateFramebuffers();
	}

	Pipeline::Pipeline(const PipelineConfig& config, std::function<void(const Pipeline&, VkCommandBuffer, uint32_t, uint32_t, Scene&)> recordFunction)
		: m_RecordWithScene(recordFunction)
	{
		CreateGraphicsPipeline(config);
		CreateFramebuffers();
	}

	Pipeline::Pipeline(const ComputePipelineConfig& config, std::function<void(const Pipeline&, VkCommandBuffer, uint32_t, uint32_t)> recordFunction)
		: m_RecordWithoutScene(recordFunction)
	{
		CreateComputePipeline(config);
		CreateFramebuffers();
	}

	Pipeline::Pipeline(const ComputePipelineConfig& config, std::function<void(const Pipeline&, VkCommandBuffer, uint32_t, uint32_t, Scene&)> recordFunction)
		: m_RecordWithScene(recordFunction)
	{
		CreateComputePipeline(config);
		CreateFramebuffers();
	}

	void Pipeline::RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t currentFrame, uint32_t imageIndex, Scene& scene) const
	{
		if (m_RecordWithoutScene != nullptr)
		{
			m_RecordWithoutScene(*this, commandBuffer, imageIndex, currentFrame);
		}
		else if (m_RecordWithScene != nullptr)
		{
			m_RecordWithScene(*this, commandBuffer, currentFrame, imageIndex, scene);
		}
		else
		{
			ASSERT(false, "A record function needs to be implemented.");
		}
	}

	void Pipeline::CreateGraphicsPipeline(const PipelineConfig& config)
	{
		static Context& context = Context::Get();

		VkResult result = vkCreateRenderPass(context.Device, &config.RenderPassInfo, nullptr, &RenderPass);
		ASSERT(result == VK_SUCCESS, "Failed to create the render pass.");

		result = vkCreatePipelineLayout(context.Device, &config.PipelineLayoutInfo, nullptr, &Layout);
		ASSERT(result == VK_SUCCESS, "Failed to create the pipeline layout.");

		ASSERT(config.VertexShaderPath != "", "You need to set the vertex shader before creating a pipeline.");
		ASSERT(config.FragmentShaderPath != "", "You need to set the fragment shader before creating a pipeline.");

		std::string vertexSource = Utility::ReadFile(config.VertexShaderPath);
		std::string fragmentSource = Utility::ReadFile(config.FragmentShaderPath);

		VkShaderModule vertexModule = CreateShaderModule(vertexSource);
		VkShaderModule fragmentModule = CreateShaderModule(fragmentSource);

		VkPipelineShaderStageCreateInfo shaderStageInfos[2]{};

		for (int i = 0; i < 2; i++)
		{
			shaderStageInfos[i].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			shaderStageInfos[i].pName = "main";
		}

		shaderStageInfos[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		shaderStageInfos[0].module = vertexModule;

		shaderStageInfos[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		shaderStageInfos[1].module = fragmentModule;

		std::vector<VkVertexInputBindingDescription> bindingDescriptions = config.BindingDescriptions;
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions = config.AttributeDescriptions;

		VkPipelineVertexInputStateCreateInfo vertexStateInfo{};
		vertexStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

		vertexStateInfo.vertexBindingDescriptionCount = (uint32_t)bindingDescriptions.size();
		vertexStateInfo.pVertexBindingDescriptions = bindingDescriptions.data();

		vertexStateInfo.vertexAttributeDescriptionCount = (uint32_t)attributeDescriptions.size();
		vertexStateInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

		VkGraphicsPipelineCreateInfo pipelineInfo{};
		{
			pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;

			pipelineInfo.stageCount = 2;
			pipelineInfo.pStages = shaderStageInfos;
			pipelineInfo.pVertexInputState = &vertexStateInfo;

			pipelineInfo.pViewportState = &config.ViewportInfo;
			pipelineInfo.pInputAssemblyState = &config.InputAssemblyInfo;
			pipelineInfo.pRasterizationState = &config.RasterizationInfo;
			pipelineInfo.pMultisampleState = &config.MultisampleInfo;
			pipelineInfo.pColorBlendState = &config.ColorBlendInfo;
			pipelineInfo.pDepthStencilState = &config.DepthStencilInfo;
			pipelineInfo.pDynamicState = &config.DynamicStateInfo;

			pipelineInfo.layout = Layout;
			pipelineInfo.renderPass = RenderPass;
			pipelineInfo.subpass = config.Subpass;

			pipelineInfo.basePipelineIndex = -1;
			pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
		}

		result = vkCreateGraphicsPipelines(context.Device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &Handle);
		ASSERT(result == VK_SUCCESS, "Failed to create the pipeline.");
	}

	void Pipeline::CreateComputePipeline(const ComputePipelineConfig& config)
	{
		static Context& context = Context::Get();

		VkComputePipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;

		pipelineInfo.layout = config.PipelineLayout;

		std::string shaderSource = Utility::ReadFile(config.ComputeShaderPath);
		VkShaderModule shaderModule = CreateShaderModule(shaderSource);

		VkPipelineShaderStageCreateInfo shaderStageInfo{};
		shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;

		shaderStageInfo.module = shaderModule;
		shaderStageInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;
		shaderStageInfo.pName = "main";

		pipelineInfo.stage = shaderStageInfo;

		pipelineInfo.basePipelineHandle = nullptr;

		VkResult result = vkCreateComputePipelines(context.Device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &Handle);
		ASSERT(result == VK_SUCCESS, "Failed to create a compute pipeline.");
	}

	VkShaderModule Pipeline::CreateShaderModule(const std::string& shaderSource)
	{
		static Context& context = Context::Get();

		VkShaderModuleCreateInfo moduleInfo{};
		moduleInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;

		moduleInfo.codeSize = shaderSource.size();
		moduleInfo.pCode = (const uint32_t*)shaderSource.c_str();

		VkShaderModule module;
		VkResult result = vkCreateShaderModule(context.Device, &moduleInfo, nullptr, &module);

		ASSERT(result == VK_SUCCESS, "Failed to create a shader module.");

		return module;
	}

	void Pipeline::CreateFramebuffers()
	{
		static Context& context = Context::Get();

		ASSERT(RenderPass != VK_NULL_HANDLE, "You need create a render pass before creating the framebuffers.");

		if (Framebuffers.size() != 0)
		{
			DestroyFramebuffers();
		}

		Framebuffers.resize(context.SwapChain.ImageCount);

		for (uint32_t i = 0; i < context.SwapChain.ImageCount; i++)
		{
			std::array<VkImageView, 2> attachments = { context.SwapChain.Images[i].View, context.SwapChain.DepthImages[i].View };

			VkFramebufferCreateInfo framebufferInfo = Defaults<VkFramebufferCreateInfo>();
			{
				framebufferInfo.attachmentCount = (uint32_t)attachments.size();
				framebufferInfo.pAttachments = attachments.data();

				framebufferInfo.renderPass = RenderPass;
			}

			VkResult result = vkCreateFramebuffer(context.Device, &framebufferInfo, nullptr, &Framebuffers[i]);
			ASSERT(result == VK_SUCCESS, "Failed to create a framebuffer.");
		}
	}

	void Pipeline::DestroyFramebuffers()
	{
		static Context& context = Context::Get();

		for (auto framebuffer : Framebuffers)
		{
			vkDestroyFramebuffer(context.Device, framebuffer, nullptr);
		}
	}
}