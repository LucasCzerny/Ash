#pragma once

namespace Ash
{
	class Entity;

	class Scene
	{
		friend class Entity;

	public:
		~Scene();

		Entity CreateEntity(const std::string& tag, const glm::vec3& position = { 0.0f, 0.0f, 0.0f }, const glm::vec3& rotation = { 0.0f, 0.0f, 0.0f }, const glm::vec3& scale = { 1.0f, 1.0f, 1.0f });

		void OnUpdate(float deltaTime);

		std::vector<Entity> GetAllEntities();

		template <typename ComponentType, typename... Other>
		std::vector<Entity> GetEntitiesWithComponents();

		std::vector<Entity> GetRenderableEntities();
		std::vector<Entity> GetCameraEntities();
		std::vector<Entity> GetLightEntities();

	private:
		entt::registry m_Registry;
	};
}

#include "Scene.inl"
