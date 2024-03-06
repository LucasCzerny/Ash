#pragma once

namespace Ash::Vulkan
{
	struct Descriptor
	{
	public:
		VkDescriptorSetLayout Layout = VK_NULL_HANDLE;
		VkDescriptorSet Set = VK_NULL_HANDLE;

	public:
		Descriptor() = default;
		Descriptor(const VkDescriptorSetLayoutCreateInfo& layoutInfo);

		// Not copyable or moveable
		// Descriptor(const Descriptor&) = delete;
		// void operator=(const Descriptor&) = delete;
		// Descriptor(Descriptor&&) = delete;
		// Descriptor& operator=(Descriptor&&) = delete;

		void Bind(VkCommandBuffer commandBuffer, VkPipelineBindPoint bindPoint, uint32_t firstSet, VkPipelineLayout layout);

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

		// Not copyable or moveable
		DescriptorGroup(const DescriptorGroup&) = delete;
		void operator=(const DescriptorGroup&) = delete;
		DescriptorGroup(DescriptorGroup&&) = delete;
		DescriptorGroup& operator=(DescriptorGroup&&) = delete;

		VkDescriptorSet operator[](int index);
	};
}