#include "pch.h"
#include "Cube.h"

namespace Ash::Vulkan::Utility
{
	// TODO: add usage flags and memory property flags to the constructor
	std::array<Buffer, 2> CubeVertex::CreateVertexBuffers()
	{
		static const std::array<float, 24 * 3> positions = {
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f,  0.5f,

			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
		};

		static const std::array<float, 24 * 2> texCoords = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f
		};

		return {
			Buffer(
				positions.data(), positions.size(),
                BufferType::VERTEX
			),

			Buffer(
				texCoords.data(), texCoords.size(),
                BufferType::VERTEX
			)
		};
	}

	Buffer CubeVertex::CreateIndexBuffer()
	{
		static const std::array<uint32_t, 6 * 6> indices = {
			0,  1,  2,  2,  3,  0,
			4,  5,  6,  6,  7,  4,
			8,  9,  10, 10, 11, 8,
			12, 13, 14, 14, 15, 12,
			16, 17, 18, 18, 19, 16,
			20, 21, 22, 22, 23, 20
		};

		return Buffer(
			indices.data(), indices.size(),
			BufferType::INDEX
		);
	}

	std::vector<VkVertexInputBindingDescription> CubeVertex::GetBindingDescriptions()
	{
		std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);

		bindingDescriptions[0].binding = 0;
		bindingDescriptions[0].stride = sizeof(CubeVertex);
		bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescriptions;
	}

	std::vector<VkVertexInputAttributeDescription> CubeVertex::GetAttributeDescriptions()
	{
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions(2);

		// Positions
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(CubeVertex, Position);

		// TexCoords
		attributeDescriptions[1].binding = 1;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(CubeVertex, TexCoords);

		return attributeDescriptions;
	}
}
