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
constexpr UINT MAX_DEFERRED_LIGHTS = 8;

class DeferredRenderer
{
	struct SceneLightBuffer
	{
		Light::LightBufferData myDirectionalLight;
		Light::LightBufferData myLights[MAX_DEFERRED_LIGHTS];

		unsigned int myNumLights;
		Vector3f Padding;
	}mySceneLightBufferData;

	struct FrameBufferData
	{
		Matrix4x4f View;
		Matrix4x4f Projection;
		Vector3f CamTranslation;
		unsigned int Padding;
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

	Microsoft::WRL::ComPtr<ID3D11PixelShader> myEnvironmentShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> myGBufferShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> myFullscreenShader;

public:
	bool Init();

	void Render(const std::shared_ptr<Camera>& aCamera, const std::shared_ptr<DirectionalLight>& aDirectionalLight, const std::shared_ptr<EnvironmentLight>& anEnvironmentLight, std::vector<std::shared_ptr<Light>> aLightList);

	void GenerateGBuffer(
		const std::shared_ptr<Camera>& aCamera,
		const std::vector<std::shared_ptr<ModelInstance>>& aModelList,
		float aDeltaTime, float aTotalTime);
};

