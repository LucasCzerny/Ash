#pragma once

namespace Ash
{
	enum class DataType
	{
		FLOAT, FLOAT2, FLOAT3, FLOAT4,
		STRING,
		FILE
	};

	struct ComponentProperty
	{
		std::string Name;
		DataType Type;
		void* Data;
	};

	using ComponentInterface = std::vector<ComponentProperty>;
}
