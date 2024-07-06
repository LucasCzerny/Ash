#include "pch.h"
#include "Component.h"

#include "Entity/Entity.h"

#include "Vulkan/Context/Context.h"

namespace Ash
{
	Component::Component(const Entity& entity)
		: m_Entity(entity) {}
}