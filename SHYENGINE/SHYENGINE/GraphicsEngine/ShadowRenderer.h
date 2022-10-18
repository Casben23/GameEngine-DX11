#pragma once
#include "Light.h"
#include "ModelInstance.h"

class ShadowRenderer
{
	struct FrameBufferData
	{
		Matrix4x4f View;
		Matrix4x4f Projection;
		Vector3f CamTranslation;

		float NearPlane;
		float FarPlane;

		Vector3f padding;
	} myFrameBufferData;

	struct ObjectBufferData
	{
		Matrix4x4f World;
		bool myHasBones = false;
		Vector3f Padding;
		Matrix4x4f myBoneData[128];
	} myObjectBufferData;

	struct MaterialBufferData
	{
		Vector3f Albedo;
		float Padding;
	} myMaterialBufferData;

	ComPtr<ID3D11Buffer> myFrameBuffer;
	ComPtr<ID3D11Buffer> myObjectBuffer;
	ComPtr<ID3D11Buffer> myMaterialBuffer;

public:
	bool Initialize();

	void Render(const std::shared_ptr<Light>& aLight, const std::vector<std::shared_ptr<ModelInstance>>& aModelList);
};

