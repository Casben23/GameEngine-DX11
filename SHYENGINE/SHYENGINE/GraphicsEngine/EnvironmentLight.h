#pragma once
#include "Light.h"
#include "Texture.h"
#include "TextureAssetHandler.h"
class EnvironmentLight : public Light
{
	friend class LightAssetHandler;

	std::shared_ptr<Texture> myTexture;

public:

	void SetTexture(const std::wstring aTexturePath);
	virtual void SetAsResource(ComPtr<ID3D11Buffer> aLightBuffer) override;
};

