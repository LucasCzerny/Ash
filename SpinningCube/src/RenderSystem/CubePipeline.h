#pragma once

#include <Ash.h>

using namespace Ash;

namespace SpinningCube
{
	struct CubePipelineData
	{
		Vulkan::Buffer VertexBuffer, IndexBuffer;

		CubePipelineData();
	};

	class CubePipeline
	{
	public:
		static CubePipelineData s_Data;

	public:
		static Vulkan::PipelineConfig CreatePipelineConfig();
		static void Record(const Vulkan::Pipeline& pipeline, VkCommandBuffer commandBuffer, uint32_t imageIndex);

	private:
		static VkPipelineLayoutCreateInfo CreateCubePipelineLayoutInfo();
		static VkRenderPassCreateInfo CreateCubePipelineRenderPassInfo();
	};
}
