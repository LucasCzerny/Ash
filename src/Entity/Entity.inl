#include "Core/Assert.h"

namespace Ash
{
	template <typename ComponentType, typename... Args>
	ComponentType& Entity::AddComponent(Args&&... args)
	{
		ASSERT(!HasComponent<ComponentType>(), "The entity already has that component.");

		return m_ParentScene->m_Registry.emplace<ComponentType>(m_EntityHandle, std::forward<Entity&>(*this), std::forward<Args>(args)...);
	}

	template <typename ComponentType>
	ComponentType& Entity::GetComponent()
	{
		ASSERT(HasComponent<ComponentType>(), "The entity doesn't have that component");

		return m_ParentScene->m_Registry.get<ComponentType>(m_EntityHandle);
	}

	template <typename ComponentType>
	const ComponentType& Entity::GetComponent() const
	{
		ASSERT(HasComponent<ComponentType>(), "The entity doesn't have that component");

		return m_ParentScene->m_Registry.get<ComponentType>(m_EntityHandle);
	}

	template <typename ComponentType>
	bool Entity::HasComponent() const
	{
		return m_ParentScene->m_Registry.all_of<ComponentType>(m_EntityHandle);
	}

	template <typename ComponentType>
	void Entity::RemoveComponent()
	{
		ASSERT(HasComponent<ComponentType>(), "The entity doesn't have that component");

		m_ParentScene->m_Registry.remove<ComponentType>(m_EntityHandle);
	}
}