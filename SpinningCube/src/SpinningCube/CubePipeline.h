#pragma once

#include <Ash.h>

using namespace Ash;

namespace SpinningCube::CubePipeline
{
	struct Data
	{
	public:
		Vulkan::Buffer VertexBuffer = Vulkan::Utility::CreateCubeVertexBuffer();
		Vulkan::Buffer IndexBuffer = Vulkan::Utility::CreateCubeIndexBuffer();

		Vulkan::Descriptor CameraDescriptor;
		Vulkan::Buffer CameraUbo;

	public:
		static Data& Get();
	};

	struct CameraUboStruct
	{
		glm::mat4 Projection, View;
	};

	Vulkan::PipelineConfig CreateConfig();
	void Record(const Vulkan::Pipeline& pipeline, VkCommandBuffer commandBuffer, uint32_t imageIndex, Scene& scene);

	static void CreateDescriptor();
	static void CreateBuffer();

	static VkPipelineLayoutCreateInfo CreateLayoutInfo();
	static VkRenderPassCreateInfo& CreateRenderPassInfo();
}
