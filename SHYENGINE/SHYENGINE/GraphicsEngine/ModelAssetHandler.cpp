#include "GraphicsEngine.pch.h"
#include "ModelAssetHandler.h"
#include "Model.h"
#include <fstream>
#include <string>
#include "Material.h"

std::unordered_map<std::wstring, std::shared_ptr<Material>> ModelAssetHandler::myMaterialRegistry;
std::unordered_map<const char*, std::shared_ptr<Model>> ModelAssetHandler::myModelRegistry;
bool ModelAssetHandler::InitUnitCube()
{
	/*std::vector<Vertex> myMdlVertices = {
		{ Vector4f(50.0f, 50.0f, 50.0f, 1), 		Vector4f(1, 0, 0, 1) },
		{ Vector4f(50.0f, 50.0f, -50.0f, 1),		Vector4f(0, 1, 0, 1) },
		{ Vector4f(50.0f, -50.0f, 50.0f, 1),		Vector4f(0, 0, 1, 1) },
		{ Vector4f(-50.0f, 50.0f, 50.0f, 1),		Vector4f(1, 0, 1, 1) },
		{ Vector4f(50.0f, -50.0f, -50.0f, 1),		Vector4f(0, 1, 1, 1) },
		{ Vector4f(-50.0f, 50.0f, -50.0f, 1),		Vector4f(1, 1, 0, 1) },
		{ Vector4f(-50.0f, -50.0f, 50.0f, 1),		Vector4f(1, 1, 1, 1) },
		{ Vector4f(-50.0f, -50.0f, -50.0f, 1),		Vector4f(0, 0, 0, 1) }
	};

	std::vector<unsigned int> myMdlIndices = {
	 0, 2, 1,
	 4, 1, 2,
	 1, 4, 5,
	 7, 5, 4,
	 5, 7, 3,
	 6, 3, 7,
	 5, 3, 1,
	 0, 1, 3,
	 2, 0, 6,
	 3, 6, 0,
	 7, 4, 6,
	 2, 6, 4

	};

	HRESULT result;

	D3D11_BUFFER_DESC vertexBufferDesc{};
	vertexBufferDesc.ByteWidth = static_cast<UINT>(myMdlVertices.size()) * static_cast<UINT>(sizeof(Vertex));
	vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexSubresourceData{};
	vertexSubresourceData.pSysMem = &myMdlVertices[0];

	ID3D11Buffer* vertexBuffer;
	result = DX11::myDevice->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	D3D11_BUFFER_DESC indexBufferDesc{};
	indexBufferDesc.ByteWidth = static_cast<UINT>(myMdlIndices.size()) * static_cast<UINT>(sizeof(unsigned int));
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA indexSubresourceData{};
	indexSubresourceData.pSysMem = &myMdlIndices[0];

	ID3D11Buffer* indexBuffer;
	result = DX11::myDevice->CreateBuffer(&indexBufferDesc, &indexSubresourceData, &indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	std::ifstream vsFile;
	vsFile.open("DefaultVS.cso", std::ios::binary);
	std::string vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
	ID3D11VertexShader* vertexShader;
	result = DX11::myDevice->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vertexShader);
	if (FAILED(result))
	{
		return false;
	}
	vsFile.close();

	std::ifstream psFile;
	psFile.open("DefaultPS.cso", std::ios::binary);
	std::string psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };
	ID3D11PixelShader* pixelShader;
	result = DX11::myDevice->CreatePixelShader(psData.data(), psData.size(), nullptr, &pixelShader);
	if (FAILED(result))
	{
		return false;
	}
	psFile.close();

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "COLOR", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "COLOR", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "COLOR", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	ID3D11InputLayout* inputLayout;
	result = DX11::myDevice->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), vsData.data(), vsData.size(), &inputLayout);

	Model::MeshData modelData = {};
	modelData.myNumberOfVertices = static_cast<UINT>(myMdlVertices.size());
	modelData.myNumberOfIndices = static_cast<UINT>(myMdlIndices.size());
	modelData.myStride = sizeof(Vertex);
	modelData.myOffset = 0;
	modelData.myVertexBuffer = vertexBuffer;
	modelData.myIndexBuffer = indexBuffer;
	modelData.myVertexShader = vertexShader;
	modelData.myPixelShader = pixelShader;
	modelData.myPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	modelData.myInputLayout = inputLayout;

	std::shared_ptr<Model> mdl = std::make_shared<Model>();

	mdl->Init(modelData, "Cube");
	myModelRegistry.insert({ "Cube", mdl });*/
	return true;
}

bool ModelAssetHandler::Initialize()
{
	return InitUnitCube();
}

std::shared_ptr<ModelInstance> ModelAssetHandler::GetModelInstance(const char* someFilePath) const
{
	std::shared_ptr<ModelInstance> mdlIns = std::make_shared<ModelInstance>();

	mdlIns->Init(myModelRegistry[someFilePath]);
	return mdlIns;
}

