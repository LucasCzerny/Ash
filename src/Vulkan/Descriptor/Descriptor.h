#pragma once

#include "Vulkan/Context/Context.h"

namespace Ash::Vulkan
{
	struct Descriptor
	{
	public:
		VkDescriptorSetLayout Layout = VK_NULL_HANDLE;
		VkDescriptorSet Set = VK_NULL_HANDLE;

	public:
		Descriptor() = default;
		Descriptor(VkDescriptorSetLayout layout, VkDescriptorSet set);

		Descriptor(const VkDescriptorSetLayoutCreateInfo& layoutInfo);

		Descriptor(const Descriptor& descriptor);
		Descriptor(Descriptor&& descriptor) noexcept;
		Descriptor& operator=(const Descriptor& descriptor);
		Descriptor& operator=(Descriptor&& descriptor) noexcept;

		void Reset();
		bool IsEmpty() const { return Set == VK_NULL_HANDLE; }

		void Bind(VkCommandBuffer commandBuffer, VkPipelineBindPoint bindPoint, uint32_t firstSet, VkPipelineLayout layout);
		void Update(const VkDescriptorBufferInfo& bufferInfo, uint32_t binding, VkDescriptorType descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);
		void Update(const VkDescriptorImageInfo& imageInfo, uint32_t binding, VkDescriptorType descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);

		VkDescriptorSet* Pointer() { return &Set; }
		const VkDescriptorSet* Pointer() const { return (const VkDescriptorSet*)&Set; }

		operator VkDescriptorSet() const { return Set; }

		operator bool() const { return IsEmpty(); }

	private:
		std::shared_ptr<Context> m_Context = nullptr;
	};

	// Multiple descriptors with the same layout
	struct DescriptorGroup
	{
	public:
		VkDescriptorSetLayout Layout = VK_NULL_HANDLE;
		std::vector<VkDescriptorSet> Sets{};

	public:
		DescriptorGroup() = default;
		DescriptorGroup(VkDescriptorSetLayout layout, const std::vector<VkDescriptorSet>& sets);

		DescriptorGroup(const VkDescriptorSetLayoutCreateInfo& layoutInfo, uint32_t count);

		DescriptorGroup(const DescriptorGroup& descriptorGroup);
		DescriptorGroup(DescriptorGroup&& descriptorGroup) noexcept;
		DescriptorGroup& operator=(const DescriptorGroup& descriptorGroup);
		DescriptorGroup& operator=(DescriptorGroup&& descriptorGroup) noexcept;

		void Reset();
		bool IsEmpty() const { return Sets.size() == 0; }

		Descriptor operator[](int index);

	private:
		std::shared_ptr<Context> m_Context = nullptr;
	};
}