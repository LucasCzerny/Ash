#pragma once

#include "Component.h"

namespace Ash
{
	class MaterialComponent : public Component
	{
	public:
		MaterialComponent(const Entity& entity, const Material& material)
			: Component(entity), m_Material(material) {}

		std::string GetName() const override { return "Material Component"; }
		ComponentInterface GetInterface() const override;

	private:
		Material m_Material;
	};
}
