#pragma once
#include "Light.h"
class SpotLight : public Light
{
	friend class LightAssetHandler;

public:
	virtual ~SpotLight() = default;

	void SetRange(float aRange) { myLightBufferData.myRange = aRange;}
	void SetInnerCone(float aRadius) { myLightBufferData.mySpotInnerRadius = aRadius; }
	void SetOuterCone(float aRadius) { myLightBufferData.mySpotOuterRadius = aRadius; }
	void SetAsResource(ComPtr<ID3D11Buffer> aLightBuffer) override { aLightBuffer; };

	FORCEINLINE float GetRange() const { return myLightBufferData.myRange; }
	FORCEINLINE float GetInnerCone() const { return myLightBufferData.mySpotInnerRadius; }
	FORCEINLINE float GetOuterCone() const { return myLightBufferData.mySpotOuterRadius; }


};

