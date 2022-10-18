#pragma once
#include "Light.h"
class DirectionalLight : public Light
{
public:
	void ClearShadowMap();
	void SetShadowMapAsDepth();
	void SetShadowMapAsResource(int aSlot);
	void SetAsResource(ComPtr<ID3D11Buffer> aLightBuffer) override;
};

