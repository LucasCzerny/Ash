#pragma once

namespace Ash::Vulkan
{
	class Context;

	class Instance
	{
	public:
		VkInstance Handle;

		VkDebugUtilsMessengerEXT DebugMessenger;

	public:
		Instance();

		// Not copyable or moveable
		Instance(const Instance&) = delete;
		void operator=(const Instance&) = delete;
		Instance(Instance&&) = delete;
		Instance& operator=(Instance&&) = delete;

		operator VkInstance() const { return Handle; }

	private:
		Context& m_Context = Context::Get();

	private:
		bool CheckValidationLayerSupport();
	};
}