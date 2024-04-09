#include "pch.h"
#include "PipelineConfig.h"

#include "Vulkan/Context/Context.h"

#include "Vulkan/Utility/Shapes/Quad.h"

namespace Ash::Vulkan
{
	PipelineConfig& PipelineConfig::Default()
	{
		static PipelineConfig config;

		{
			config.ViewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;

			config.ViewportInfo.viewportCount = 1;
			config.ViewportInfo.pViewports = nullptr;

			config.ViewportInfo.scissorCount = 1;
			config.ViewportInfo.pScissors = nullptr;
		}

		{
			config.InputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;

			// Vertices: a, b, c, d, e, f
			// Triangle list: triangles (a, b), (b, c), (e, f)
			// Triangle strip: triangles (a, b), (b, c), (c, d), (d, e), (e, f)
			// Could alse be point/list/...
			config.InputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

			config.InputAssemblyInfo.primitiveRestartEnable = VK_FALSE;
		}

		{
			config.RasterizationInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;

			// If enabled: clamp(gl_Position.z, 0.0, 1.0)
			// Doesn't make sense for most applications because if the z value is < 0, it's behind the camera
			// > 1: Vertex is outside of the view frustum
			config.RasterizationInfo.depthClampEnable = VK_FALSE;

			// Discard all fragments immediately
			config.RasterizationInfo.rasterizerDiscardEnable = VK_FALSE;

			config.RasterizationInfo.polygonMode = VK_POLYGON_MODE_FILL;
			config.RasterizationInfo.lineWidth = 1.0f;
			config.RasterizationInfo.cullMode = VK_CULL_MODE_NONE;
			config.RasterizationInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;

			// The depth values of all fragments are generated by the rasterization of a polygon
			// Can be offset by a single value that is computed for that polygon
			config.RasterizationInfo.depthBiasEnable = VK_FALSE;
			config.RasterizationInfo.depthBiasConstantFactor = 0.0f;
			config.RasterizationInfo.depthBiasClamp = 0.0f;
			config.RasterizationInfo.depthBiasSlopeFactor = 0.0f;
		}

		{
			// Multisampling is used to prevent aliasing
			// No multisampling: if fragments's center is contained in triangle: fragment is "fully" in triangle
			// Results in jagged lines
			// Multisampling: Multiple samples (VK_SAMPLE_COUNT_4_BIT or 8_BIT etc.); determines how much of a pixel
			// contained in the triangle
			// MSAA ... Multisample Anti Aliasing
			config.MultisampleInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
			config.MultisampleInfo.sampleShadingEnable = VK_FALSE;
			config.MultisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
			config.MultisampleInfo.minSampleShading = 1.0f;
			config.MultisampleInfo.pSampleMask = nullptr;
			config.MultisampleInfo.alphaToCoverageEnable = VK_FALSE;
			config.MultisampleInfo.alphaToOneEnable = VK_FALSE;
		}

		{
			config.ColorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
			config.ColorBlendAttachment.blendEnable = VK_FALSE;

			config.ColorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
			config.ColorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
			config.ColorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;

			config.ColorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			config.ColorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			config.ColorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
		}

		{
			config.ColorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;

			// Logical op: &, |, ^, ...
			// Copy(a, b) = a
			// Is performed on all color values before writing them into the framebuffer
			// Only for signed-, unsigned- and normalized integer framebuffers
			// Not for floating point or SRGB framebuffers
			config.ColorBlendInfo.logicOpEnable = VK_FALSE;
			config.ColorBlendInfo.logicOp = VK_LOGIC_OP_COPY;

			config.ColorBlendInfo.attachmentCount = 1;
			config.ColorBlendInfo.pAttachments = &config.ColorBlendAttachment;
			config.ColorBlendInfo.blendConstants[0] = 0.0f;
			config.ColorBlendInfo.blendConstants[1] = 0.0f;
			config.ColorBlendInfo.blendConstants[2] = 0.0f;
			config.ColorBlendInfo.blendConstants[3] = 0.0f;
		}

		{
			config.DepthStencilInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
			config.DepthStencilInfo.depthTestEnable = VK_TRUE;
			config.DepthStencilInfo.depthWriteEnable = VK_TRUE;
			config.DepthStencilInfo.depthCompareOp = VK_COMPARE_OP_LESS;

			// Depth Bounds Test: discard fragments if their depth isn't in the specified range			
			config.DepthStencilInfo.depthBoundsTestEnable = VK_FALSE;
			config.DepthStencilInfo.minDepthBounds = 0.0f;
			config.DepthStencilInfo.maxDepthBounds = 1.0f;

			config.DepthStencilInfo.stencilTestEnable = VK_FALSE;
			config.DepthStencilInfo.front = {};
			config.DepthStencilInfo.back = {};
		}

		{
			config.DynamicStateEnables = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };

			config.DynamicStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
			config.DynamicStateInfo.dynamicStateCount = (uint32_t)config.DynamicStateEnables.size();
			config.DynamicStateInfo.pDynamicStates = config.DynamicStateEnables.data();
			config.DynamicStateInfo.flags = NULL;
		}

		{
			config.BindingDescriptions = Utility::QuadVertex::GetBindingDescriptions();
			config.AttributeDescriptions = Utility::QuadVertex::GetAttributeDescriptions();
		}

		return config;
	}
}