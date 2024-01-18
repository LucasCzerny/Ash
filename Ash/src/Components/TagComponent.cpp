#include "pch.h"
#include "TagComponent.h"

namespace Ash
{
	ComponentInterface TagComponent::GetInterface() const
	 {
		return ComponentInterface{ {
			{ "Tag", DataType::STRING, &m_Tag }
		} };
	}
}