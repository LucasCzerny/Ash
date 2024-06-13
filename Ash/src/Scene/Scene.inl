namespace Ash
{
	template <typename ComponentType, typename... Other>
	std::vector<Entity> Scene::GetEntitiesWithComponents()
	{
		std::vector<Entity> entities;
		auto view = m_Registry.view<ComponentType, Other...>();

		for (entt::entity entity : view)
		{
			entities.push_back({ entity, this });
		}

		return entities;
	}
}