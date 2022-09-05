#include "GraphicsEngine.pch.h"
#include "DeferredRenderer.h"
#include "Material.h"

bool DeferredRenderer::Init()
{
	HRESULT result = S_FALSE;

	D3D11_BUFFER_DESC bufferDescription = { 0 };
	bufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	bufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDescription.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	bufferDescription.ByteWidth = sizeof(FrameBufferData);
	result = DX11::myDevice->CreateBuffer(&bufferDescription, nullptr, myFrameBuffer.GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	bufferDescription.ByteWidth = sizeof(ObjectBufferData);
	result = DX11::myDevice->CreateBuffer(&bufferDescription, nullptr, myObjectBuffer.GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	bufferDescription.ByteWidth = sizeof(MaterialBufferData);
	result = DX11::myDevice->CreateBuffer(&bufferDescription, nullptr, myMaterialBuffer.GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	bufferDescription.ByteWidth = sizeof(Light::LightBufferData);
	result = DX11::myDevice->CreateBuffer(&bufferDescription, nullptr, myLightBuffer.GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

void DeferredRenderer::Render(const std::shared_ptr<Camera>& aCamera, const std::shared_ptr<DirectionalLight>& aDirectionalLight, const std::shared_ptr<EnvironmentLight>& anEnvironmentLight)
{
	HRESULT result = S_FALSE;
	D3D11_MAPPED_SUBRESOURCE bufferData;

	myFrameBufferData.View = Matrix4x4f::GetFastInverse(aCamera->GetTransform().GetMatrix());
	// This might be where everything breaks???! WE do not know math
	myFrameBufferData.CamTranslation = aCamera->GetTransform().GetPosition();
	myFrameBufferData.Projection = aCamera->GetProjection();

	ZeroMemory(&bufferData, sizeof(D3D11_MAPPED_SUBRESOURCE));
	result = DX11::myContext->Map(myFrameBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferData);
	if (FAILED(result))
	{
		return;
	}
	memcpy_s(bufferData.pData, sizeof(FrameBufferData), &myFrameBufferData, sizeof(FrameBufferData));
	DX11::myContext->Unmap(myFrameBuffer.Get(), 0);
	DX11::myContext->VSSetConstantBuffers(0, 1, myFrameBuffer.GetAddressOf());

	if (aDirectionalLight)
	{
		aDirectionalLight->SetAsResource(myLightBuffer);
	}

	if (anEnvironmentLight)
	{
		anEnvironmentLight->SetAsResource(nullptr);
	}

	DX11::myContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DX11::myContext->IASetInputLayout(nullptr);
	DX11::myContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
	DX11::myContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
	DX11::myContext->GSSetShader(nullptr, nullptr, 0);
}

void DeferredRenderer::GenerateGBuffer(
	const std::shared_ptr<Camera>& aCamera,
	const std::vector<std::shared_ptr<ModelInstance>>& aModelList,
	float aDeltaTime, float aTotalTime)
{
	HRESULT result = S_FALSE;
	D3D11_MAPPED_SUBRESOURCE bufferData;

	myFrameBufferData.View = Matrix4x4f::GetFastInverse(aCamera->GetTransform().GetMatrix());
	// This might be where everything breaks???! WE do not know math
	myFrameBufferData.CamTranslation = aCamera->GetTransform().GetPosition();
	myFrameBufferData.Projection = aCamera->GetProjection();

	ZeroMemory(&bufferData, sizeof(D3D11_MAPPED_SUBRESOURCE));
	result = DX11::myContext->Map(myFrameBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferData);
	if (FAILED(result))
	{
		return;
	}
	memcpy_s(bufferData.pData, sizeof(FrameBufferData), &myFrameBufferData, sizeof(FrameBufferData));
	DX11::myContext->Unmap(myFrameBuffer.Get(), 0);

	DX11::myContext->VSSetConstantBuffers(0, 1, myFrameBuffer.GetAddressOf());
	DX11::myContext->PSSetConstantBuffers(0, 1, myFrameBuffer.GetAddressOf());

	for (const std::shared_ptr<ModelInstance>& model : aModelList) 
	{
		for(unsigned int m = 0; m < model->GetNumMeshes(); m++)
		{
			const Model::MeshData& meshData = model->GetMeshData(m);
			myObjectBufferData.World = model->GetTransform().GetMatrix();
			ZeroMemory(&bufferData, sizeof(D3D11_MAPPED_SUBRESOURCE));
			result = DX11::myContext->Map(myObjectBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferData);
			if (FAILED(result))
			{
				return;
			}
			memcpy_s(bufferData.pData, sizeof(ObjectBufferData), &myObjectBufferData, sizeof(ObjectBufferData));
			DX11::myContext->Unmap(myObjectBuffer.Get(), 0);

			DX11::myContext->VSSetConstantBuffers(1, 1, myObjectBuffer.GetAddressOf());
			DX11::myContext->PSSetConstantBuffers(1, 1, myObjectBuffer.GetAddressOf());

			if (meshData.myMaterial)
			{
				meshData.myMaterial->SetAsResource(myMaterialBuffer);
			}

			DX11::myContext->IASetVertexBuffers(0, 1, meshData.myVertexBuffer.GetAddressOf(), &meshData.myStride, &meshData.myOffset);
			DX11::myContext->IASetIndexBuffer(meshData.myIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

			DX11::myContext->IASetPrimitiveTopology(static_cast<D3D_PRIMITIVE_TOPOLOGY>(meshData.myPrimitiveTopology));
			DX11::myContext->IASetInputLayout(meshData.myInputLayout.Get());
			DX11::myContext->PSSetConstantBuffers(2, 1, myMaterialBuffer.GetAddressOf());
			DX11::myContext->PSSetShader(myGBufferShader.Get(), nullptr, 0);
			DX11::myContext->DrawIndexed(meshData.myNumberOfIndices, 0, 0);
		}
	}

}
