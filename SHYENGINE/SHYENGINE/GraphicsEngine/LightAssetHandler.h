#pragma once
#include <vector>
#include "Light.h"
#include "DirectionalLight.h"
#include "EnvironmentLight.h"
class LightAssetHandler
{
	static inline std::vector<std::shared_ptr<Light>> myLights{};
	static inline std::shared_ptr<DirectionalLight> myDirectionalLight;
	static inline std::shared_ptr<EnvironmentLight> myEnvironmentLight;

public:
	
	
	static std::shared_ptr<DirectionalLight> CreateDirectionalLight(Vector4f aColor, float anIntensity, Vector3f aRotation);
	static std::shared_ptr<EnvironmentLight> CreateEnvironmentLight(const std::wstring& aTextureName);

};

