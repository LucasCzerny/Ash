#pragma once

#include "Vulkan/Buffer/Buffer.h"

namespace Ash::Vulkan::Utility
{
	struct QuadVertex
	{
		glm::vec2 Position;
		glm::vec2 TexCoords;

		static Vulkan::Buffer CreateVertexBuffer();
		static Vulkan::Buffer CreateIndexBuffer();

		static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions();
		static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
	};
}
