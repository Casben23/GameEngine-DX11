#pragma once
#include "Light.h"
#include "SceneObject.h"
class PointLight : public Light
{
	friend class LightAssetHandler;

public:
	virtual ~PointLight() = default;

	void SetRange(float aRange);
	void SetAsResource(ComPtr<ID3D11Buffer> aLightBuffer) override;
	FORCEINLINE float GetRange() const { return myLightBufferData.myRange; }
};

