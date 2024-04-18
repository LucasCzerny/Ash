#pragma once

#include "Vulkan/Buffer/Buffer.h"

namespace Ash::Vulkan::Utility
{
	struct CubeVertex
	{
		glm::vec3 Position;
		glm::vec2 TexCoords;

		static std::array<Buffer, 2> CreateVertexBuffers();
		static Vulkan::Buffer CreateIndexBuffer();

		static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions();
		static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
	};
}
