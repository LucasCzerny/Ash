#include "pch.h"
#include "Model.h"

#include "Core/Assert.h"

#include "Vulkan/Defaults/Defaults.h"

namespace Ash
{
	Mesh::Mesh(const std::vector<glm::vec4>& positions, const std::vector<glm::vec4>& normals, const std::vector<glm::vec4>& tangents, const std::vector<glm::vec2>& texCoords, const Vulkan::BufferType& bufferType)
		: Positions(positions), Normals(normals), Tangents(tangents), TexCoords(texCoords), m_BufferType(bufferType)
	{
		CreateBuffers();
	}

	void Mesh::Bind(VkCommandBuffer commandBuffer) 
	{
		static VkDeviceSize offset = 0;

		std::array<VkBuffer*, 5> buffers = { PositionsBuffer.Pointer(), NormalsBuffer.Pointer(), TangentsBuffer.Pointer(), TexCoordsBuffer.Pointer(), IndicesBuffer.Pointer() };

		for (uint32_t i = 0; i < buffers.size(); i++)
		{
			vkCmdBindVertexBuffers(commandBuffer, i, 1, buffers[i], &offset);
		}
	}

	std::array<Vulkan::Descriptor, 5> Mesh::CreateDescriptors()
	{
		ASSERT(m_BufferType == Vulkan::BufferType::UBO || m_BufferType == Vulkan::BufferType::SSBO, "Can only create descriptors for UBO's or SSBO's.");

		std::array<VkBuffer*, 5> buffers = { PositionsBuffer.Pointer(), NormalsBuffer.Pointer(), TangentsBuffer.Pointer(), TexCoordsBuffer.Pointer(), IndicesBuffer.Pointer() };
		std::array<Vulkan::Descriptor, 5> result;

		for (uint32_t i = 0; i < buffers.size(); i++)
		{
			VkDescriptorSetLayoutBinding attributeBinding = CreateAttributeBinding(buffers[i], i);
		
			VkDescriptorSetLayoutCreateInfo layoutInfo = Vulkan::Defaults<VkDescriptorSetLayoutCreateInfo>();
			{
				layoutInfo.bindingCount = 1;
				layoutInfo.pBindings = &attributeBinding;
			}

			result[i] = Vulkan::Descriptor(layoutInfo);
		}

		return result;
	}

	std::array<Vulkan::DescriptorGroup, 5> Mesh::CreateDescriptorGroups(uint32_t count)
	{
		ASSERT(m_BufferType == Vulkan::BufferType::UBO || m_BufferType == Vulkan::BufferType::SSBO, "Can only create descriptors for UBO's or SSBO's.");

		std::array<VkBuffer*, 5> buffers = { PositionsBuffer.Pointer(), NormalsBuffer.Pointer(), TangentsBuffer.Pointer(), TexCoordsBuffer.Pointer(), IndicesBuffer.Pointer() };
		std::array<Vulkan::DescriptorGroup, 5> result;

		for (uint32_t i = 0; i < buffers.size(); i++)
		{
			VkDescriptorSetLayoutBinding attributeBinding = CreateAttributeBinding(buffers[i], i);
		
			VkDescriptorSetLayoutCreateInfo layoutInfo = Vulkan::Defaults<VkDescriptorSetLayoutCreateInfo>();
			{
				layoutInfo.bindingCount = 1;
				layoutInfo.pBindings = &attributeBinding;
			}

			result[i] = Vulkan::DescriptorGroup(layoutInfo, count);
		}

		return result;
	}

	void Mesh::CreateBuffers()
	{
		PositionsBuffer = Vulkan::Buffer(
			Positions,
			m_BufferType
		);

		NormalsBuffer = Vulkan::Buffer(
			Normals,
			m_BufferType
		);
		
		TangentsBuffer = Vulkan::Buffer(
			Tangents,
			m_BufferType
		);

		TexCoordsBuffer = Vulkan::Buffer(
			TexCoords,
			m_BufferType
		);

		IndicesBuffer = Vulkan::Buffer(
			Indices,
			m_BufferType
		);
	}

	VkDescriptorSetLayoutBinding Mesh::CreateAttributeBinding(VkBuffer* buffer, int binding)
	{
		VkDescriptorSetLayoutBinding attributeBinding = Vulkan::Defaults<VkDescriptorSetLayoutBinding>();
		{
			attributeBinding.binding = binding;

			switch (m_BufferType)
			{
				case Vulkan::BufferType::UBO:
				{
					attributeBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				}
				case Vulkan::BufferType::SSBO:
				{
					attributeBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				}
			}

			attributeBinding.descriptorCount = 1;
			attributeBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_COMPUTE_BIT;
		}

		return attributeBinding;
	}

	Model::Model(const fs::path& path, bool createBuffer)
	{
		LoadGltfModel(path);

		int defaultSceneIndex = m_Model.defaultScene == -1 ? 0 : m_Model.defaultScene;
		tinygltf::Scene defaultScene = m_Model.scenes[defaultSceneIndex];

		for (int nodeIndex : defaultScene.nodes)
		{
			LoadNode(m_Model.nodes[nodeIndex]);
		}
	}

