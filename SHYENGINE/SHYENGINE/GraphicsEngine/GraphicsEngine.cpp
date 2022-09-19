#include "GraphicsEngine.pch.h"
#include "GraphicsEngine.h"
#include "InputHandler.h"
#include "Timer.h"
#include "ParticleAssetHandler.h"
#include <math.h>

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

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(myWindowHandle);
	ImGui_ImplDX11_Init(DX11::myDevice.Get(), DX11::myContext.Get());

	myScene = std::make_shared<Scene>();

	myCamera = std::make_shared<Camera>();
	myCamera->Init(90, { 1920, 1080 }, 0.1f, 1500.f);

	myCamera->GetTransform().SetPosition(0, 0, -5.f);

	nlohmann::json data;
	std::ifstream f("EngineSettings/Settings.json");
	f >> data;
	myClearColor = { data["Color"]["r"], data["Color"]["g"], data["Color"]["b"], data["Color"]["a"]};


	myModelAssetHandler.Initialize();
	myScene->SetCamera(myCamera);

	ps = ParticleAssetHandler::GetParticleSystem(L"TestSystem.json");
	ps->SetLocation2({ 50.0f,0.0f,0.0f,1.0f });

	RECT clientRect = { 0,0,0,0 };
	GetClientRect(myWindowHandle, &clientRect);
	myGBuffer = std::make_shared<GBuffer>(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);

	if (myModelAssetHandler.LoadModel("Particle_Chest.fbx"))
	{
		std::shared_ptr<ModelInstance> mdlChest = myModelAssetHandler.GetModelInstance("Particle_Chest.fbx");
		mdlChest->SetName("Chest");
		myScene->AddGameObject(mdlChest);
		mdlChest->GetTransform().SetPosition(100, 0, 100);
	}

	if (myModelAssetHandler.LoadModel("gremlin_sk.fbx", "gremlin@walk.fbx"))
	{
		std::shared_ptr<ModelInstance> mdlGremlin = myModelAssetHandler.GetModelInstance("gremlin_sk.fbx");
		mdlGremlin->SetName("Gremlin");
		myScene->AddGameObject(mdlGremlin);
		mdlGremlin->GetTransform().SetPosition(0, 0, 100);
		mdlGremlin->GetTransform().SetRotation(0, 180, 0);
	}

	Vector4f color = { 1, 1, 1,1 };
	Vector3f dir = { 1,1,1 };
	
	myDirectionalLight = LightAssetHandler::CreateDirectionalLight(color, 0.5f, dir);
	myEnvironmentLight = LightAssetHandler::CreateEnvironmentLight(L"skansen_cubemap.dds");
	myPointLight = LightAssetHandler::CreatePointLight({ 255,0,0 }, 100, 100, {0,0,0});

	myScene->AddLight(myPointLight);

	if (!myForwardRenderer.Initialize())
	{
		return false;
	}

	if (!myDeferredRenderer.Init())
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

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK GraphicsEngine::WinProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

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
	myFramework.BeginFrame(myClearColor);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void GraphicsEngine::RenderFrame()
{
	if (myScene)
	{
		const std::shared_ptr<Camera> camera = myScene->GetMainCamera();
		const std::vector<std::shared_ptr<ModelInstance>>& modelToRender = myScene->GetSceneObjects();
		//myForwardRenderer.RenderModels(camera, modelToRender, myDirectionalLight, myEnvironmentLight);
		myGBuffer->ClearResource(0);
		myGBuffer->Clear();
		myGBuffer->SetAsTarget();
		myDeferredRenderer.GenerateGBuffer(camera, modelToRender, Timer::GetDeltaTime(), Timer::GetTotalTime());
		
		myGBuffer->ClearTarget();
		myGBuffer->SetAsResource(0);

		DX11::myContext->OMSetRenderTargets(1, DX11::myBackBuffer.GetAddressOf(), DX11::myDepthBuffer.Get());
		SetDepthStencilState(DepthStencilState::DSS_ReadOnly);
		myDeferredRenderer.Render(camera, myDirectionalLight, myEnvironmentLight);
		SetBlendState(BlendState::BS_Additive);
		SetDepthStencilState(DepthStencilState::DSS_ReadOnly);
		myForwardRenderer.RenderParticles(camera, { ps });
		SetDepthStencilState(DepthStencilState::DSS_ReadWrite);
		SetBlendState(BlendState::BS_None);

		ImGUIUpdate();
		//ImGui::ShowDemoWindow();
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

void GraphicsEngine::BlendColor()
{
	ImGui::Begin("Color Blending");

	static int selected = -1;
	static int selected1 = -1;

	if (ImGui::TreeNode("Presets 1"))
	{
		for (int n = 0; n < myColorPresets.size(); n++)
		{
			char buf1[32];
			sprintf_s(buf1, myColorPresets[n].name.c_str(), n);
			if (ImGui::Selectable(buf1, selected == n))
				selected = n;
		}
		ImGui::TreePop();
	}
	if (selected != -1)
	{
		ImGui::SameLine();
		ImGui::ColorButton("##color", { myColorPresets[selected].color.x, myColorPresets[selected].color.y, myColorPresets[selected].color.z, myColorPresets[selected].color.w, });
	}

	if (ImGui::TreeNode("Presets 2"))
	{
		for (int n = 0; n < myColorPresets.size(); n++)
		{
			char buf1[32];
			sprintf_s(buf1, myColorPresets[n].name.c_str(), n);
			if (ImGui::Selectable(buf1, selected1 == n))
				selected1 = n;
		}
		ImGui::TreePop();
	}
	if (selected1 != -1)
	{
		ImGui::SameLine();
		ImGui::ColorButton("##color1", { myColorPresets[selected1].color.x, myColorPresets[selected1].color.y, myColorPresets[selected1].color.z, myColorPresets[selected1].color.w, });
	}

	ImGui::SliderFloat("Blend Value", &myBlendInterpolation, 0, 1);
	
	Vector3f blendColor;
	if (selected != -1 && selected1 != -1)
	{
		blendColor = { Lerp(myColorPresets[selected].color.x, myColorPresets[selected1].color.x, myBlendInterpolation),
					   Lerp(myColorPresets[selected].color.y, myColorPresets[selected1].color.y, myBlendInterpolation),
					   Lerp(myColorPresets[selected].color.z, myColorPresets[selected1].color.z, myBlendInterpolation) };
	}
	ImGui::ColorButton("Blended Color", { blendColor.x, blendColor.y, blendColor.z, 1 }, 0, { 100,100 });

	if (ImGui::Button("Save Blended Color Preset"))
	{
		ColorPreset colorPreset;
		colorPreset.color = { blendColor.x,blendColor.y,blendColor.z, 1 };

		if (myPresetName.empty())
		{
			colorPreset.name = "Preset" + std::to_string(myColorPresets.size()) + " (blend)";
			nlohmann::json file;
			std::ifstream filestream("EngineSettings/Presets.json");

			filestream >> file;

			file["Presets"][colorPreset.name]["r"] = myClearColor[0];
			file["Presets"][colorPreset.name]["g"] = myClearColor[1];
			file["Presets"][colorPreset.name]["b"] = myClearColor[2];
			file["Presets"][colorPreset.name]["a"] = myClearColor[3];

			std::ofstream s("EngineSettings/Presets.json");
			s << file;
		}
		else
		{
			colorPreset.name = myPresetName;

			nlohmann::json file;
			std::ifstream filestream("EngineSettings/Presets.json");

			filestream >> file;

			file["Presets"][colorPreset.name]["r"] = myClearColor[0];
			file["Presets"][colorPreset.name]["g"] = myClearColor[1];
			file["Presets"][colorPreset.name]["b"] = myClearColor[2];
			file["Presets"][colorPreset.name]["a"] = myClearColor[3];

			std::ofstream s("EngineSettings/Presets.json");
			s << file;
		}
		myPresetName = "";
		myColorPresets.push_back(colorPreset);
	}

	ImGui::End();
}

void GraphicsEngine::ImGUIUpdate()
{
	bool ImGUIWindowsOpen = true;
	mySelectedSceneObject = myScene->GetSceneObjects()[0];

	ImGui::Begin("Clear Color Picker", &ImGUIWindowsOpen, ImGuiWindowFlags_MenuBar);

	float color[4] = { myClearColor[0],myClearColor[1],myClearColor[2],myClearColor[3] };
	ImGui::ColorPicker4("Clear Color", color);
	myClearColor[0] = color[0];
	myClearColor[1] = color[1];
	myClearColor[2] = color[2];
	myClearColor[3] = color[3];

	static int selected1 = -1;

	if (ImGui::TreeNode("Color Presets"))
	{
		for (int n = 0; n < myColorPresets.size(); n++)
		{
			char buf1[32];
			sprintf_s(buf1, myColorPresets[n].name.c_str(), n);
			if (ImGui::Selectable(buf1, selected1 == n))
				selected1 = n;
		}
		ImGui::TreePop();
	}

	if (ImGui::Button("Blend Color"))
	{
		myIsBlending = !myIsBlending;
	}


	if (myIsBlending)
	{
		BlendColor();
	}

	ImGui::InputText("Preset Name", &myPresetName);

	if (ImGui::Button("Save Color Preset"))
	{
		ColorPreset colorPreset;
		colorPreset.color = { myClearColor[0],myClearColor[1] ,myClearColor[2], 1 };

		if (myPresetName.empty())
		{
			colorPreset.name = "Preset" + std::to_string(myColorPresets.size());
			nlohmann::json file;
			std::ifstream filestream("EngineSettings/Presets.json");

			filestream >> file;

			file["Presets"][colorPreset.name]["r"] = myClearColor[0];
			file["Presets"][colorPreset.name]["g"] = myClearColor[1];
			file["Presets"][colorPreset.name]["b"] = myClearColor[2];
			file["Presets"][colorPreset.name]["a"] = myClearColor[3];

			std::ofstream s("EngineSettings/Presets.json");
			s << file;
		}
		else
		{
			colorPreset.name = myPresetName;

			nlohmann::json file;
			std::ifstream filestream("EngineSettings/Presets.json");

			filestream >> file;

			file["Presets"][colorPreset.name]["r"] = myClearColor[0];
			file["Presets"][colorPreset.name]["g"] = myClearColor[1];
			file["Presets"][colorPreset.name]["b"] = myClearColor[2];
			file["Presets"][colorPreset.name]["a"] = myClearColor[3];

			std::ofstream s("EngineSettings/Presets.json");
			s << file;
		}
		myPresetName = "";
		myColorPresets.push_back(colorPreset);
	}

	if (ImGui::Button("Save Settings"))
	{
		nlohmann::json file;
		file["Color"]["r"] = myClearColor[0];
		file["Color"]["g"] = myClearColor[1];
		file["Color"]["b"] = myClearColor[2];
		file["Color"]["a"] = myClearColor[3];

		std::ofstream filestream("EngineSettings/Settings.json");
		filestream << file;
	}

	ImGui::LabelText("", "Directional Light Settings");
	ImGui::DragFloat("Intensity", &myDirectionalLight->GetIntensity(),.1f,0.f,100.f);

	float lightRot[3] = { myDirectionalLight->GetTransform().GetRotation().x,
						 myDirectionalLight->GetTransform().GetRotation().y,
						 myDirectionalLight->GetTransform().GetRotation().z };

	ImGui::DragFloat3("Rotation", lightRot, 0.1f, -360, 360);

	myDirectionalLight->GetTransform().SetRotation(lightRot[0], lightRot[1], lightRot[2]);
	myDirectionalLight->GetLightBufferData().myDirection = myDirectionalLight->GetTransform().GetRotation();
	ImGui::End();

	ImGui::Begin("Scene Hierarchy", &ImGUIWindowsOpen, ImGuiWindowFlags_MenuBar);

	static int selected = -1;
	for (int n = 0; n < myScene->GetSceneObjects().size(); n++)
	{
		char buf[32];
		if (myScene->GetSceneObjects()[n]->GetName().empty())
		{
			sprintf_s(buf, "Object %d", n);
		}
		else
		{
			sprintf_s(buf, myScene->GetSceneObjects()[n]->GetName().c_str(), n);
		}
		if (ImGui::Selectable(buf, selected == n))
			selected = n;
	}
	ImGui::End();

	ImGui::Begin("Properties", &ImGUIWindowsOpen, ImGuiWindowFlags_MenuBar);

	if (selected >= 0)
	{
		float pos[3] = { myScene->GetSceneObjects()[selected]->GetTransform().GetPosition().x,
						 myScene->GetSceneObjects()[selected]->GetTransform().GetPosition().y,
						 myScene->GetSceneObjects()[selected]->GetTransform().GetPosition().z };

		ImGui::DragFloat3("Position", pos, 1, -INT_MAX, INT_MAX);
		myScene->GetSceneObjects()[selected]->GetTransform().SetPosition(pos[0], pos[1], pos[2]);

		float rot[3] = { myScene->GetSceneObjects()[selected]->GetTransform().GetRotation().x,
						 myScene->GetSceneObjects()[selected]->GetTransform().GetRotation().y,
						 myScene->GetSceneObjects()[selected]->GetTransform().GetRotation().z };

		ImGui::DragFloat3("Rotation", rot, 0.05f, -INT_MAX, INT_MAX);
		myScene->GetSceneObjects()[selected]->GetTransform().SetRotation(rot[0], rot[1], rot[2]);

		float scale[3] = { myScene->GetSceneObjects()[selected]->GetTransform().GetScale().x,
						 myScene->GetSceneObjects()[selected]->GetTransform().GetScale().y,
						 myScene->GetSceneObjects()[selected]->GetTransform().GetScale().z };

		ImGui::DragFloat3("Scale", scale, 1, -INT_MAX, INT_MAX);
		myScene->GetSceneObjects()[selected]->GetTransform().SetScale(scale[0], scale[1], scale[2]);
	}

	ImGui::End();
}

void GraphicsEngine::EndFrame()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	myFramework.EndFrame();
}
