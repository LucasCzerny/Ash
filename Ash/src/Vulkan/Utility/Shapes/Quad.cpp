#include "pch.h"
#include "Quad.h"

namespace Ash::Vulkan::Utility
{
	// TODO: add usage flags and memory property flags to the constructor
	std::array<Vulkan::Buffer, 2> QuadVertex::CreateVertexBuffers()
	{
		static const std::array<float, 4 * 2> positions = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f,
		};

		static const std::array<float, 4 * 2> texCoords = {
			 0.0f, 0.0f,
			 1.0f, 0.0f,
			 1.0f, 1.0f,
			 0.0f, 1.0f,
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

	Buffer QuadVertex::CreateIndexBuffer()
	{
		static const std::array<uint32_t, 6> indices = {
			0,  1,  2,  2,  3,  0,
		};

		return Buffer(
			indices.data(), indices.size(),
			BufferType::INDEX
		);
	}

	std::vector<VkVertexInputBindingDescription> QuadVertex::GetBindingDescriptions()
	{
		static std::vector<VkVertexInputBindingDescription> bindingDescriptions(2);

		bindingDescriptions[0].binding = 0;
		bindingDescriptions[0].stride = sizeof(glm::vec2);
		bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		bindingDescriptions[1].binding = 1;
		bindingDescriptions[1].stride = sizeof(glm::vec2);
		bindingDescriptions[1].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescriptions;
	}

	std::vector<VkVertexInputAttributeDescription> QuadVertex::GetAttributeDescriptions()
	{
		static std::vector<VkVertexInputAttributeDescription> attributeDescriptions(2);

		// Positions
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = 0;

		// TexCoords
		attributeDescriptions[1].binding = 1;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[1].offset = 0;

		return attributeDescriptions;
	}
}

