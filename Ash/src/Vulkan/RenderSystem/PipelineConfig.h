#pragma once

namespace Ash::Vulkan
{
	struct PipelineConfig
	{
	public:
		VkPipelineViewportStateCreateInfo ViewportInfo{};
		VkPipelineInputAssemblyStateCreateInfo InputAssemblyInfo{};
		VkPipelineRasterizationStateCreateInfo RasterizationInfo{};
		VkPipelineMultisampleStateCreateInfo MultisampleInfo{};
		VkPipelineColorBlendAttachmentState ColorBlendAttachment{};
		VkPipelineColorBlendStateCreateInfo ColorBlendInfo{};
		VkPipelineDepthStencilStateCreateInfo DepthStencilInfo{};
		std::vector<VkDynamicState> DynamicStateEnables{};
		VkPipelineDynamicStateCreateInfo DynamicStateInfo{};
		uint32_t Subpass = 0;
		std::vector<VkVertexInputBindingDescription> BindingDescriptions{};
		std::vector<VkVertexInputAttributeDescription> AttributeDescriptions{};

		// These don't have a default value
		VkPipelineLayoutCreateInfo PipelineLayoutInfo{};
		VkRenderPassCreateInfo RenderPassInfo{};
		fs::path VertexShaderPath{}, FragmentShaderPath{};

	public:
		PipelineConfig() = default;

		static PipelineConfig& Default();
	};

	struct ComputePipelineConfig
	{
	public:
		// Unlike the graphics pipeline config, there aren't any default values
		VkPipelineLayout PipelineLayout = nullptr;
		fs::path ComputeShaderPath{};

	public:
		ComputePipelineConfig() = default;
	};
}