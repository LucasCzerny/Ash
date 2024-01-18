#include "SpinningCube.h"

#include "RenderSystem/RenderingLayer.h"

namespace SpinningCube
{
	SpinningCubeApplication::SpinningCubeApplication()
		: Ash::Application({
			"SpinningCube",
			1280, 720,
			false,
			true
		})
	{
		RenderingLayer renderingLayer;
		AddLayer(renderingLayer);
	}

	void SpinningCube::OnResize(uint32_t width, uint32_t height)
	{
	}
}