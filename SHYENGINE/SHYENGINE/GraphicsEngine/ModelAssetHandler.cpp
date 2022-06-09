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

bool ModelAssetHandler::LoadModel(const char* modelFilePath) const
{
	const std::string ansiFileName = modelFilePath;

	TGA::FBXModel tgaModel;
	
	if (TGA::FBXImporter::LoadModel(ansiFileName, tgaModel))
	{
		std::vector<Model::MeshData> mdlMeshData;
		mdlMeshData.resize(tgaModel.Meshes.size());

		Skeleton mdlSkeleton;
		const bool hasSkeleton = tgaModel.Skeleton.GetRoot();

		if (hasSkeleton)
		{
			for (size_t amount = 0; amount < tgaModel.Skeleton.Bones.size(); amount++)
			{
				Skeleton::Bone bone;

				memcpy(&bone.myBindPoseInverse, &tgaModel.Skeleton.Bones[amount].BindPoseInverse, sizeof(bone.myBindPoseInverse)); 
				bone.myChildren = tgaModel.Skeleton.Bones[amount].Children;
				bone.myParent = tgaModel.Skeleton.Bones[amount].Parent;
				bone.myName = tgaModel.Skeleton.Bones[amount].Name;
				
				mdlSkeleton.myBones.push_back(bone);
			}
		}

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

				/*if (hasSkeleton)
				{
					mdlVertices[v].myBoneIDs = {
						mesh.Vertices[v].BoneIDs[0],
						mesh.Vertices[v].BoneIDs[1],
						mesh.Vertices[v].BoneIDs[2],
						mesh.Vertices[v].BoneIDs[3]
					};

					mdlVertices[v].myBoneWeights = {
						mesh.Vertices[v].BoneWeights[0],
						mesh.Vertices[v].BoneWeights[1],
						mesh.Vertices[v].BoneWeights[2],
						mesh.Vertices[v].BoneWeights[3]
					};
				}*/
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
				{ "BONEIDS", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "BONEWEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
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
		
		if (hasSkeleton)
		{
			model->Init(mdlMeshData, modelFilePath, mdlSkeleton);
		}
		else
		{
			model->Init(mdlMeshData, modelFilePath);
		}
		
		TGA::FBXAnimation tgaAnimation;

		/*if (TGA::FBXImporter::LoadAnimation(ansiFileName, model->GetSkeleton()->myBoneName, tgaAnimation))
		{
			Animation result;

			result.myDuration = tgaAnimation.Duration;
			result.myFramesPerSecond = tgaAnimation.FramesPerSecond;
			result.myLength = tgaAnimation.Length;
			result.myName = std::wstring(tgaAnimation.Name.begin(), tgaAnimation.Name.end());

			for (size_t f = 0; f < result.myFrames.size(); f++)
			{
				memcpy(&result.myFrames[f].myLocalTransforms, &tgaAnimation.Frames[f].LocalTransforms, sizeof(tgaAnimation.Frames[f].LocalTransforms));
			}
			model->AddAnimation(result);
		}*/
		myModelRegistry.insert({ modelFilePath, model });
		return true;
	}

	return false;
}

bool ModelAssetHandler::LoadModel(const char* modelFilePath, const char* animFilePath) const
{
	const std::string ansiFileName = modelFilePath;
	const std::string animFileName = animFilePath;

	TGA::FBXModel tgaModel;

	if (TGA::FBXImporter::LoadModel(ansiFileName, tgaModel))
	{
		std::vector<Model::MeshData> mdlMeshData;
		mdlMeshData.resize(tgaModel.Meshes.size());

		Skeleton mdlSkeleton;
		const bool hasSkeleton = tgaModel.Skeleton.GetRoot();
		mdlSkeleton.myName = ansiFileName;

		if (hasSkeleton)
		{
			for (size_t amount = 0; amount < tgaModel.Skeleton.Bones.size(); amount++)
			{
				Skeleton::Bone bone;

				memcpy(&bone.myBindPoseInverse, &tgaModel.Skeleton.Bones[amount].BindPoseInverse, sizeof(bone.myBindPoseInverse));
				bone.myChildren = tgaModel.Skeleton.Bones[amount].Children;
				bone.myParent = tgaModel.Skeleton.Bones[amount].Parent;
				bone.myName = tgaModel.Skeleton.Bones[amount].Name;
				mdlSkeleton.myBoneNames.push_back(bone.myName);
				
				mdlSkeleton.myBones.push_back(bone);
			}
		}

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

				if (hasSkeleton)
				{
					mdlVertices[v].myBoneIDs = {
						mesh.Vertices[v].BoneIDs[0],
						mesh.Vertices[v].BoneIDs[1],
						mesh.Vertices[v].BoneIDs[2],
						mesh.Vertices[v].BoneIDs[3]
					};

					mdlVertices[v].myBoneWeights = {
						mesh.Vertices[v].BoneWeights[0],
						mesh.Vertices[v].BoneWeights[1],
						mesh.Vertices[v].BoneWeights[2],
						mesh.Vertices[v].BoneWeights[3]
					};
				}
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
				{ "BONEIDS", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "BONEWEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
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

		if (hasSkeleton)
		{
			model->Init(mdlMeshData, modelFilePath, mdlSkeleton);
		}
		else
		{
			model->Init(mdlMeshData, modelFilePath);
		}

		TGA::FBXAnimation tgaAnimation;

		if (TGA::FBXImporter::LoadAnimation(animFileName, model->GetSkeleton()->myBoneNames, tgaAnimation))
		{
			Animation result;

			result.myDuration = tgaAnimation.Duration;
			result.myFramesPerSecond = tgaAnimation.FramesPerSecond;
			result.myLength = tgaAnimation.Length;
			result.myName = std::wstring(tgaAnimation.Name.begin(), tgaAnimation.Name.end());
			result.myFrames.resize(tgaAnimation.Frames.size());
			for (size_t f = 0; f < tgaAnimation.Frames.size(); f++)
			{
				result.myFrames[f].myLocalTransforms.resize(tgaAnimation.Frames[f].LocalTransforms.size());
				for (size_t b = 0; b < tgaAnimation.Frames[f].LocalTransforms.size(); b++)
				{
					memcpy(&result.myFrames[f].myLocalTransforms[b], &tgaAnimation.Frames[f].LocalTransforms[b], sizeof(Matrix4x4f));
					result.myFrames[f].myLocalTransforms[b] = Matrix4x4f::Transpose(result.myFrames[f].myLocalTransforms[b]);
				}
			}
			model->AddAnimation(result);
		}
		myModelRegistry.insert({ modelFilePath, model });
		return true;
	}

	return false;
}
