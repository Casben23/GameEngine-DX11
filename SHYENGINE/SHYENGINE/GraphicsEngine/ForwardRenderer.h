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
constexpr UINT MAX_FORWARD_LIGHTS = 8;

class ParticleSystem;

class ForwardRenderer
{
	struct SceneLightBuffer
	{
		Light::LightBufferData myDirectionalLight;
		Light::LightBufferData Lights[MAX_FORWARD_LIGHTS];
		unsigned int myNumLights;
		Vector3f Padding;
	} mySceneLightBufferData;


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

public:
	bool Initialize();
	void RenderModels(const std::shared_ptr<Camera>& aCamera, const std::vector<std::shared_ptr<ModelInstance>>& aModelList, const std::shared_ptr<DirectionalLight>& aDirectionalLight, const std::shared_ptr<EnvironmentLight>& anEnvironmentLight);
	void RenderParticles(const std::shared_ptr<Camera>& aCamera, const std::vector<std::shared_ptr<ParticleSystem>>& aParticleSystemList);
};

