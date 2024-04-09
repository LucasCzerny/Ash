#pragma once

#include "Vulkan/Texture/Texture.h"

namespace Ash
{
	class Material
	{
	public:
		alignas(16) glm::vec3 Albedo(1.0f);

		float NormalScale = 1.0f;

		float Metallic = 1.0;
		float Roughness = 1.0;

		alignas(16) glm::vec3 Emissive(1.0f);

		Vulkan::Texture AlbedoTexture, NormalTexture, EmissiveTexture, MetalnessTexture, RoughnessTexture;

	public:
		Material() = default;

		Material(const glm::vec3& albedo, float normalScale, float metallic, float roughness, const glm::vec3& emissive)
			: Albedo(albedo), NormalScale(normalScale), Metallic(metallic), Roughness(roughness), Emissive(emissive) {}

		Material(const Vulkan::Texture& albedo, const Vulkan::Texture& normal, const Vulkan::Texture& emissive, const Vulkan::Texture& metalness, const Vulkan::Texture& roughness)
			: AlbedoTexture(albedo), NormalTexture(normal), EmissiveTexture(emissive), MetalnessTexture(metalness), RoughnessTexture(roughness) {}

		Material(const Vulkan::Texture& albedoTexture, const Vulkan::Texture& normalTexture, const Vulkan::Texture& emissiveTexture, const Vulkan::Texture& metalnessTexture, const Vulkan::Texture& roughnessTexture,
			const glm::vec3& albedo, float normalScale, float metallic, float roughness, const glm::vec3& emissive)
			: AlbedoTexture(albedoTexture), NormalTexture(normalTexture), EmissiveTexture(emissiveTexture), MetalnessTexture(metalnessTexture), RoughnessTexture(roughnessTexture),
				Albedo(albedo), NormalScale(normalScale), Metallic(metallic), Roughness(roughness), Emissive(emissive) {}
	};
}
