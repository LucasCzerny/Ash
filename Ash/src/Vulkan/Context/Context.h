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

		Context(const Context&) = delete;
		Context(Context&&) = delete;
		void operator=(const Context&) = delete;
		Context& operator=(Context&&) = delete;

		static void Create();
		static std::shared_ptr<Context> Get();
		
		void Resize(uint32_t width, uint32_t height);

		template <typename T>
		T GetExtensionFunction(const std::string& name);

	private:
		VkDebugUtilsMessengerEXT m_DebugMessenger;

		static std::shared_ptr<Context> s_Instance;

	private:
		void CreateCommandPool();
		void CreateCommandBuffers();

		void CreateDescriptorPool();

		void CreateEventCallbacks();
	};
}

#include "Context.inl"