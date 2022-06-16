#pragma once
#include "Math/Matrix/Matrix4x4.hpp"
#include <wrl.h>
#include "Camera.h"
#include <vector>
#include "Model.h"
#include "ModelInstance.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "EnvironmentLight.h"
class ForwardRenderer
{
	struct FrameBufferData
	{
		Matrix4x4f View;
		Matrix4x4f Projection;
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

	Microsoft::WRL::ComPtr<ID3D11Buffer> myFrameBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> myObjectBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> myMaterialBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> myLightBuffer;

public:
	bool Initialize();

	void Render(const std::shared_ptr<Camera>& aCamera, const std::vector<std::shared_ptr<ModelInstance>>& aModelList, const std::shared_ptr<DirectionalLight>& aDirectionalLight, const std::shared_ptr<EnvironmentLight>& anEnvironmentLight);
};

