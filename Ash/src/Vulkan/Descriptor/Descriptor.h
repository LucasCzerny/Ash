#pragma once

#include "Model/Model.h"

namespace Ash::Vulkan
{
	struct Descriptor
	{
	public:
		VkDescriptorSetLayout Layout = VK_NULL_HANDLE;
		VkDescriptorSet Set = VK_NULL_HANDLE;

	public:
		Descriptor() = default;
		Descriptor(VkDescriptorSetLayout layout, VkDescriptorSet set)
			: Layout(layout), Set(set) {}

		Descriptor(const VkDescriptorSetLayoutCreateInfo& layoutInfo);

		void Bind(VkCommandBuffer commandBuffer, VkPipelineBindPoint bindPoint, uint32_t firstSet, VkPipelineLayout layout);
		void Update(const VkDescriptorBufferInfo& bufferInfo, uint32_t binding, VkDescriptorType descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);
		void Update(const VkDescriptorImageInfo& imageInfo, uint32_t binding, VkDescriptorType descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);

		operator VkDescriptorSet() const { return Set; }
	};

	// Multiple descriptors with the same layout
	struct DescriptorGroup
	{
	public:
		VkDescriptorSetLayout Layout = VK_NULL_HANDLE;
		std::vector<VkDescriptorSet> Sets{};

	public:
		DescriptorGroup() = default;
		DescriptorGroup(const VkDescriptorSetLayoutCreateInfo& layoutInfo, uint32_t count);

		Descriptor operator[](int index);
	};
}