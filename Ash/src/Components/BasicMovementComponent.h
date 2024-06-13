#pragma once

#include "Component.h"
#include "TransformComponent.h"

namespace Ash
{
	class BasicMovementComponent : public Component
	{
	private:
		TransformComponent& m_Transform;

		float m_MovementSpeed = 1.0f;
		float m_MovementSpeedMultiplier = 3.0f;
		float m_RotationSpeed = 0.6f;

	public:
		BasicMovementComponent(const Entity& entity)
  			: Component(entity), m_Transform(GetComponent<TransformComponent>()) {}

		std::string GetName() const override { return "Basic Movement Component"; };
		ComponentInterface GetInterface() const override;
		
		void OnUpdate(float deltaTime) override;
	};
}