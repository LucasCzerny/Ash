#include "pch.h"
#include "Descriptor.h"

#include "Core/Assert.h"

#include "Vulkan/Context/Context.h"
#include "Vulkan/Defaults/Defaults.h"

namespace Ash::Vulkan
{
	Descriptor::Descriptor(VkDescriptorSetLayout layout, VkDescriptorSet set)
		: Layout(layout), Set(set) {}

	Descriptor::Descriptor(const VkDescriptorSetLayoutCreateInfo& layoutInfo)
	{
		VkResult result = vkCreateDescriptorSetLayout(m_Context->Device, &layoutInfo, nullptr, &Layout);
		ASSERT(result == VK_SUCCESS, "Failed to create a descriptor set layout.");

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;

		allocInfo.descriptorPool = m_Context->DescriptorPool;
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts = &Layout;

		result = vkAllocateDescriptorSets(m_Context->Device, &allocInfo, &Set);
		ASSERT(result == VK_SUCCESS, "Failed to allocate descriptor sets.");
	}

	Descriptor::Descriptor(const Descriptor& descriptor)
		: Descriptor(descriptor.Layout, descriptor.Set)
	{
		Log::Info("Descriptor was just copied at line ", __LINE__, " in file ", __FILE__);
	}

	Descriptor::Descriptor(Descriptor&& descriptor) noexcept
		: Descriptor(descriptor.Layout, descriptor.Set)
	{
		descriptor.Reset();
	}

	Descriptor& Descriptor::operator=(const Descriptor& descriptor)
	{
		*this = Descriptor(descriptor.Layout, descriptor.Set);
		Log::Info("Descriptor was just copied at line ", __LINE__, " in file ", __FILE__);

		return *this;
	}

	Descriptor& Descriptor::operator=(Descriptor&& descriptor) noexcept
	{
		Layout = descriptor.Layout;
		Set = descriptor.Set;

		descriptor.Reset();

		return *this;
	}

	void Descriptor::Reset()
	{
		Layout = VK_NULL_HANDLE;
		Set = VK_NULL_HANDLE;
	}

	void Descriptor::Bind(VkCommandBuffer commandBuffer, VkPipelineBindPoint bindPoint, uint32_t firstSet, VkPipelineLayout layout)
	{
		vkCmdBindDescriptorSets(commandBuffer, bindPoint, layout, firstSet, 1, &Set, 0, nullptr);
	}

	void Descriptor::Update(const VkDescriptorBufferInfo& bufferInfo, uint32_t binding, VkDescriptorType descriptorType)
	{
		VkWriteDescriptorSet writeDescriptor = Defaults<VkWriteDescriptorSet>();
		{
			writeDescriptor.dstSet = Set;
			writeDescriptor.dstBinding = binding;
			writeDescriptor.descriptorCount = 1;
			writeDescriptor.descriptorType = descriptorType;

			writeDescriptor.pBufferInfo = &bufferInfo;
		}

		vkUpdateDescriptorSets(m_Context->Device, 1, &writeDescriptor, 0, nullptr);
	}

	void Descriptor::Update(const VkDescriptorImageInfo& imageInfo, uint32_t binding, VkDescriptorType descriptorType)
	{
		VkWriteDescriptorSet writeDescriptor = Defaults<VkWriteDescriptorSet>();
		{
			writeDescriptor.dstSet = Set;
			writeDescriptor.dstBinding = binding;
			writeDescriptor.descriptorCount = 1;
			writeDescriptor.descriptorType = descriptorType;

			writeDescriptor.pImageInfo = &imageInfo;
		}

		vkUpdateDescriptorSets(m_Context->Device, 1, &writeDescriptor, 0, nullptr);
	}

	DescriptorGroup::DescriptorGroup(VkDescriptorSetLayout layout, const std::vector<VkDescriptorSet>& sets)
		: Layout(layout), Sets(sets) {}

	DescriptorGroup::DescriptorGroup(const VkDescriptorSetLayoutCreateInfo& layoutInfo, uint32_t count)
	{
		VkResult result = vkCreateDescriptorSetLayout(m_Context->Device, &layoutInfo, nullptr, &Layout);
		ASSERT(result == VK_SUCCESS, "Failed to create a descriptor set layout.");

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;

		allocInfo.descriptorPool = m_Context->DescriptorPool;
		allocInfo.descriptorSetCount = count;

		std::vector<VkDescriptorSetLayout> layouts(count, Layout);
		allocInfo.pSetLayouts = layouts.data();

		Sets.resize(count);
		result = vkAllocateDescriptorSets(m_Context->Device, &allocInfo, Sets.data());

		ASSERT(result == VK_SUCCESS, "Failed to allocate descriptor sets.");
	}

	DescriptorGroup::DescriptorGroup(const DescriptorGroup& descriptorGroup)
		: DescriptorGroup(descriptorGroup.Layout, descriptorGroup.Sets)
	{
		Log::Info("Descriptor was just copied at line ", __LINE__, " in file ", __FILE__);
	}

	DescriptorGroup::DescriptorGroup(DescriptorGroup&& descriptorGroup) noexcept
		: DescriptorGroup(descriptorGroup.Layout, descriptorGroup.Sets)
	{
		descriptorGroup.Reset();
	}

	DescriptorGroup& DescriptorGroup::operator=(const DescriptorGroup& descriptorGroup)
	{
		*this = DescriptorGroup(descriptorGroup.Layout, descriptorGroup.Sets);
		Log::Info("Descriptor was just copied at line ", __LINE__, " in file ", __FILE__);

		return *this;
	}

	DescriptorGroup& DescriptorGroup::operator=(DescriptorGroup&& descriptorGroup) noexcept
	{
		Layout = descriptorGroup.Layout;
		Sets = descriptorGroup.Sets;

		descriptorGroup.Reset();

		return *this;
	}

	void DescriptorGroup::Reset()
	{
		Layout = VK_NULL_HANDLE;
		Sets.clear();
	}

	Descriptor DescriptorGroup::operator[](int index)
	{
		return Descriptor{ Layout, Sets[index] };
	}
}