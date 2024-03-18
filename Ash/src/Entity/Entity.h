#pragma once

#include "Scene/Scene.h"

namespace Ash
{
	class Component;

	class Entity
	{
	public:
		Entity(entt::entity entityHandle, Scene* parentScene)
			: m_EntityHandle(entityHandle), m_ParentScene(parentScene) {}

		Entity() = default;

		void Destroy();

		void ForEveryComponent(std::function<void(Component&)> function);

		std::string GetTag() const;

		template <typename ComponentType, typename... Args>
		ComponentType& AddComponent(Args&&... args);

		template <typename ComponentType>
		ComponentType& GetComponent();

		template <typename ComponentType>
		const ComponentType& GetComponent() const;

		template <typename ComponentType>
		bool HasComponent() const;

		template <typename ComponentType>
		void RemoveComponent();

		operator entt::entity() const { return m_EntityHandle; }
		operator bool() const { return m_EntityHandle != entt::null; }

	private:
		entt::entity m_EntityHandle = entt::null;
		Scene* m_ParentScene = nullptr;
	};
}

#include "Entity.inl"
