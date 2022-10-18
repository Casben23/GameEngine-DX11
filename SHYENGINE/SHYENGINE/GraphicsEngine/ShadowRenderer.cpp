#include "GraphicsEngine.pch.h"
#include "ShadowRenderer.h"
#include "Material.h"

bool ShadowRenderer::Initialize()
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

void ShadowRenderer::Render(const std::shared_ptr<Light>& aLight, const std::vector<std::shared_ptr<ModelInstance>>& aModelList)
{
    HRESULT result = S_FALSE;
    D3D11_MAPPED_SUBRESOURCE bufferData;

    const Light::LightBufferData lightData = aLight->GetLightBufferData();

    myFrameBufferData.View = lightData.myLightView;
    myFrameBufferData.CamTranslation = lightData.myPosition;
    myFrameBufferData.Projection = lightData.myLightProjection;
	myFrameBufferData.FarPlane = lightData.myFarPlane;
	myFrameBufferData.NearPlane = lightData.myNearPlane;

    DX11::myContext->PSSetShader(nullptr, nullptr, 0);
	DX11::myContext->GSSetShader(nullptr, nullptr, 0);

	ZeroMemory(&bufferData, sizeof(D3D11_MAPPED_SUBRESOURCE));
	result = DX11::myContext->Map(myFrameBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferData);
	if (FAILED(result))
	{
		return;
	}

	memcpy_s(bufferData.pData, sizeof(FrameBufferData), &myFrameBufferData, sizeof(FrameBufferData));

	DX11::myContext->Unmap(myFrameBuffer.Get(), 0);
	DX11::myContext->VSSetConstantBuffers(0, 1, myFrameBuffer.GetAddressOf());

	for (const std::shared_ptr<ModelInstance>& model : aModelList)
	{
		for (unsigned int m = 0; m < model->GetNumMeshes(); m++)
		{
			const Model::MeshData& meshData = model->GetMeshData(m);

			if (model->GetModel()->GetSkeleton()->GetRoot())
			{
				myObjectBufferData.myHasBones = true;
				memcpy_s(&myObjectBufferData.myBoneData[0], sizeof(Matrix4x4f) * 128, &model->GetBoneTransforms(), sizeof(Matrix4x4f) * 128);
			}
			ZeroMemory(&bufferData, sizeof(D3D11_MAPPED_SUBRESOURCE));
			result = DX11::myContext->Map(myObjectBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferData);
			if (FAILED(result))
			{
				return;
			}
			memcpy_s(bufferData.pData, sizeof(ObjectBufferData), &myObjectBufferData, sizeof(ObjectBufferData));
			DX11::myContext->Unmap(myObjectBuffer.Get(), 0);

			DX11::myContext->VSSetConstantBuffers(1, 1, myObjectBuffer.GetAddressOf());

			DX11::myContext->IASetVertexBuffers(0, 1, meshData.myVertexBuffer.GetAddressOf(), &meshData.myStride, &meshData.myOffset);
			DX11::myContext->IASetIndexBuffer(meshData.myIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

			DX11::myContext->IASetPrimitiveTopology(static_cast<D3D_PRIMITIVE_TOPOLOGY>(meshData.myPrimitiveTopology));
			DX11::myContext->IASetInputLayout(meshData.myInputLayout.Get());

			meshData.myMaterial->SetAsResource(myMaterialBuffer);
			DX11::myContext->VSSetShader(meshData.myVertexShader.Get(), nullptr, 0);
			DX11::myContext->PSSetShader(nullptr, nullptr, 0);

			DX11::myContext->DrawIndexed(meshData.myNumberOfIndices, 0, 0);
		}
	}
}
