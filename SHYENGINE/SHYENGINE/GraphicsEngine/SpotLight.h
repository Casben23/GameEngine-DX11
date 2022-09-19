#pragma once
#include "Light.h"
class SpotLight : public Light
{
	friend class LightAssetHandler;

public:
	virtual ~SpotLight() = default;

	void SetRange(float aRange);
	void SetInnerCone(float aRadius);
	void SetOuterCone(float aRadius);

	FORCEINLINE float GetRange() const { return myLightBufferData.myRange; }
	FORCEINLINE float GetInnerCone() const { return myLightBufferData.mySpotInnerRadius; }
	FORCEINLINE float GetOuterCone() const { return myLightBufferData.mySpotOuterRadius; }


};

