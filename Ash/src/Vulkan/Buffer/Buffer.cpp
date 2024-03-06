#include "pch.h"
#include "Buffer.h"

#include "Core/Assert.h"

#include "Vulkan/Context/Context.h"
#include "Vulkan/Defaults.h"

namespace Ash::Vulkan
{
	static Context& context = Context::Get();

	Buffer::Buffer(VkBuffer handle, VkDeviceMemory memory, uint32_t size, void* mappedMemory)
		: Handle(handle), Memory(memory), Size(size), MappedMemory(mappedMemory) {}

	Buffer::Buffer(VkDeviceSize instanceSize, uint32_t instanceCount, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment)
	{
		VkDeviceSize alignmentSize = GetAlignment(instanceSize, minOffsetAlignment);
		Size = (uint32_t)alignmentSize * instanceCount;

		VkBufferCreateInfo bufferInfo{};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = Size;
		bufferInfo.usage = usageFlags;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		VkResult result = vkCreateBuffer(context.Device, &bufferInfo, nullptr, &Handle);
		ASSERT(result == VK_SUCCESS, "Failed to create the buffer.");

		VkMemoryRequirements memoryRequirements;
		vkGetBufferMemoryRequirements(context.Device, Handle, &memoryRequirements);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;

		allocInfo.allocationSize = memoryRequirements.size;
		allocInfo.memoryTypeIndex = FindMemoryType(context.Device, memoryRequirements.memoryTypeBits, memoryPropertyFlags);

		result = vkAllocateMemory(context.Device, &allocInfo, nullptr, &Memory);
		ASSERT(result == VK_SUCCESS, "Failed to allocate memory for the buffer.");

		vkBindBufferMemory(context.Device, Handle, Memory, 0);
	}

	Buffer::Buffer(VkDeviceSize instanceSize, uint32_t instanceCount, void* data, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment)
		: Buffer(instanceSize, instanceCount, usageFlags, memoryPropertyFlags, minOffsetAlignment)
	{
		CopyData(data);
	}

	Buffer::~Buffer()
	{
		vkDestroyBuffer(context.Device, Handle, nullptr);
		Unmap();
	}

	void Buffer::CopyData(void* data)
	{
		Map();
		memcpy(MappedMemory, data, Size);
		Unmap();
	}

	void Buffer::Map(uint32_t offset)
	{
		VkResult result = vkMapMemory(context.Device, Memory, offset, Size, NULL, &MappedMemory);
		ASSERT(result == VK_SUCCESS, "Failed to map the buffer memory.");
	}

	void Buffer::Unmap()
	{
		vkUnmapMemory(context.Device, Memory);
	}

	void Buffer::WriteToDescriptor(VkDescriptorType type, const Descriptor& descriptor)
	{
		static Context& context = Context::Get();

		VkDescriptorBufferInfo bufferInfo = Defaults<VkDescriptorBufferInfo>();
		{
			bufferInfo.buffer = Handle;
			bufferInfo.range = Size;
		}

		VkWriteDescriptorSet writeDescriptor = Vulkan::Defaults<VkWriteDescriptorSet>();
		{
			writeDescriptor.dstSet = descriptor;
			writeDescriptor.dstBinding = 0;
			writeDescriptor.descriptorType = type;
			writeDescriptor.descriptorCount = 1;
			writeDescriptor.pBufferInfo = &bufferInfo;
		}

		vkUpdateDescriptorSets(context.Device, 1, &writeDescriptor, 0, nullptr);
	}

	VkDeviceSize Buffer::GetAlignment(VkDeviceSize instanceSize, VkDeviceSize minOffsetAlignment)
	{
		if (minOffsetAlignment > 0)
		{
			return (instanceSize + minOffsetAlignment - 1) & ~(minOffsetAlignment - 1);
		}

		return instanceSize;
	}

	uint32_t Buffer::FindMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties)
	{
		VkPhysicalDeviceMemoryProperties memoryProperties{};
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

		for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
		{
			if ((typeFilter) & (1 << i) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
			{
				return i;
			}
		}

		ASSERT(false, "Failed to find a supported memory type.");
		return 0;
	}
}
 