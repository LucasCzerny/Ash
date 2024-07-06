#include "Core/Assert.h"

namespace Ash::Vulkan
{
	template<typename T>
	T Context::GetExtensionFunction(const std::string& name)
	{
		T func = (T)vkGetInstanceProcAddr(Instance, name.c_str());
		ASSERT(func != nullptr, "Couldn't get the adress of the \"", name, "\" function.");
		
		return func;
	}
}