#include "pch.h"
#include "Buffer.h"

#include "Core/Assert.h"

#include "Vulkan/Context/Context.h"
#include "Vulkan/Defaults/Defaults.h"

namespace Ash::Vulkan
{
	Buffer::Buffer(VkBuffer handle, VkDeviceMemory memory, uint32_t size, void* mappedMemory)
		: m_Context(Context::Get()), Handle(handle), Memory(memory), Size(size), MappedMemory(mappedMemory)
	{
		Map();
	}

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

		VkResult result = vkCreateBuffer(m_Context->Device, &bufferInfo, nullptr, &Handle);
		ASSERT(result == VK_SUCCESS, "Failed to create the buffer.");

		VkMemoryRequirements memoryRequirements;
		vkGetBufferMemoryRequirements(m_Context->Device, Handle, &memoryRequirements);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;

		allocInfo.allocationSize = memoryRequirements.size;
		allocInfo.memoryTypeIndex = FindMemoryType(m_Context->Device, memoryRequirements.memoryTypeBits, memoryPropertyFlags);

		result = vkAllocateMemory(m_Context->Device, &allocInfo, nullptr, &Memory);
		ASSERT(result == VK_SUCCESS, "Failed to allocate memory for the buffer.");

		vkBindBufferMemory(m_Context->Device, Handle, Memory, 0);
	}

	Buffer::Buffer(VkDeviceSize instanceSize, uint32_t instanceCount, void* data, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment)
		: Buffer(instanceSize, instanceCount, usageFlags, memoryPropertyFlags, minOffsetAlignment)
	{
		CopyData(data);
	}

	Buffer::~Buffer()
	{
		vkDestroyBuffer(m_Context->Device, Handle, nullptr);
	}

	Buffer::Buffer(const Buffer& buffer)
		: Buffer(buffer.Handle, buffer.Memory, buffer.Size, buffer.MappedMemory)
	{
		Log::Info("Buffer was just copied at line ", __LINE__, " in file ", __FILE__);
	}

	Buffer::Buffer(Buffer&& buffer) noexcept
		: Buffer(buffer.Handle, buffer.Memory, buffer.Size, buffer.MappedMemory)
	{
		buffer.Reset();
	}

	Buffer& Buffer::operator=(const Buffer& buffer)
	{
		*this = Buffer(buffer.Handle, buffer.Memory, buffer.Size, buffer.MappedMemory);
		Log::Info("Buffer was just copied at line ", __LINE__, " in file ", __FILE__);

		return *this;
	}

	Buffer& Buffer::operator=(Buffer&& buffer) noexcept
	{
		Handle = buffer.Handle;
		Memory = buffer.Memory;
		Size = buffer.Size;
		MappedMemory = buffer.MappedMemory;

		buffer.Reset();

		return *this;
	}

	void Buffer::Reset()
	{
		Handle = VK_NULL_HANDLE;
		Memory = VK_NULL_HANDLE;
		Size = 0;
		MappedMemory = nullptr;
	}

	void Buffer::CopyData(void* data)
	{
		Map();
		memcpy(MappedMemory, data, Size);
		Unmap();
	}

	void Buffer::Map(uint32_t offset)
	{
		VkResult result = vkMapMemory(m_Context->Device, Memory, offset, Size, NULL, &MappedMemory);
		ASSERT(result == VK_SUCCESS, "Failed to map the buffer memory.");
	}

	void Buffer::Unmap()
	{
		vkUnmapMemory(m_Context->Device, Memory);
	}

	VkDescriptorBufferInfo Buffer::GetDescriptorBufferInfo() const
	{
		VkDescriptorBufferInfo bufferInfo = Vulkan::Defaults<VkDescriptorBufferInfo>();
		{
			bufferInfo.buffer = Handle;
			bufferInfo.range = Size;
		}

		return bufferInfo;
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

	VkBufferUsageFlagBits Buffer::GetUsageFromType(const BufferType& type)
	{
		VkBufferUsageFlagBits usage;

		switch (type)
		{
			case BufferType::VERTEX:
			{
				usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
				break;
			}

			case BufferType::INDEX:
			{
				usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
				break;
			}

			case BufferType::UBO:
			{
				usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
				break;
			}

			case BufferType::SSBO:
			{
				usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
				break;
			}

			default:
			{
				ASSERT(false, "Invalid buffer type (how did you even manage to do that).");
			}
		}

		return usage;
	}
}
 