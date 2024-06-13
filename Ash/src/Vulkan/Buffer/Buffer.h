#pragma once

#include "Vulkan/Context/Context.h"

namespace Ash::Vulkan
{
	enum class BufferType
	{
		VERTEX, INDEX,
		UBO, SSBO
	};

	class Buffer
	{
	public:
		VkBuffer Handle = VK_NULL_HANDLE;
		VkDeviceMemory Memory = VK_NULL_HANDLE;
		uint32_t Size = 0;
		void* MappedMemory = nullptr;

	public:
		Buffer() = default;
		Buffer(VkBuffer handle, VkDeviceMemory memory, uint32_t size, void* mappedMemory = nullptr);

		Buffer(VkDeviceSize instanceSize, uint32_t instanceCount, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment = 1);
		Buffer(VkDeviceSize instanceSize, uint32_t instanceCount, void* data, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment = 1);
		
		template <typename Type> 
		Buffer(const std::vector<Type>& vector, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment = 1)
			: Buffer(sizeof(Type), vector.size(), (void*)vector.data(), usageFlags, memoryPropertyFlags, minOffsetAlignment) {}

		template <typename Type, unsigned int Size>
		Buffer(const std::array<Type, Size>& array, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment = 1)
			: Buffer(sizeof(Type), array.size(), (void*)array.data(), usageFlags, memoryPropertyFlags, minOffsetAlignment) {}

		template <typename Type>
		Buffer(const std::vector<Type>& vector, BufferType type)
			: Buffer(vector, GetUsageFromType(type), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {}

		template <typename Type, unsigned int Size>
		Buffer(const std::array<Type, Size>& vector, BufferType type)
			: Buffer(array, GetUsageFromType(type), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {}

		~Buffer();

		Buffer(const Buffer& buffer);
		Buffer(Buffer&& buffer) noexcept;
		Buffer& operator=(const Buffer& buffer);
		Buffer& operator=(Buffer&& buffer) noexcept;

		void Reset();
		bool IsEmpty() const { return Handle == VK_NULL_HANDLE; }

		void CopyData(void* data);

		void Map(uint32_t offset = 0);
		void Unmap();

		VkDescriptorBufferInfo GetDescriptorBufferInfo() const;

		VkBuffer* Pointer() { return &Handle; }
		const VkBuffer* Pointer() const { return (const VkBuffer*)&Handle; }

		operator VkBuffer() const { return Handle; }

		operator bool() const { return !IsEmpty(); }

	private:
		std::shared_ptr<Context> m_Context = nullptr;
		
	private:
		VkDeviceSize GetAlignment(VkDeviceSize instanceSize, VkDeviceSize minOffsetAlignment);
		uint32_t FindMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

		VkBufferUsageFlagBits GetUsageFromType(const BufferType& type);
	};
}
