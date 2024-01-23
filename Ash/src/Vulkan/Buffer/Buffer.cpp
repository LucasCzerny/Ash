#include "pch.h"
#include "Buffer.h"

#include "Core/Assert.h"

#include "Vulkan/Context/Context.h"

namespace Ash::Vulkan
{
	Buffer::Buffer()
		: m_Context(Context::Get()) {}

	Buffer::Buffer(VkBuffer handle, VkDeviceMemory memory, uint32_t size, void* mappedMemory)
		: m_Context(Context::Get()), Handle(handle), Memory(memory), Size(size), MappedMemory(mappedMemory) {}

	Buffer::Buffer(VkDeviceSize instanceSize, uint32_t instanceCount, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment)
		: m_Context(Context::Get())
	{
		VkDeviceSize alignmentSize = GetAlignment(instanceSize, minOffsetAlignment);
		Size = (uint32_t)alignmentSize * instanceCount;

		VkBufferCreateInfo bufferInfo{};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = Size;
		bufferInfo.usage = usageFlags;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		VkResult result = vkCreateBuffer(m_Context.Device, &bufferInfo, nullptr, &Handle);
		ASSERT(result == VK_SUCCESS, "Failed to create the buffer.");

		VkMemoryRequirements memoryRequirements;
		vkGetBufferMemoryRequirements(m_Context.Device, Handle, &memoryRequirements);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;

		allocInfo.allocationSize = memoryRequirements.size;
		allocInfo.memoryTypeIndex = FindMemoryType(m_Context.Device, memoryRequirements.memoryTypeBits, memoryPropertyFlags);

		result = vkAllocateMemory(m_Context.Device, &allocInfo, nullptr, &Memory);
		ASSERT(result == VK_SUCCESS, "Failed to allocate memory for the buffer.");

		vkBindBufferMemory(m_Context.Device, Handle, Memory, 0);
	}

	Buffer::Buffer(VkDeviceSize instanceSize, uint32_t instanceCount, void* data, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment)
		: Buffer(instanceSize, instanceCount, usageFlags, memoryPropertyFlags, minOffsetAlignment)
	{
		CopyData(data);
	}

	Buffer::~Buffer()
	{
		vkDestroyBuffer(m_Context.Device, Handle, nullptr);
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
		VkResult result = vkMapMemory(m_Context.Device, Memory, offset, Size, NULL, &MappedMemory);
		ASSERT(result == VK_SUCCESS, "Failed to map the buffer memory.");
	}

	void Buffer::Unmap()
	{
		vkUnmapMemory(m_Context.Device, Memory);
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
 