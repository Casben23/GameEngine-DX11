#include "GraphicsEngine.pch.h"
#include "EnvironmentLight.h"

void EnvironmentLight::SetTexture(const std::wstring aTexturePath)
{
	if (TextureAssetHandler::LoadTexture(aTexturePath))
	{
		myTexture = TextureAssetHandler::GetTexture(aTexturePath);
	}
}

void EnvironmentLight::SetAsResource(ComPtr<ID3D11Buffer> aLightBuffer)
{
	if (myTexture)
	{
		myTexture->SetAsResource(10);
	}
}
