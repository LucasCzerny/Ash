#pragma once

#include <Ash.h>

using namespace Ash;

namespace SpinningCube::CubePipeline
{
	struct Data
	{
	public:
		Vulkan::Buffer VertexBuffer = Vulkan::Utility::CubeVertex::CreateVertexBuffer();
		Vulkan::Buffer IndexBuffer = Vulkan::Utility::CubeVertex::CreateIndexBuffer();

		Vulkan::DescriptorGroup CameraDescriptors;
		std::deque<Vulkan::Buffer> CameraUbos;

	public:
		static Data& Get();
	};

	struct CameraUboStruct
	{
		glm::mat4 Projection, View;
	};

	Vulkan::PipelineConfig CreateConfig();
	void Record(const Vulkan::Pipeline& pipeline, VkCommandBuffer commandBuffer, uint32_t currentFrame, uint32_t imageIndex, Scene& scene);

	static void CreateBuffers();
	static void CreateDescriptors();

	static VkPipelineLayoutCreateInfo CreateLayoutInfo();
	static VkRenderPassCreateInfo& CreateRenderPassInfo();
}