	void Model::Bind(VkCommandBuffer commandBuffer)
	{
		for (Mesh& mesh : m_Meshes)
		{
			mesh.Bind(commandBuffer);
		}
	}

	void Model::LoadGltfModel(const fs::path& path)
	{
		static tinygltf::TinyGLTF loader;

		bool ret;
		std::string error, warn;

		ASSERT(path.has_extension(), "Invalid file extension. Must either be .gltf or .glb.");

		fs::path extension = path.extension();

		if (extension == ".gltf")
		{
			ret = loader.LoadASCIIFromFile(&m_Model, &error, &warn, path.string());
		}
		else if (extension == ".glb")
		{
			ret = loader.LoadBinaryFromFile(&m_Model, &error, &warn, path.string());
		}
		else
		{
			ASSERT(false, "Invalid file extension. Must either be .gltf or .glb.")
		}

		if (!warn.empty())
		{
			Log::Warn(warn);
		}

		if (!error.empty())
		{
			Log::Error(error);
		}

		ASSERT(ret == true, "Failed to parse the glTF model.");
	}

	void Model::LoadNode(const tinygltf::Node& node)
	{
		if (node.mesh < 0)
		{
			return;
		}

		glm::mat4 transform = ConvertNodeTransform(node);
		glm::mat4 normalMatrix = glm::inverse(glm::transpose(transform));

		tinygltf::Mesh& mesh = m_Model.meshes[node.mesh];
		Mesh result;


		for (tinygltf::Primitive& primitive : mesh.primitives)
		{
			size_t vertexCount;

			const float* positionBuffer = GetPointerToAttribute("POSITION",primitive, &vertexCount);
			const float* normalsBuffer = GetPointerToAttribute("NORMAL", primitive);
			const float* tangentsBuffer = GetPointerToAttribute("TANGENT", primitive);
			const float* texCoordsBuffer = GetPointerToAttribute("TEXCOORD_0", primitive);

			for (size_t i = 0; i < vertexCount; i++)
			{
				result.Positions.push_back(transform * glm::vec4(glm::make_vec3(&positionBuffer[i * 3]), 1.0f));
				result.Normals.push_back(normalMatrix * glm::vec4(glm::make_vec3(&normalsBuffer[i * 3]), 0.0f));
				result.Tangents.push_back(glm::make_vec4(&tangentsBuffer[i * 4]));
				result.TexCoords.push_back(glm::make_vec2(&texCoordsBuffer[i * 2]));
			}

			int indexType = GetIndexType(primitive);
			size_t indexCount;

			switch (indexType)
			{
				case TINYGLTF_PARAMETER_TYPE_UNSIGNED_BYTE:
				{
					LoadIndices<uint8_t>(primitive, 0, result.Indices);
					break;
				}

				case TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT:
				{
					LoadIndices<uint16_t>(primitive, 0, result.Indices);
					break;
				}

				case TINYGLTF_PARAMETER_TYPE_UNSIGNED_INT:
				{
					LoadIndices<uint32_t>(primitive, 0, result.Indices);
					break;
				}

				default:
				{
					ASSERT(false, "Unsupported index data type.");
				}
			}
		}

		m_Meshes.push_back(result);
	}

	glm::mat4 Model::ConvertNodeTransform(const tinygltf::Node& node)
	{
		glm::mat4 transform(1.0f);

		if (node.translation.size() == 3)
		{
			glm::vec3 translation = glm::make_vec3(node.translation.data());
			transform = glm::translate(transform, translation);
		}

		if (node.rotation.size() == 4)
		{
			glm::quat q;

			// gltf order: xyzw
			// glm order: wxyz
			// w ... scalar
			for (int i = 0; i < 4; i++)
			{
				q[i] = node.rotation[(i + 3) % 4];
			}

			transform *= glm::toMat4(q);
		}

		if (node.scale.size() == 3)
		{
			glm::vec3 scale = glm::make_vec3(node.scale.data());
			transform = glm::scale(transform, scale);

		}

		if (node.matrix.size() == 16)
		{
			transform = glm::make_mat4(node.matrix.data());
		}

		return transform;
	}

	const float* Model::GetPointerToAttribute(const std::string& attributeName, tinygltf::Primitive& primitive, size_t* countOut)
	{
		const tinygltf::Accessor& accessor = m_Model.accessors[primitive.attributes[attributeName]];

		// todo: use default data instead
		if (primitive.attributes.find(attributeName) == primitive.attributes.end())
		{
			Log::Warn("Model is missing attribute ", attributeName, ".");
			return nullptr;
		}

		const tinygltf::BufferView& bufferView = m_Model.bufferViews[accessor.bufferView];
		const tinygltf::Buffer& buffer = m_Model.buffers[bufferView.buffer];

		if (countOut)
		{
			*countOut = accessor.count;
		}

		return (const float*)(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);
	}

	int Model::GetIndexType(tinygltf::Primitive& primitive)
	{
		const tinygltf::Accessor& accessor = m_Model.accessors[primitive.indices];
		return accessor.componentType;
	}
}
