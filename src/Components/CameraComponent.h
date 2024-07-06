#pragma once

#include "Component.h"

namespace Ash
{
	class CameraComponent : public Component
	{
	private:
		float m_FovDegrees;
		float m_Near;
		float m_Far;

	public:
		CameraComponent(const Entity& entity, float fovDegrees = 45.0f, float near = 0.1f, float far = 1000.0f)
			: Component(entity), m_FovDegrees(fovDegrees), m_Near(near), m_Far(far) {}

		std::string GetName() const override { return "Camera Component"; };
		ComponentInterface GetInterface() const override;

		bool HasMoved();

		glm::mat4 CalculateProjectionMatrix();
		glm::mat4 CalculateViewMatrix();
	};
}
