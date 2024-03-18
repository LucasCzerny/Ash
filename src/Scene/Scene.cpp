#include "pch.h"
#include "Scene.h"

#include "Entity/Entity.h"

#include "Components/CameraComponent.h"
#include "Components/TagComponent.h"
#include "Components/TransformComponent.h"

namespace Ash
{
	Scene::~Scene()
	{
		for (Entity& entity : GetAllEntities())
		{
			entity.Destroy();
		}
	}

	Entity Scene::CreateEntity(const std::string& tag, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	{
		Entity entity(m_Registry.create(), this);
		entity.AddComponent<TagComponent>(tag);
		entity.AddComponent<TransformComponent>(position, rotation, scale);

		return entity;
	}

	void Scene::OnUpdate(float deltaTime)
	{
		for (Entity& entity : GetAllEntities())
		{
			entity.ForEveryComponent([&deltaTime](Component& component) {
				component.OnUpdate(deltaTime);
			});
		}
	}

	std::vector<Entity> Scene::GetAllEntities()
	{
		return GetEntitiesWithComponents<TagComponent>();
	}

	// TODO: add lights and maybe use transform component in getcameraentiteis
	std::vector<Entity> Scene::GetRenderableEntities()
	{
		return GetAllEntities();
		// return GetEntitiesWithComponents<ModelComponent>();
	}

	std::vector<Entity> Scene::GetCameraEntities()
	{
		return GetEntitiesWithComponents<CameraComponent>();
	}

	std::vector<Entity> Scene::GetDirectionalLightEntities()
	{
		return GetAllEntities();
		// return GetEntitiesWithComponents<DirectionalLightComponent>();
	}

	std::vector<Entity> Scene::GetPointLightEntities()
	{
		return GetAllEntities();
		// return GetEntitiesWithComponents<PointLightComponent>();
	}
}