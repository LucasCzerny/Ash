#pragma once

namespace Ash::Vulkan
{
	class Instance
	{
	public:
		VkInstance Handle;
		VkDebugUtilsMessengerEXT DebugMessenger;

	public:
		Instance();

		Instance(const Instance&) = delete;
		Instance(Instance&&) = delete;
		void operator=(const Instance&) = delete;
		Instance& operator=(Instance&&) = delete;

		operator VkInstance() const { return Handle; }

	private:
		bool CheckValidationLayerSupport();
	};
}