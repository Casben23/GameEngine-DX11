#include "GraphicsEngine.pch.h"
#include "LightAssetHandler.h"

std::shared_ptr<DirectionalLight> LightAssetHandler::CreateDirectionalLight(Vector4f aColor, float anIntensity, Vector3f aRotation)
{
    myDirectionalLight = std::make_shared<DirectionalLight>();
    myDirectionalLight->Init(aColor, anIntensity);

    myDirectionalLight->myLightBufferData.myDirection = aRotation;
	
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

    result->Init({aColor.x, aColor.y, aColor.z, 1}, anIntensity);
    result->SetRange(aRange);
    result->myTransform.SetPosition(aPosition.x, aPosition.y, aPosition.z);
    result->myLightBufferData.myLightType = 1;
    return result;
}
