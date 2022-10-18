#include "GraphicsEngine.pch.h"
#include "LightAssetHandler.h"

std::shared_ptr<DirectionalLight> LightAssetHandler::CreateDirectionalLight(Vector4f aColor, float anIntensity, Vector3f aRotation)
{
    myDirectionalLight = std::make_shared<DirectionalLight>();
    myDirectionalLight->Init(aColor, anIntensity);

    myDirectionalLight->myLightBufferData.myDirection = aRotation;

	constexpr float nearPlane = 0.01f;
	constexpr float farPlane = 3000.f;
	const Vector2f resolution = { 2048,2048 };
	 
	myDirectionalLight->myLightBufferData.myNearPlane = nearPlane;
	myDirectionalLight->myLightBufferData.myFarPlane = farPlane;
	
	Matrix4x4f lightProjection;

	lightProjection(1, 1) = 2.0f / static_cast<float>(resolution.x);
	lightProjection(2, 2) = 2.0f / static_cast<float>(resolution.y);
	lightProjection(3, 3) = 1.0f / (farPlane - nearPlane);
	lightProjection(4, 3) = nearPlane / (nearPlane - farPlane);
	lightProjection(4, 4) = 1.0f;

	myDirectionalLight->myLightBufferData.myLightProjection = lightProjection;

	myDirectionalLight->myShadowMap = TextureAssetHandler::CreateDepthStencil(L"DepthEyo", resolution.x, resolution.y);

	myDirectionalLight->myLightBufferData.myCastingShadows = true;

    return myDirectionalLight;
}

std::shared_ptr<EnvironmentLight> LightAssetHandler::CreateEnvironmentLight(const std::wstring& aTextureName)
{
	myEnvironmentLight = std::make_shared<EnvironmentLight>();
    myEnvironmentLight->SetTexture(aTextureName);
    return myEnvironmentLight;
}

std::shared_ptr<PointLight> LightAssetHandler::CreatePointLight(Vector3f aColor, float anIntensity, float aRange, Vector3f aPosition)
{
    myLights.push_back(std::make_shared<PointLight>());
    std::shared_ptr<PointLight> result = std::dynamic_pointer_cast<PointLight>(myLights.back());

    result->Init({ aColor.x, aColor.y,aColor.z,1 }, anIntensity);
	result->SetRange(aRange);
	result->myTransform.SetPosition(aPosition.x, aPosition.y, aPosition.z);
	result->myLightBufferData.myPosition = aPosition;
	result->myLightBufferData.myAttenuation = 1;
	result->myLightBufferData.myLightType = 1;
    return result;
}

std::shared_ptr<SpotLight> LightAssetHandler::CreateSpotLight(Vector3f aColor, float anIntensity, float aRange, float aInnerConeRadius, float aOuterConeRadius, Vector3f aPosition)
{
	myLights.push_back(std::make_shared<SpotLight>());
	std::shared_ptr<SpotLight> result = std::dynamic_pointer_cast<SpotLight>(myLights.back());

	result->Init({ aColor.x, aColor.y,aColor.z,1 }, anIntensity);
	result->SetRange(aRange);
	result->SetInnerCone(aInnerConeRadius);
	result->SetOuterCone(aOuterConeRadius);
	result->myTransform.SetPosition(aPosition.x, aPosition.y, aPosition.z);
	result->myLightBufferData.myPosition = aPosition;
	result->myLightBufferData.myAttenuation = 1;
	result->myLightBufferData.myLightType = 2;
	return result;
}
