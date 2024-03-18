#pragma once

#include "Config/Config.h"

#include "Vulkan/Device/Device.h"
#include "Vulkan/Instance/Instance.h"
#include "Vulkan/SwapChain/SwapChain.h"
#include "Vulkan/Window/Window.h"

namespace Ash::Vulkan
{
	class Context
	{
	public:
		Vulkan::Instance Instance;
		Vulkan::Window Window;

		Vulkan::Device Device;

		Vulkan::SwapChain SwapChain;

		VkCommandPool CommandPool;
		std::vector<VkCommandBuffer> CommandBuffers;

		VkDescriptorPool DescriptorPool;

	public:
		Context();
		~Context();

		static Context& Get() { return s_Instance; }

		void Resize(uint32_t width, uint32_t height);

		VkCommandBuffer GetNextCommandBuffer();

		template <typename T>
		T GetExtensionFunction(const std::string& name);

	private:
		VkDebugUtilsMessengerEXT m_DebugMessenger;

		static Context s_Instance;

	private:
		void CreateCommandPool();
		void CreateCommandBuffers();

		void CreateDescriptorPool();

		void CreateEventCallbacks();
	};
}

#include "Context.inl"