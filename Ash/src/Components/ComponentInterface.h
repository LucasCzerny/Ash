#pragma once

namespace Ash
{
	enum class DataType
	{
		FLOAT, FLOAT2, FLOAT3, FLOAT4,
		STRING
	};

	struct ComponentProperty
	{
		const char* Name;
		DataType DataType;
		void* Data;
	};

	using ComponentInterface = std::vector<ComponentProperty>;
}
