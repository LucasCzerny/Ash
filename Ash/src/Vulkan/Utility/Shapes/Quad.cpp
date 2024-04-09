#include "pch.h"
#include "Quad.h"

namespace Ash::Vulkan::Utility
{
	// TODO: add usage flags and memory property flags to the constructor
	Buffer QuadVertex::CreateVertexBuffer()
	{
		static std::array<float, 4 * (2 + 2)> vertices = {
			-0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f,
		};

		return Buffer(
			vertices,
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
		);
	}

	Buffer QuadVertex::CreateIndexBuffer()
	{
		static std::array<uint32_t, 6> indices = {
			0,  1,  2,  2,  3,  0,
		};

		return Buffer(
			indices,
			VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
		);
	}

	std::vector<VkVertexInputBindingDescription> QuadVertex::GetBindingDescriptions()
	{
		std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);

		bindingDescriptions[0].binding = 0;
		bindingDescriptions[0].stride = sizeof(QuadVertex);
		bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescriptions;
	}

	std::vector<VkVertexInputAttributeDescription> QuadVertex::GetAttributeDescriptions()
	{
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions(2);

		// Position
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(QuadVertex, Position);

		// TexCoords
		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(QuadVertex, TexCoords);

		return attributeDescriptions;
	}
}
