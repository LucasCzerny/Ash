#include "pch.h"
#include "Layer.h"

namespace Ash
{
	Layer::Layer()
	{
		static uint8_t layerCount = 0;
		m_Id = layerCount++;
	}

	bool Layer::operator==(Layer& other) const
	{
		return m_Id == other.m_Id;
	}
}
