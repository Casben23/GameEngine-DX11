#pragma once
#include "SceneObject.h"
class Light : public SceneObject
{
	friend class LightAssetHandler;

public:  
	struct LightBufferData 
	{
		Vector4f myColor;
		float myIntensity;
		Vector3f myDirection;
	};

protected:
	LightBufferData myLightBufferData;
	
public:
	virtual ~Light() override = default;
	virtual void Init(Vector4f aColor, float anIntensity);
	
	virtual void SetAsResource(ComPtr<ID3D11Buffer> aLightBuffer) = 0;
	
	FORCEINLINE Vector4f GetColor() const { return myLightBufferData.myColor; }
	FORCEINLINE float& GetIntensity() { return myLightBufferData.myIntensity; }

	LightBufferData& GetLightBufferData() { return myLightBufferData; }
	void SetIntensity(float aIntensity) { myLightBufferData.myIntensity = aIntensity; }
};

