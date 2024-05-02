#pragma once

#include "PipelineConfig.h"

#include "Scene/Scene.h"

#include "Vulkan/Context/Context.h"

namespace Ash::Vulkan
{
	class Pipeline
	{
	public:
        VkPipeline Handle = VK_NULL_HANDLE;
		VkPipelineLayout Layout = VK_NULL_HANDLE;
		VkRenderPass RenderPass = VK_NULL_HANDLE;

		std::vector<VkFramebuffer> Framebuffers;
		
	public:
		Pipeline() = default;
		Pipeline(VkPipeline handle, VkPipelineLayout layout, VkRenderPass renderPass, const std::vector<VkFramebuffer> framebuffers = {});

		Pipeline(const PipelineConfig& config, std::function<void(const Pipeline&, VkCommandBuffer, uint32_t, uint32_t)> recordFunction);
		Pipeline(const PipelineConfig& config, std::function<void(const Pipeline&, VkCommandBuffer, uint32_t, uint32_t, Scene&)> recordFunction);
		Pipeline(const ComputePipelineConfig& config, std::function<void(const Pipeline&, VkCommandBuffer, uint32_t, uint32_t)> recordFunction);
		Pipeline(const ComputePipelineConfig& config, std::function<void(const Pipeline&, VkCommandBuffer, uint32_t, uint32_t, Scene&)> recordFunction);
		
		Pipeline(const Pipeline& pipeline);
		Pipeline(Pipeline&& pipeline) noexcept;
		Pipeline& operator=(const Pipeline& pipeline);
		Pipeline& operator=(Pipeline&& pipeline) noexcept;

		void Reset();
		bool IsEmpty() const { return Handle == VK_NULL_HANDLE; }

		void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t currentFrame, uint32_t imageIndex, Scene& scene = Scene()) const;

		operator VkPipeline() const { return Handle; }

	private:
		std::function<void(const Pipeline&, VkCommandBuffer, uint32_t, uint32_t)> m_RecordWithoutScene = nullptr;
		std::function<void(const Pipeline&, VkCommandBuffer, uint32_t, uint32_t, Scene&)> m_RecordWithScene = nullptr;

		std::shared_ptr<Context> m_Context = nullptr;

	private:
		void CreateGraphicsPipeline(const PipelineConfig& config);
		void CreateComputePipeline(const ComputePipelineConfig& config);

		VkShaderModule CreateShaderModule(const std::string& shaderSource);
		
		void CreateFramebuffers();
		void DestroyFramebuffers();
	};
}
