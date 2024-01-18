#include <iostream>

#include <SpinningCube.h>

using namespace SpinningCube;

/*
NEXT:
Images in swap chain, render system, event system, ...
*/

/*
TODO:
Sampler Anisotropy: move to config
line above m_Context... consistent?
*/

int main()
{
	SpinningCubeApplication spinningCube;
	spinningCube.Run();
}