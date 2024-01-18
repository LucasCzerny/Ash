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
		// TODO: emplace_back?
		RenderingLayer renderingLayer;
		AddLayer(renderingLayer);
	}
}