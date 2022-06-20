#pragma once
#include <memory>
#include "DX11.h"
#include "ForwardRenderer.h"
#include "Scene.h"
#include "ModelAssetHandler.h"
#include "ModelInstance.h"
#include "InputHandler.h"
#include "LightAssetHandler.h"
class GraphicsEngine
{
	SIZE myWindowSize{0,0};
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
	std::shared_ptr<Scene> myScene;
	
	std::shared_ptr<DirectionalLight> myDirectionalLight;
	std::shared_ptr<EnvironmentLight> myEnvironmentLight;

	std::shared_ptr<Camera> myCamera;
	ModelAssetHandler myModelAssetHandler;

	[[nodiscard]] HWND FORCEINLINE GetWindowHandle() const { return myWindowHandle; }
	[[nodiscard]] SIZE FORCEINLINE GetWindowSize() const { return myWindowSize; }
};

