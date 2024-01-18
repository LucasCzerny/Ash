#pragma once

#include "PipelineConfig.h"

#include "Vulkan/Context/Context.h"

namespace Ash::Vulkan
{
	class Pipeline
	{
	public:
        VkPipeline Handle = VK_NULL_HANDLE;
		VkPipelineLayout PipelineLayout = VK_NULL_HANDLE;
		VkRenderPass RenderPass = VK_NULL_HANDLE;

		std::vector<VkFramebuffer> Framebuffers;
		
	public:
		Pipeline(const PipelineConfig& config, std::function<void(const Pipeline&, VkCommandBuffer, uint32_t)> recordFunction);
		Pipeline(const ComputePipelineConfig& config, std::function<void(const Pipeline&, VkCommandBuffer, uint32_t)> recordFunction);
		
		// Not copyable or moveable
		Pipeline(const Pipeline&) = delete;
		void operator=(const Pipeline&) = delete;
		Pipeline(Pipeline&&) = delete;
		Pipeline& operator=(Pipeline&&) = delete;

		void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t currentFrame) const;

		operator VkPipeline() const { return Handle; }

	private:
		std::function<void(const Pipeline&, VkCommandBuffer, uint32_t)> m_RecordFunction = nullptr;

		Context& m_Context = Context::Get();

	private:
		void CreateGraphicsPipeline(const PipelineConfig& config);
		void CreateComputePipeline(const ComputePipelineConfig& config);

		VkShaderModule CreateShaderModule(const std::string& shaderSource);
		
		void CreateFramebuffers();
		void DestroyFramebuffers();
	};
}
