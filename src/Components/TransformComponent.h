#pragma once

#include "Component.h"

namespace Ash
{
	class TransformComponent : public Component
	{
	public:
		glm::vec3 Position{ 0.0f };
		glm::vec3 Rotation{ 0.0f };
		glm::vec3 Scale{ 1.0f };

	private:
		glm::mat4 m_ModelMatrix{ 1.0f };
		glm::mat4 m_NormalMatrix{ 1.0f };

	public:
		TransformComponent(const Entity& entity, const glm::vec3& position = { 0.0f, 0.0f, 0.0f }, const glm::vec3& rotation = { 0.0f, 0.0f, 0.0f }, const glm::vec3& scale = { 1.0f, 1.0f, 1.0f })
			: Component(entity), Position(position), Rotation(rotation), Scale(scale) {}

		std::string GetName() const override { return "Transform Component"; };
		ComponentInterface GetInterface() const override;

		void CalculateMatrices();

		glm::mat4 GetModelMatrix() const { return m_ModelMatrix; }
		glm::mat4 GetNormalMatrix() const { return m_NormalMatrix; }

		glm::vec3 GetForwardDirection();
		glm::vec3 GetRightDirection();
		glm::vec3 GetUpDirection();
	};
}
