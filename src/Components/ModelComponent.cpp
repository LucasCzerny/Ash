#include "pch.h"
#include "ModelComponent.h"

namespace Ash
{
	ComponentInterface ModelComponent::GetInterface() const
	{
		return ComponentInterface{ {
			{ "File Path", DataType::FILE, nullptr }
		} };
	}
}
