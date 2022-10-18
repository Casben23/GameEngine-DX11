#pragma once
#include "SceneObject.h"
#include "DepthStencil.h"

class Light : public SceneObject
{
	friend class LightAssetHandler;

public:  
	struct LightBufferData 
	{
		Matrix4x4f myLightView;
		Matrix4x4f myLightProjection;

		Vector4f myColor;

		float myIntensity;
		Vector3f myDirection;

		float myRange;
		Vector3f myPosition;

		float myAttenuation;
		float mySpotInnerRadius;
		float mySpotOuterRadius;
		unsigned myLightType;
		bool myCastingShadows;

		float myNearPlane;
		float myFarPlane;

		float padding;
	};

	std::unique_ptr<DepthStencil> myShadowMap;
protected:
	
public:
	LightBufferData myLightBufferData;
	virtual ~Light() override = default;
	virtual void Init(Vector4f aColor, float anIntensity);

	virtual void SetAsResource(ComPtr<ID3D11Buffer> aLightBuffer) = 0;
	
	FORCEINLINE Vector4f GetColor() const { return myLightBufferData.myColor; }
	FORCEINLINE float& GetIntensity() { return myLightBufferData.myIntensity; }

	LightBufferData& GetLightBufferData() { return myLightBufferData; }
	void SetIntensity(float aIntensity) { myLightBufferData.myIntensity = aIntensity; }
	
};