bool ModelAssetHandler::LoadModel(const char* someFilePath) const
{
	const std::string ansiFileName = someFilePath;

	TGA::FBXModel tgaModel;
	if (TGA::FBXImporter::LoadModel(ansiFileName, tgaModel))
	{
		std::vector<Model::MeshData> mdlMeshData;
		mdlMeshData.resize(tgaModel.Meshes.size());

		for (size_t i = 0; i < tgaModel.Meshes.size(); i++)
		{
			std::vector<Vertex> mdlVertices;

			TGA::FBXModel::FBXMesh& mesh = tgaModel.Meshes[i];

			const std::wstring wideMatName(mesh.MaterialName.begin(), mesh.MaterialName.end());
			std::shared_ptr<Material> meshMaterial;
			if (myMaterialRegistry.find(wideMatName) != myMaterialRegistry.end())
			{
				meshMaterial = myMaterialRegistry[wideMatName];
			}
			else
			{
				meshMaterial = std::make_shared<Material>();
				meshMaterial->Init(wideMatName, 
					{
					static_cast<float>(rand() % 100) / 100,
					static_cast<float>(rand() % 100) / 100,
					static_cast<float>(rand() % 100) / 100,
					});

				myMaterialRegistry.insert({ wideMatName, meshMaterial });
			}
			
			Model::MeshData& meshData = mdlMeshData[i];
			meshData.myMaterial = meshMaterial;

			for (size_t v = 0; v < mesh.Vertices.size(); v++)
			{
				Vertex vertex;

				vertex.myPosition.x = mesh.Vertices[v].Position[0];
				vertex.myPosition.y = mesh.Vertices[v].Position[1];
				vertex.myPosition.z = mesh.Vertices[v].Position[2];
				vertex.myPosition.w = mesh.Vertices[v].Position[3];

				mdlVertices.push_back(vertex);

				for (int vCol = 0; vCol < 4; vCol++)
				{
					mdlVertices[v].myVertexColors[vCol].x = mesh.Vertices[v].VertexColors[vCol][0];
					mdlVertices[v].myVertexColors[vCol].y = mesh.Vertices[v].VertexColors[vCol][1];
					mdlVertices[v].myVertexColors[vCol].z = mesh.Vertices[v].VertexColors[vCol][2];
					mdlVertices[v].myVertexColors[vCol].w = mesh.Vertices[v].VertexColors[vCol][3];
				}

				mdlVertices[v].myVertexColors[0] =
				{
					static_cast<float>(rand() % 100) / 100,
					static_cast<float>(rand() % 100) / 100,
					static_cast<float>(rand() % 100) / 100,
					1.0f
				};
			}
			std::vector<unsigned int> mdlIndices = mesh.Indices;

			HRESULT result;

			D3D11_BUFFER_DESC vertexBufferDesc{};
			vertexBufferDesc.ByteWidth = static_cast<UINT>(mdlVertices.size()) * static_cast<UINT>(sizeof(Vertex));
			vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
			vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			D3D11_SUBRESOURCE_DATA vertexSubresourceData{};
			vertexSubresourceData.pSysMem = &mdlVertices[0];

			ID3D11Buffer* vertexBuffer;
			result = DX11::myDevice->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &vertexBuffer);
			if (FAILED(result))
			{
				return false;
			}

			D3D11_BUFFER_DESC indexBufferDesc{};
			indexBufferDesc.ByteWidth = static_cast<UINT>(mdlIndices.size()) * static_cast<UINT>(sizeof(unsigned int));
			indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
			indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

			D3D11_SUBRESOURCE_DATA indexSubresourceData{};
			indexSubresourceData.pSysMem = &mdlIndices[0];

			ID3D11Buffer* indexBuffer;
			result = DX11::myDevice->CreateBuffer(&indexBufferDesc, &indexSubresourceData, &indexBuffer);
			if (FAILED(result))
			{
				return false;
			}

			std::ifstream vsFile;
			vsFile.open("VertexShader.cso", std::ios::binary);
			std::string vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
			ID3D11VertexShader* vertexShader;
			result = DX11::myDevice->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vertexShader);
			if (FAILED(result))
			{
				return false;
			}
			vsFile.close();

			std::ifstream psFile;
			psFile.open("PixelShader.cso", std::ios::binary);
			std::string psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };
			ID3D11PixelShader* pixelShader;
			result = DX11::myDevice->CreatePixelShader(psData.data(), psData.size(), nullptr, &pixelShader);
			if (FAILED(result))
			{
				return false;
			}
			psFile.close();

			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "COLOR", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "COLOR", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "COLOR", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				
			};

			ID3D11InputLayout* inputLayout;
			result = DX11::myDevice->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), vsData.data(), vsData.size(), &inputLayout);

			Model::MeshData modelData = {};

			modelData.myNumberOfVertices = static_cast<UINT>(mdlVertices.size());
			modelData.myNumberOfIndices = static_cast<UINT>(mdlIndices.size());
			modelData.myStride = sizeof(Vertex);
			modelData.myOffset = 0;
			modelData.myVertexBuffer = vertexBuffer;
			modelData.myIndexBuffer = indexBuffer;
			modelData.myVertexShader = vertexShader;
			modelData.myPixelShader = pixelShader;
			modelData.myPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			modelData.myInputLayout = inputLayout;

			modelData.myMaterial = meshMaterial;
			mdlMeshData[i] = modelData;
		}
		std::shared_ptr<Model> model = std::make_shared<Model>();
		model->Init(mdlMeshData, someFilePath);
		myModelRegistry.insert({ someFilePath, model });
		return true;
	}

	return false;
}
