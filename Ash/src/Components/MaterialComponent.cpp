#include "pch.h"
#include "MaterialComponent.h"

namespace Ash
{
	ComponentInterface MaterialComponent::GetInterface() const
	{
		return ComponentInterface{ {
			{ "Albedo",       DataType::FLOAT3, (void*)&m_Material.Albedo      },
			{ "Normal Scale", DataType::FLOAT,  (void*)&m_Material.NormalScale },
			{ "Metallic",     DataType::FLOAT,  (void*)&m_Material.Metallic    },
			{ "Roughness",    DataType::FLOAT,  (void*)&m_Material.Roughness   },
			{ "Emissive",     DataType::FLOAT3, (void*)&m_Material.Emissive    }
		} };
	}
}
