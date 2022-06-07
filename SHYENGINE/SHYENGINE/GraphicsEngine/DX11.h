#pragma once
#include <array> 
#include <d3d11.h>
#include <wrl.h>

using namespace Microsoft::WRL;

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11SamplerState;
struct ID3D11SamplerState;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;

class DX11
{
public: 
	DX11();
	~DX11();

	bool Initialize(HWND aWindowHandle, bool enableDeviceDebug);
	void BeginFrame(std::array<float, 4> aClearColor = { 0,0,0,0 });
	void EndFrame();

	static ComPtr<ID3D11Device> myDevice;
	static ComPtr<ID3D11DeviceContext> myContext;
	static ComPtr<IDXGISwapChain> mySwapChain;
	
	static ComPtr<ID3D11SamplerState> mySamplerStateDefault;
	static ComPtr<ID3D11SamplerState> mySamplerStateWrap;

	static ComPtr<ID3D11RenderTargetView> myBackBuffer;
	static ComPtr<ID3D11DepthStencilView> myDepthBuffer;

};

