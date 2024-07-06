#pragma once

#include "Component.h"

#include "Model/Model.h"

namespace Ash
{
	class ModelComponent : public Component
	{
	public:
		ModelComponent(const Entity& entity, const Model& model)
			: Component(entity), m_Model(model) {}

		std::string GetName() const override { return "Model Component"; }
		ComponentInterface GetInterface() const override;

	private:
		Model m_Model;
	};
}
