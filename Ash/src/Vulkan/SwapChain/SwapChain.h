#pragma once

#include "Vulkan/Device/Device.h"
#include "Vulkan/Texture/SwapChainTextures.h"
#include "Vulkan/Window/Window.h"

namespace Ash::Vulkan
{
	class Texture;

	class SwapChain
	{
	public:
		VkSwapchainKHR Handle = VK_NULL_HANDLE;
		
		VkExtent2D Extent2D;
		VkExtent3D Extent3D;
		VkPresentModeKHR PresentMode;
		VkSurfaceFormatKHR SurfaceFormat;
		uint32_t ImageCount;
		VkFormat DepthFormat;

		std::deque<SwapChainTexture> Images;
		std::deque<SwapChainDepthTexture> DepthImages;
		std::vector<VkFramebuffer> Framebuffers;

	public:
		SwapChain(Device& device, Window& window);

		SwapChain(const SwapChain&) = delete;
		SwapChain(SwapChain&&) = delete;
		void operator=(const SwapChain&) = delete;
		SwapChain& operator=(SwapChain&&) = delete;

		void Recreate();

		VkSwapchainKHR* Pointer() { return &Handle; }
		const VkSwapchainKHR* Pointer() const { return (const VkSwapchainKHR*)&Handle; }

		operator VkSwapchainKHR() const { return Handle; }

	private:
		VkSwapchainKHR m_OldSwapChain = VK_NULL_HANDLE;

		Device& m_Device;
		Window& m_Window;

	private:
		void ChooseSwapChainSpecification();
		VkExtent2D ChooseExtent(const VkSurfaceCapabilitiesKHR& surfaceCapabilities, VkExtent2D default);
		VkPresentModeKHR ChoosePresentMode(const std::vector<VkPresentModeKHR>& availableModes);
		VkSurfaceFormatKHR ChooseSwapChainSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

		void CreateSwapChain();

		void CreateSwapChainImages();
		void CreateDepthResources();
	};
}