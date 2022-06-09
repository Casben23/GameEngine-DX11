#include "GraphicsEngine.pch.h"
#include "GraphicsEngine.h"
#include "InputHandler.h"
#include "Timer.h"

bool GraphicsEngine::Initialize(unsigned someX, unsigned someY,
	unsigned someWidth, unsigned someHeight,
	bool enableDeviceDebug)
{
	// Initialize our window:
	WNDCLASS windowClass = {};
	windowClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc = GraphicsEngine::WinProc;
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.lpszClassName = L"SHYENGINE";
	RegisterClass(&windowClass);

	myWindowHandle = CreateWindow(
		L"SHYENGINE",
		L"SHYENGINE",
		WS_OVERLAPPEDWINDOW | WS_POPUP | WS_VISIBLE,
		someX,
		someY,
		someWidth,
		someHeight,
		nullptr, nullptr, nullptr,
		this
		);

	// F1 -- This is where we should init our Framework
	// ex: myFramework.Initialize(myWindowHandle, false);

	myFramework.Initialize(myWindowHandle, true);
	myScene = std::make_shared<Scene>();

	myCamera = std::make_shared<Camera>();
	myCamera->Init(90, { 1920, 1080 }, 0.1f, 1500.f);

	myCamera->SetLocation(0, 0, -300.f);

	myModelAssetHandler.Initialize();
	//myScene->AddGameObject(myModelAssetHandler.GetModelInstance(L"Cube"));
	myScene->SetCamera(myCamera);

	if (myModelAssetHandler.LoadModel("SM_Particle_Chest.fbx"))
	{
		std::shared_ptr<ModelInstance> mdlChest = myModelAssetHandler.GetModelInstance("SM_Particle_Chest.fbx");
		myScene->AddGameObject(mdlChest);
	}
	
	if (myModelAssetHandler.LoadModel("gremlin_sk.fbx", "gremlin@walk.fbx"))
	{
		std::shared_ptr<ModelInstance> mdlGremlin = myModelAssetHandler.GetModelInstance("gremlin_sk.fbx");
		myScene->AddGameObject(mdlGremlin);
	}


	if (!myForwardRenderer.Initialize())
	{
		return false;
	}

	return true;
}

LRESULT CALLBACK GraphicsEngine::WinProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{	
	// We want to be able to access the Graphics Engine instance from inside this function.
	InputHandler::UpdateEvents(uMsg, wParam, lParam);

	static GraphicsEngine* graphicsEnginePtr = nullptr;

	if(uMsg == WM_DESTROY || uMsg == WM_CLOSE)
	{
		PostQuitMessage(0);
	}
	else if (uMsg == WM_CREATE)
	{
		const CREATESTRUCT* createdStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
		graphicsEnginePtr = static_cast<GraphicsEngine*>(createdStruct->lpCreateParams);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void GraphicsEngine::BeginFrame()
{
	// F1 - This is where we clear our buffers and start the DX frame.
	// ex: myFramework.BeginFrame({1, 0.5f, 0, 1});
	myFramework.BeginFrame({ 0.1f,0.1f,0.1f,1 });
}

void GraphicsEngine::RenderFrame()
{
	// Will be fleshed out later!
	if (myScene)
	{
		const std::shared_ptr<Camera> camera = myScene->GetMainCamera();
		const std::vector<std::shared_ptr<ModelInstance>> modelToRender = myScene->GetSceneObjects();
		myForwardRenderer.Render(camera, modelToRender);
	}
}

void GraphicsEngine::Update()
{
	for (auto& modelInstance : myScene->GetSceneObjects())
	{
		modelInstance->Update();
	}
	myCamera->Update();
	InputHandler::UpdateInput();
	Timer::Update();
}

void GraphicsEngine::EndFrame()
{
	// F1 - This is where we finish our rendering and tell the framework
	// to present our result to the screen.
	// ex: myFramework.EndFrame();
	myFramework.EndFrame();
}
