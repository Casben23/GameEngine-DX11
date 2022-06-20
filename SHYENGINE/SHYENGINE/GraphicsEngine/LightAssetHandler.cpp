#include "GraphicsEngine.pch.h"
#include "LightAssetHandler.h"

std::shared_ptr<DirectionalLight> LightAssetHandler::CreateDirectionalLight(Vector4f aColor, float anIntensity, Vector3f aRotation)
{
    myDirectionalLight = std::make_shared<DirectionalLight>();
    myDirectionalLight->Init(aColor, anIntensity);

    myDirectionalLight->myLightBufferData.myDirection = Vector3f( 45,45,45 );
	
    return myDirectionalLight;
}

std::shared_ptr<EnvironmentLight> LightAssetHandler::CreateEnvironmentLight(const std::wstring& aTextureName)
{
	myEnvironmentLight = std::make_shared<EnvironmentLight>();
    myEnvironmentLight->SetTexture(aTextureName);
    return myEnvironmentLight;
}
