#pragma once

#include "Vulkan/Texture/Texture.h"
#include "Vulkan/Texture/SwapChainTexture.h"

namespace Ash::Vulkan
{
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
		std::deque<Texture> DepthImages;
		std::vector<VkFramebuffer> Framebuffers;

	public:
		SwapChain();

		// Not copyable or moveable
		SwapChain(const SwapChain&) = delete;
		void operator=(const SwapChain&) = delete;
		SwapChain(SwapChain&&) = delete;
		SwapChain& operator=(SwapChain&&) = delete;

		void Recreate();

		operator VkSwapchainKHR() const { return Handle; }

	private:
		VkSwapchainKHR m_OldSwapChain = VK_NULL_HANDLE;

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