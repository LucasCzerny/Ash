#include "pch.h"
#include "Entity.h"

#include "Components/Component.h"
#include "Components/TagComponent.h"

namespace Ash
{
	void Entity::Destroy()
	{
		m_ParentScene->m_Registry.destroy(m_EntityHandle);
	}

	void Entity::ForEveryComponent(std::function<void(Component&)> function)
	{
		for (auto&& curr : m_ParentScene->m_Registry.storage())
		{
			if (auto& storage = curr.second; storage.contains(m_EntityHandle))
			{
				Component& component = *(Component*)storage.value(m_EntityHandle);

				if (component.GetName() == "Tag Component")
				{
					continue;
				}

				function(component);
			}
		}
	}

	std::string Entity::GetTag() const
	{
		return GetComponent<TagComponent>().GetTag();
	}
}
