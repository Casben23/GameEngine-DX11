#pragma once
#include <memory>
#include "DX11.h"
#include "ForwardRenderer.h"
#include "Scene.h"
#include "ModelAssetHandler.h"
#include "ModelInstance.h"
#include "InputHandler.h"
#include "LightAssetHandler.h"
#include <filesystem>
#include "Tools/json.hpp"
#include <fstream>
#include "GBuffer.h"
#include "DeferredRenderer.h"
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_dx11.h"
#include "ImGUI/imgui_impl_win32.h"
#include "ImGUI/misc/cpp/imgui_stdlib.h"

enum BlendState
{
	BS_None,
	BS_AlphaBlend,
	BS_Additive,
	BS_COUNT
};

enum DepthStencilState
{
	DSS_ReadWrite,
	DSS_ReadOnly,
	DSS_COUNT
};

struct ColorPreset
{
	Vector4f color;
	std::string name;
};

class GraphicsEngine
{
	SIZE myWindowSize{ 0,0 };
	HWND myWindowHandle{};
	// Container window message pump.
	static LRESULT CALLBACK WinProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);

public:

	bool Initialize(unsigned someX, unsigned someY, unsigned someWidth, unsigned someHeight, bool enableDeviceDebug);

	void BeginFrame();
	void EndFrame();
	void RenderFrame();

	void Update();
	
	DX11 myFramework;

	ForwardRenderer myForwardRenderer;
	DeferredRenderer myDeferredRenderer;

	std::shared_ptr<GBuffer> myGBuffer;

	std::shared_ptr<Scene> myScene;

	std::shared_ptr<DirectionalLight> myDirectionalLight;
	std::shared_ptr<EnvironmentLight> myEnvironmentLight;
	std::shared_ptr<PointLight> myPointLight;
	
	std::shared_ptr<Camera> myCamera;
	std::shared_ptr<ParticleSystem> ps;
	ModelAssetHandler myModelAssetHandler;

	[[nodiscard]] HWND FORCEINLINE GetWindowHandle() const { return myWindowHandle; }
	[[nodiscard]] SIZE FORCEINLINE GetWindowSize() const { return myWindowSize; }

	void SetBlendState(BlendState aBlendState);
	void SetDepthStencilState(DepthStencilState aDepthStencilState);

	void BlendColor();

	void ImGUIUpdate();

private:
	float Lerp(float a, float b, float t) { return a + t * (b - a); }

	bool ShowImGUIWindow = false;

	std::vector<ColorPreset> myColorPresets;
	Vector3f myFirstBlendColor = { 0,0,0 };
	Vector3f mySecondBlendColor = { 0,0,0 };
	std::array<float, 4> myClearColor;
	float myBlendInterpolation = 0;
	std::string myPresetName;

	bool myIsBlending;
	std::shared_ptr<ModelInstance> mySelectedSceneObject;

	std::array<ComPtr<ID3D11BlendState>, static_cast<unsigned>(BlendState::BS_COUNT)> myBlendStates;
	std::array<ComPtr<ID3D11DepthStencilState>, static_cast<unsigned>(DepthStencilState::DSS_COUNT)> myDepthStencilStates;

};

