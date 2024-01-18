#pragma once

#include "Vulkan/Buffer/Buffer.h"

namespace Ash::Vulkan::Utility
{
	Vulkan::Buffer CreateQuadVertexBuffer();
	Vulkan::Buffer CreateQuadIndexBuffer();

	struct QuadVertex
	{
		glm::vec2 Position;
		glm::vec2 TexCoords;

		static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions();
		static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
	};
}
