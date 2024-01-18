#include "pch.h"
#include "Descriptor.h"

#include "Core/Assert.h"

#include "Vulkan/Context/Context.h"

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

	VkDescriptorSet DescriptorGroup::operator[](int index)
	{
		return Sets[index];
	}
}