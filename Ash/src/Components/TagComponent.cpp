#include "pch.h"
#include "TagComponent.h"

namespace Ash
{
	ComponentInterface TagComponent::GetInterface() const
	{
		return ComponentInterface{ {
			{ "Tag", DataType::STRING, (void*)&m_Tag}
		} };
	}
}