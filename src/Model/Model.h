#pragma once

#include "Vulkan/Buffer/Buffer.h"
#include "Vulkan/Descriptor/Descriptor.h"

namespace Ash
{
	// TODO: maybe return std::array<VkBuffer*, 5>
	class Mesh
	{
	public:
		std::vector<glm::vec4> Positions, Normals, Tangents;
		std::vector<glm::vec2> TexCoords;

		std::vector<uint32_t> Indices;

		Vulkan::Buffer PositionsBuffer, NormalsBuffer, TangentsBuffer, TexCoordsBuffer, IndicesBuffer;

	public:
		Mesh() = default;
		Mesh(const std::vector<glm::vec4>& positions, const std::vector<glm::vec4>& normals, const std::vector<glm::vec4>& tangents, const std::vector<glm::vec2>& texCoords, const Vulkan::BufferType& bufferType);

		void Bind(VkCommandBuffer commandBuffer);

		std::array<Vulkan::Descriptor, 5> CreateDescriptors();
		std::array<Vulkan::DescriptorGroup, 5> CreateDescriptorGroups(uint32_t count);

	private:
		Vulkan::BufferType m_BufferType;

	private:
		void CreateBuffers();
		VkDescriptorSetLayoutBinding CreateAttributeBinding(VkBuffer* buffer, int binding);
	};

	class Model
	{
	public:
		Model(const fs::path& path, bool createBuffer = true);

		void Bind(VkCommandBuffer commandBuffer);

	private:
		tinygltf::Model m_Model;

		std::vector<Mesh> m_Meshes;

	private:
		void LoadGltfModel(const fs::path& path);

		void LoadNode(const tinygltf::Node& node);
		glm::mat4 ConvertNodeTransform(const tinygltf::Node& node);

		template <typename IndexType>
		void LoadIndices(tinygltf::Primitive& primitive, uint32_t indexStart, std::vector<uint32_t>& indices, size_t* countOut = nullptr);

		const float* GetPointerToAttribute(const std::string& attributeName,tinygltf::Primitive& primitive, size_t* countOut = nullptr);
		int GetIndexType(tinygltf::Primitive& primitive);

	public:
		class Iterator
		{
		public:
			explicit Iterator(std::vector<Mesh>::const_iterator it)
				: m_CurrentMesh(it) {}

			const Mesh& operator*() const
			{
				return *m_CurrentMesh;
			}

			Iterator& operator++()
			{
				m_CurrentMesh++;
				return *this;
			}

			bool operator!=(const Iterator& other) const
			{
				return m_CurrentMesh != other.m_CurrentMesh;
			}

		private:
			std::vector<Mesh>::const_iterator m_CurrentMesh;
		};

		Iterator begin() const
		{
			return Iterator(m_Meshes.begin());
		}

		Iterator end() const
		{
			return Iterator(m_Meshes.end());
		}
	};
}

#include "Model.inl"
