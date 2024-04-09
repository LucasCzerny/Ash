#pragma once

#include "Component.h"

namespace Ash
{
	class LightComponent : public Component
	{
	public:
		LightComponent(const Entity& entity, const glm::vec3& color, float intensity)
			: Component(entity) {}

		std::string GetName() const override { return "Light Component"; };
		ComponentInterface GetInterface() const override;

	private:
		glm::vec3 m_Color;
		float m_Intensity;
	};
}