#pragma once
#include "Light.h"
#include "Texture.h"
class EnvironmentLight : public Light
{
	friend class LightAssetHandler;

	std::shared_ptr<Texture> myTexture;

public:

	virtual void SetAsResource(ComPtr<ID3D11Buffer> aLightBuffer) override;
};

