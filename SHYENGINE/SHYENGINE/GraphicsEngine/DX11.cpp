#include "GraphicsEngine.pch.h"
#include "DX11.h"
#include <float.h>

ComPtr<ID3D11Device> DX11::myDevice;
ComPtr<ID3D11DeviceContext> DX11::myContext;
ComPtr<IDXGISwapChain> DX11::mySwapChain;

ComPtr<ID3D11SamplerState> DX11::mySamplerStateDefault;
ComPtr<ID3D11SamplerState> DX11::mySamplerStateWrap;

ComPtr<ID3D11RenderTargetView> DX11::myBackBuffer;
ComPtr<ID3D11DepthStencilView> DX11::myDepthBuffer;

DX11::DX11()
{
}

DX11::~DX11()
{
}

bool DX11::Initialize(HWND aWindowHandle, bool enableDeviceDebug)
{
	HRESULT result;

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	//swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = aWindowHandle;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = true;

	result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		enableDeviceDebug ? D3D11_CREATE_DEVICE_DEBUG : 0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&mySwapChain,
		&myDevice,
		nullptr,
		&myContext
	);

	ComPtr<ID3D11Texture2D> backBufferTexture;
	result = mySwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBufferTexture);

	if (FAILED(result))
	{
		return false;
	}

	result = myDevice->CreateRenderTargetView(backBufferTexture.Get(), nullptr, myBackBuffer.GetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	RECT clientRect = { 0,0,0,0 };
	GetClientRect(aWindowHandle, &clientRect);
	ComPtr<ID3D11Texture2D> depthBufferTexture;
	D3D11_TEXTURE2D_DESC depthBufferDesc = { 0 };
	depthBufferDesc.Width = clientRect.right - clientRect.left;
	depthBufferDesc.Height = clientRect.bottom - clientRect.top;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;


	result = myDevice->CreateTexture2D(&depthBufferDesc, nullptr, depthBufferTexture.GetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	result = myDevice->CreateDepthStencilView(depthBufferTexture.Get(), nullptr, myDepthBuffer.GetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	myContext->OMSetRenderTargets(1, myBackBuffer.GetAddressOf(), myDepthBuffer.Get());

	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = static_cast<FLOAT>(clientRect.right - clientRect.left);
	viewport.Height = static_cast<FLOAT>(clientRect.bottom - clientRect.top);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	myContext->RSSetViewports(1, &viewport);

	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	result = myDevice->CreateSamplerState(&samplerDesc, mySamplerStateDefault.GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	D3D11_SAMPLER_DESC pointSampleDesc = {};
	pointSampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	pointSampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	pointSampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	pointSampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	pointSampleDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	pointSampleDesc.MinLOD = -FLT_MAX;
	pointSampleDesc.MaxLOD = FLT_MAX;

	result = DX11::myDevice->CreateSamplerState(&pointSampleDesc, &mySamplerStateDefault);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void DX11::BeginFrame(std::array<float, 4> aClearColor)
{
	myContext->ClearRenderTargetView(myBackBuffer.Get(), &aClearColor[0]);
	myContext->ClearDepthStencilView(myDepthBuffer.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void DX11::EndFrame()
{
	mySwapChain->Present(1, 0);
}
