#include "pch.h"
#include "LightComponent.h"

namespace Ash
{
	ComponentInterface LightComponent::GetInterface() const
	{
		return ComponentInterface{ {
			{ "Color",     DataType::FLOAT3, (void*)glm::value_ptr(m_Color) },
			{ "Intensity", DataType::FLOAT,  (void*)&m_Intensity            }
		} };
	}
}
