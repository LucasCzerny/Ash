#include "pch.h"
#include "BasicMovementComponent.h"

#include "Input/Input.h"

namespace Ash
{
	ComponentInterface BasicMovementComponent::GetInterface() const
	{
		return ComponentInterface{ {
			{ "Movement Speed",            DataType::FLOAT, (void*)&m_MovementSpeed           },
			{ "Movement Speed Multiplier", DataType::FLOAT, (void*)&m_MovementSpeedMultiplier },
			{ "Rotation Speed",            DataType::FLOAT, (void*)&m_RotationSpeed           }
		} };
	}

	void BasicMovementComponent::OnUpdate(float deltaTime)
	{
		glm::vec3 forward = m_Transform.GetForwardDirection();
		glm::vec3 right = m_Transform.GetRightDirection();
		glm::vec3 up = m_Transform.GetUpDirection();

		glm::vec3 movementVector(0.0f);

		if (Input::GetKey(Key::W) == KeyState::Down)
		{
			movementVector += forward * m_MovementSpeed * deltaTime;
		}

		if (Input::GetKey(Key::S) == KeyState::Down)
		{
			movementVector -= forward * m_MovementSpeed * deltaTime;
		}

		if (Input::GetKey(Key::D) == KeyState::Down)
		{
			movementVector += right * m_MovementSpeed * deltaTime;
		}

		if (Input::GetKey(Key::A) == KeyState::Down)
		{
			movementVector -= right * m_MovementSpeed * deltaTime;
		}

		if (Input::GetKey(Key::Space) == KeyState::Down)
		{
			movementVector.y += m_MovementSpeed * deltaTime;
		}

		if (Input::GetKey(Key::LeftControl) == KeyState::Down)
		{
			movementVector.y -= m_MovementSpeed * deltaTime;
		}

		if (Input::GetKey(Key::LeftShift) == KeyState::Down)
		{
			movementVector *= m_MovementSpeedMultiplier;
		}

		m_Transform.Position += movementVector;

		static glm::vec2 oldMousePosition(0.0f);

		glm::vec2 mousePosition = Input::GetMousePosition();
		glm::vec2 mouseDelta = mousePosition - oldMousePosition;

		if (Input::GetMouseButton(Key::MouseButton1) == KeyState::Down)
		{
			Input::SetCursorMode(CursorMode::Disabled);

			m_Transform.Rotation.x += -mouseDelta.y * m_RotationSpeed * deltaTime;
			m_Transform.Rotation.y += -mouseDelta.x * m_RotationSpeed * deltaTime;
		}
		else
		{
			Input::SetCursorMode(CursorMode::Normal);
		}

		oldMousePosition = mousePosition;
	}
}