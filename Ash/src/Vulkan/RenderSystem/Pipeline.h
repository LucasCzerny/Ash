#pragma once

#include "PipelineConfig.h"

#include "Scene/Scene.h"

namespace Ash::Vulkan
{
	class Context;

	class Pipeline
	{
	public:
        VkPipeline Handle = VK_NULL_HANDLE;
		VkPipelineLayout Layout = VK_NULL_HANDLE;
		VkRenderPass RenderPass = VK_NULL_HANDLE;

		std::vector<VkFramebuffer> Framebuffers;
		
	public:
		Pipeline() = default;

		Pipeline(const PipelineConfig& config, std::function<void(const Pipeline&, VkCommandBuffer, uint32_t, uint32_t)> recordFunction);
		Pipeline(const PipelineConfig& config, std::function<void(const Pipeline&, VkCommandBuffer, uint32_t, uint32_t, Scene&)> recordFunction);
		Pipeline(const ComputePipelineConfig& config, std::function<void(const Pipeline&, VkCommandBuffer, uint32_t, uint32_t)> recordFunction);
		Pipeline(const ComputePipelineConfig& config, std::function<void(const Pipeline&, VkCommandBuffer, uint32_t, uint32_t, Scene&)> recordFunction);
		
		// Not copyable or moveable
		// Pipeline(const Pipeline&) = delete;
		// void operator=(const Pipeline&) = delete;
		// Pipeline(Pipeline&&) noexcept {}
		// Pipeline& operator=(Pipeline&&) noexcept {}

		void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t currentFrame, uint32_t imageIndex, Scene& scene = Scene()) const;

		operator VkPipeline() const { return Handle; }

	private:
		std::function<void(const Pipeline&, VkCommandBuffer, uint32_t, uint32_t)> m_RecordWithoutScene = nullptr;
		std::function<void(const Pipeline&, VkCommandBuffer, uint32_t, uint32_t, Scene&)> m_RecordWithScene = nullptr;

	private:
		void CreateGraphicsPipeline(const PipelineConfig& config);
		void CreateComputePipeline(const ComputePipelineConfig& config);

		VkShaderModule CreateShaderModule(const std::string& shaderSource);
		
		void CreateFramebuffers();
		void DestroyFramebuffers();
	};
}
