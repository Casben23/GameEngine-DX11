#include "GraphicsEngine.pch.h"
#include "GraphicsEngine.h"
#include "InputHandler.h"
#include "Timer.h"
#include "ParticleAssetHandler.h"

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


	myFramework.Initialize(myWindowHandle, true);
	myScene = std::make_shared<Scene>();

	myCamera = std::make_shared<Camera>();
	myCamera->Init(90, { 1920, 1080 }, 0.1f, 1500.f);

	myCamera->SetLocation(0, 0, -5.f);

	myModelAssetHandler.Initialize();
	myScene->SetCamera(myCamera);

	ps = ParticleAssetHandler::GetParticleSystem(L"TestSystem.json");
	ps->SetLocation2({ 50.0f,0.0f,0.0f,1.0f });

	//if (myModelAssetHandler.LoadModel("SM_Particle_Chest.fbx"))
	//{
	//	std::shared_ptr<ModelInstance> mdlChest = myModelAssetHandler.GetModelInstance("SM_Particle_Chest.fbx");
	//	myScene->AddGameObject(mdlChest);
	//}

	/*if (myModelAssetHandler.LoadModel("Particle_Chest.fbx"))
	{
		std::shared_ptr<ModelInstance> mdlChest = myModelAssetHandler.GetModelInstance("Particle_Chest.fbx");
		myScene->AddGameObject(mdlChest);
		mdlChest->SetLocation(100, 0, 100);
	}*/

	if (myModelAssetHandler.LoadModel("gremlin_sk.fbx", "gremlin@walk.fbx"))
	{
		std::shared_ptr<ModelInstance> mdlGremlin = myModelAssetHandler.GetModelInstance("gremlin_sk.fbx");
		myScene->AddGameObject(mdlGremlin);
		mdlGremlin->SetLocation(0, 0, 100);
		mdlGremlin->SetRotation(0, 180, 0);
	}

	Vector4f color = { 1,1,1,1 };
	Vector3f dir = { 0,0,0 };

	myDirectionalLight = LightAssetHandler::CreateDirectionalLight(color, 2, dir);
	myEnvironmentLight = LightAssetHandler::CreateEnvironmentLight(L"skansen_cubemap.dds");

	if (!myForwardRenderer.Initialize())
	{
		return false;
	}

	myBlendStates[BlendState::BS_None] = nullptr;

	HRESULT result;

	D3D11_BLEND_DESC alphaBlendDesc = {};
	alphaBlendDesc.RenderTarget[0].BlendEnable = true;
	alphaBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	alphaBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	alphaBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	alphaBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	alphaBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	alphaBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
	alphaBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	result = DX11::myDevice->CreateBlendState(&alphaBlendDesc, &myBlendStates[BlendState::BS_Additive]);

	if (FAILED(result)) 
	{
		return false;
	}

	D3D11_DEPTH_STENCIL_DESC readOnlyDepthDesc = {};
	readOnlyDepthDesc.DepthEnable = true;
	readOnlyDepthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	readOnlyDepthDesc.DepthFunc = D3D11_COMPARISON_LESS;
	readOnlyDepthDesc.StencilEnable = false;

	result = DX11::myDevice->CreateDepthStencilState(&readOnlyDepthDesc, &myDepthStencilStates[DepthStencilState::DSS_ReadOnly]);

	if (FAILED(result)) 
	{
		return false;
	}

	myDepthStencilStates[DepthStencilState::DSS_ReadWrite] = nullptr;

	return true;
}

LRESULT CALLBACK GraphicsEngine::WinProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	// We want to be able to access the Graphics Engine instance from inside this function.
	InputHandler::UpdateEvents(uMsg, wParam, lParam);

	static GraphicsEngine* graphicsEnginePtr = nullptr;

	if (uMsg == WM_DESTROY || uMsg == WM_CLOSE)
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
	myFramework.BeginFrame({ 0.1f,0.1f,0.1f,1 });
}

void GraphicsEngine::RenderFrame()
{
	if (myScene)
	{
		const std::shared_ptr<Camera> camera = myScene->GetMainCamera();
		const std::vector<std::shared_ptr<ModelInstance>>& modelToRender = myScene->GetSceneObjects();
		myForwardRenderer.RenderModels(camera, modelToRender, myDirectionalLight, myEnvironmentLight);

		SetBlendState(BlendState::BS_Additive);
		SetDepthStencilState(DepthStencilState::DSS_ReadOnly);
		myForwardRenderer.RenderParticles(camera, { ps });
		SetBlendState(BlendState::BS_None);
		SetDepthStencilState(DepthStencilState::DSS_ReadWrite);
	}
}

void GraphicsEngine::Update()
{
	for (auto& modelInstance : myScene->GetSceneObjects())
	{
		modelInstance->Update();
	}
	ps->Update(Timer::GetDeltaTime());
	myCamera->Update();
	InputHandler::UpdateInput();
	Timer::Update();
}

void GraphicsEngine::SetBlendState(BlendState aBlendState)
{
	DX11::myContext->OMSetBlendState(myBlendStates[aBlendState].Get(), nullptr, 0xffffffff);
}

void GraphicsEngine::SetDepthStencilState(DepthStencilState aDepthStencilState)
{
	DX11::myContext->OMSetDepthStencilState(myDepthStencilStates[aDepthStencilState].Get(), 0);
}

void GraphicsEngine::EndFrame()
{
	myFramework.EndFrame();
}
