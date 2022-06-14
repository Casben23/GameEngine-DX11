#include "GraphicsEngine.pch.h"
#include "ForwardRenderer.h"
#include "Camera.h"
#include "Material.h"

bool ForwardRenderer::Initialize()
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
	return true;
}

void ForwardRenderer::Render(const std::shared_ptr<Camera>& aCamera, const std::vector<std::shared_ptr<ModelInstance>>& aModelList)
{
	HRESULT result = S_FALSE;
	D3D11_MAPPED_SUBRESOURCE bufferData; 

	myFrameBufferData.View = Matrix4x4f::GetFastInverse(aCamera->GetTransform());
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
	ZeroMemory(&bufferData, sizeof(D3D11_MAPPED_SUBRESOURCE));
	result = DX11::myContext->Map(myObjectBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferData);
	if (FAILED(result))
	{
		return;
	}
	memcpy_s(bufferData.pData, sizeof(ObjectBufferData), &myObjectBufferData, sizeof(ObjectBufferData));

	

	for (const std::shared_ptr<ModelInstance>& model : aModelList)
	{
		myObjectBufferData.World = model->GetTransform();
		
		if (model->GetModel()->GetSkeleton()->GetRoot())
		{
			myObjectBufferData.myHasBones = true;
			memcpy_s(&myObjectBufferData.myBoneData[0], sizeof(Matrix4x4f) * 128, &model->GetBoneTransforms(), sizeof(Matrix4x4f) * 128);
		}
		
		for (size_t i = 0; i < model->GetNumMeshes(); i++)
		{
			const Model::MeshData& meshData = model->GetMeshData(i);
			myObjectBufferData.World = model->GetTransform();
			DX11::myContext->Unmap(myObjectBuffer.Get(), 0);

			if (meshData.myMaterial)
			{
				meshData.myMaterial->SetAsResource(myMaterialBuffer);
			}

			result = DX11::myContext->Map(myMaterialBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferData);
			if (FAILED(result))
			{
				return;
			}

			memcpy(bufferData.pData, &myMaterialBufferData, sizeof(MaterialBufferData));
			DX11::myContext->Unmap(myMaterialBuffer.Get(), 0);
			
			DX11::myContext->IASetVertexBuffers(0, 1, meshData.myVertexBuffer.GetAddressOf(), &meshData.myStride, &meshData.myOffset);
			DX11::myContext->IASetIndexBuffer(meshData.myIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

			DX11::myContext->IASetPrimitiveTopology(static_cast<D3D_PRIMITIVE_TOPOLOGY>(meshData.myPrimitiveTopology));
			DX11::myContext->IASetInputLayout(meshData.myInputLayout.Get());
			DX11::myContext->VSSetShader(meshData.myVertexShader.Get(), nullptr, 0);
			DX11::myContext->PSSetShader(meshData.myPixelShader.Get(), nullptr, 0);

			DX11::myContext->VSSetConstantBuffers(1, 1, myObjectBuffer.GetAddressOf());
			DX11::myContext->PSSetConstantBuffers(1, 1, myObjectBuffer.GetAddressOf());
			DX11::myContext->PSSetConstantBuffers(2, 1, myMaterialBuffer.GetAddressOf());

			DX11::myContext->DrawIndexed(meshData.myNumberOfIndices, 0, 0);

		}
	}
}
