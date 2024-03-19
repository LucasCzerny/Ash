#include "pch.h"
#include "Descriptor.h"

#include "Core/Assert.h"

#include "Vulkan/Context/Context.h"
#include "Vulkan/Defaults/Defaults.h"

namespace Ash::Vulkan
{
	Descriptor::Descriptor(const VkDescriptorSetLayoutCreateInfo& layoutInfo)
	{
		static Context& context = Context::Get();

		VkResult result = vkCreateDescriptorSetLayout(context.Device, &layoutInfo, nullptr, &Layout);
		ASSERT(result == VK_SUCCESS, "Failed to create a descriptor set layout.");

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;

		allocInfo.descriptorPool = context.DescriptorPool;
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts = &Layout;

		result = vkAllocateDescriptorSets(context.Device, &allocInfo, &Set);
		ASSERT(result == VK_SUCCESS, "Failed to allocate descriptor sets.");
	}

	void Descriptor::Bind(VkCommandBuffer commandBuffer, VkPipelineBindPoint bindPoint, uint32_t firstSet, VkPipelineLayout layout)
	{
		vkCmdBindDescriptorSets(commandBuffer, bindPoint, layout, firstSet, 1, &Set, 0, nullptr);
	}

	void Descriptor::Update(const VkDescriptorBufferInfo& bufferInfo, uint32_t binding, VkDescriptorType descriptorType)
	{
		static Context& context = Context::Get();

		VkWriteDescriptorSet writeDescriptor = Defaults<VkWriteDescriptorSet>();
		{
			writeDescriptor.dstSet = Set;
			writeDescriptor.dstBinding = binding;
			writeDescriptor.descriptorCount = 1;
			writeDescriptor.descriptorType = descriptorType;

			writeDescriptor.pBufferInfo = &bufferInfo;
		}

		vkUpdateDescriptorSets(context.Device, 1, &writeDescriptor, 0, nullptr);
	}

	void Descriptor::Update(const VkDescriptorImageInfo& imageInfo, uint32_t binding, VkDescriptorType descriptorType)
	{
		static Context& context = Context::Get();

		VkWriteDescriptorSet writeDescriptor = Defaults<VkWriteDescriptorSet>();
		{
			writeDescriptor.dstSet = Set;
			writeDescriptor.dstBinding = binding;
			writeDescriptor.descriptorCount = 1;
			writeDescriptor.descriptorType = descriptorType;

			writeDescriptor.pImageInfo = &imageInfo;
		}

		vkUpdateDescriptorSets(context.Device, 1, &writeDescriptor, 0, nullptr);
	}

	DescriptorGroup::DescriptorGroup(const VkDescriptorSetLayoutCreateInfo& layoutInfo, uint32_t count)
	{
		static Context& context = Context::Get();

		VkResult result = vkCreateDescriptorSetLayout(context.Device, &layoutInfo, nullptr, &Layout);
		ASSERT(result == VK_SUCCESS, "Failed to create a descriptor set layout.");

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;

		allocInfo.descriptorPool = context.DescriptorPool;
		allocInfo.descriptorSetCount = count;

		std::vector<VkDescriptorSetLayout> layouts(count, Layout);
		allocInfo.pSetLayouts = layouts.data();

		Sets.resize(count);
		result = vkAllocateDescriptorSets(context.Device, &allocInfo, Sets.data());

		ASSERT(result == VK_SUCCESS, "Failed to allocate descriptor sets.");
	}

	Descriptor DescriptorGroup::operator[](int index)
	{
		return Descriptor{ Layout, Sets[index] };
	}
}