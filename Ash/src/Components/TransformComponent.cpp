#include "pch.h"
#include "TransformComponent.h"

namespace Ash
{
	ComponentInterface TransformComponent::GetInterface() const
	{
		return ComponentInterface{ {
			{ "Transform", DataType::FLOAT3, (void*)glm::value_ptr(Position) },
			{ "Rotation",  DataType::FLOAT3, (void*)glm::value_ptr(Rotation) },
			{ "Scale",	   DataType::FLOAT3, (void*)glm::value_ptr(Scale)    },
		} };
	}

	void TransformComponent::CalculateMatrices()
	{
		m_ModelMatrix = glm::translate(glm::mat4(1.0f), Position);
		m_ModelMatrix *= glm::toMat4(glm::quat(Rotation));
		m_ModelMatrix *= glm::scale(glm::mat4(1.0f), Scale);

		m_NormalMatrix = glm::inverse(m_ModelMatrix);
		m_NormalMatrix = glm::transpose(m_NormalMatrix);
	}

	glm::vec3 TransformComponent::GetForwardDirection()
	{
		return glm::rotate(glm::quat(Rotation), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::vec3 TransformComponent::GetRightDirection()
	{
		return glm::rotate(glm::quat(Rotation), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 TransformComponent::GetUpDirection()
	{
		return glm::rotate(glm::quat(Rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	}
}
