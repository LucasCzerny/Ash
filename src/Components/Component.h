#pragma once

#include "ComponentInterface.h"

#include "Entity/Entity.h"

#include "Vulkan/Context/Context.h"

namespace Ash
{
	class Component
	{
	public:
		Component(const Entity& entity);

		virtual void OnUpdate(float deltaTime) {}

		virtual std::string GetName() const { return "Unnamed Component"; }
		virtual ComponentInterface GetInterface() const { return ComponentInterface(); }

	protected:
		Entity m_Entity;

	protected:
		template <typename ComponentType>
		ComponentType& GetComponent() { return m_Entity.GetComponent<ComponentType>(); }

		template <typename ComponentType>
		bool HasComponent() { return m_Entity.HasComponent<ComponentType>(); }
	};
}
