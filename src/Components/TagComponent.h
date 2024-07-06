#pragma once

#include "Component.h"

namespace Ash
{
	class TagComponent : public Component
	{
	private:
		std::string m_Tag;

	public:
		TagComponent(const Entity& entity, const std::string& tag)
			: Component(entity), m_Tag(tag) {}

		std::string GetName() const override { return "Tag Component"; };
		ComponentInterface GetInterface() const override;

		void SetTag(const std::string& tag) { m_Tag = tag; }
		std::string GetTag() const { return m_Tag; }
	};
}
