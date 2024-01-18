#pragma once

#include "ComponentInterface.h"

#include "Vulkan/Context/Context.h"

namespace Ash
{
	class Entity;

	class Component
	{
	public:
		Component(const Entity& entity)
			: m_Entity(entity) {}

		virtual void OnUpdate(float deltaTime) {}

		virtual std::string GetName() const { return "Unnamed Component"; }
		virtual ComponentInterface GetInterface() const { return {}; }

	protected:
		Entity m_Entity;

		Vulkan::Context& m_Context = Vulkan::Context::Get();

	protected:
		template <typename ComponentType>
		ComponentType& GetComponent() { return m_Entity.GetComponent<ComponentType>(); }

		template <typename ComponentType>
		bool HasComponent() { return m_Entity.HasComponent<ComponentType>(); }
	};
}
