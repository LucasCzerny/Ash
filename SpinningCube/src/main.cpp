#include <iostream>

#include "SpinningCube/RenderingLayer.h"

using namespace SpinningCube;

/*
NEXT:
Images in swap chain, render system, event system, ...
*/

/*
TODO:
Sampler Anisotropy: move to config
line above m_Context->.. consistent?
*/

// static const Config config {
// 	"Spinning Cube Application",
// 	1,
// 	0,
// 	0,
// 	1280,
// 	720,
// 	false,
// 	true
// };

int main()
{
	Application& app = Application::Get();
	app.AddLayer(std::make_unique<RenderingLayer>());

	app.Run();
}