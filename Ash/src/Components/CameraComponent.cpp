#include "pch.h"
#include "CameraComponent.h"

#include "TransformComponent.h"

namespace Ash
{
	ComponentInterface CameraComponent::GetInterface() const
	{
		return ComponentInterface{ {
			{ "FOV",		DataType::FLOAT, (void*)&m_FovDegrees },
			{ "Near Plane",	DataType::FLOAT, (void*)&m_Near       },
			{ "Far Plane",  DataType::FLOAT, (void*)&m_Far        }
		} };
	}

	bool CameraComponent::HasMoved()
	{
		static TransformComponent& transform = GetComponent<TransformComponent>();
		static glm::vec3 oldPosition = glm::vec3(0.0f);
		static glm::vec3 oldRotation = glm::vec3(0.0f);

		glm::vec3 position = transform.Position;
		glm::vec3 rotation = transform.Rotation;

		bool hasMoved = position != oldPosition || rotation != oldRotation;

		oldPosition = position;
		oldRotation = rotation;

		return hasMoved;
	}

	glm::mat4 CameraComponent::CalculateProjectionMatrix()
	{
		static std::shared_ptr<Vulkan::Context> context = Vulkan::Context::Get();

		glm::vec2 screenSize = context->Window.GetSize();

		if (screenSize.x == 0)
		{
			return glm::mat4(1.0f);
		}

		float aspectRatio = screenSize.x / screenSize.y;
		return glm::perspective(glm::radians(m_FovDegrees), aspectRatio, m_Near, m_Far);
	}

	glm::mat4 CameraComponent::CalculateViewMatrix()
	{
		TransformComponent& transform = GetComponent<TransformComponent>();

		glm::mat4 transformationMatrix = glm::translate(glm::mat4(1.0f), transform.Position);
		transformationMatrix *= glm::toMat4(glm::quat(transform.Rotation));

		return glm::inverse(transformationMatrix);
	}
}
