#include "GraphicsEngine.pch.h"
#include "ParticleEmitter.h"
#include <fstream>
#include <memory>
#include <random>
void ParticleEmitter::InitParticle(size_t aParticleIndex)
{
	myParticles[aParticleIndex].Color = myEmitterSettings.StartColor;
	myParticles[aParticleIndex].LifeTime = 0.0f;
	myParticles[aParticleIndex].Scale = { myEmitterSettings.StartSize,myEmitterSettings.StartSize,myEmitterSettings.StartSize };
	myParticles[aParticleIndex].Position = myPosition;
}

bool ParticleEmitter::Init(const ParticleEmitterTemplate& aTemplate)
{
	myEmitterSettings = aTemplate.EmitterSettings;
	myStride = static_cast<UINT>(sizeof(ParticleVertex));

	myPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;

	//const size_t maxNumberOfParticles = static_cast<size_t>(ceilf(myEmitterSettings.SpawnRate * myEmitterSettings.LifeTime));

	const size_t maxNumberOfParticles = 200;

	myNummberOfAliveParticles = 0;

	myParticles.resize(maxNumberOfParticles);
	float offsetedTime = 0;
	for (int i = 0; i < myParticles.size(); i++) {
		InitParticle(i);
		offsetedTime += 0.1f;
	}


	HRESULT result;

	D3D11_BUFFER_DESC vertexBufferDesc{};
	vertexBufferDesc.ByteWidth = static_cast<UINT>(myParticles.size() * static_cast<UINT>(sizeof(ParticleVertex)));
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA vertexSubresourceData{};
	vertexSubresourceData.pSysMem = &myParticles[0];

	result = DX11::myDevice->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &myVertexBuffer);
	if (FAILED(result))
	{
		return false;
	}


	std::ifstream vsFile;
	vsFile.open("ParticleVS.cso", std::ios::binary);
	std::string vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
	result = DX11::myDevice->CreateVertexShader(vsData.data(), vsData.size(), nullptr, myVertexShader.GetAddressOf());
	if (FAILED(result)) {
		return false;
	}
	vsFile.close();

	std::ifstream gsFile;
	gsFile.open("ParticleGS.cso", std::ios::binary);
	std::string gsData = { std::istreambuf_iterator<char>(gsFile), std::istreambuf_iterator<char>() };
	result = DX11::myDevice->CreateGeometryShader(gsData.data(), gsData.size(), nullptr, myGeometryShader.GetAddressOf());
	if (FAILED(result)) {
		return false;
	}
	gsFile.close();

	std::ifstream psFile;
	psFile.open("ParticlePS.cso", std::ios::binary);
	std::string psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };
	result = DX11::myDevice->CreatePixelShader(psData.data(), psData.size(), nullptr, myPixelShader.GetAddressOf());
	if (FAILED(result)) {
		return false;
	}
	psFile.close();


	D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "VELOCITY", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "SCALE", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "LIFETIME", 0, DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	result = DX11::myDevice->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), vsData.data(), vsData.size(), myInputLayout.GetAddressOf());
	if (FAILED(result))
		return false;

	if (TextureAssetHandler::LoadTexture(L"ParticleStar.dds"))
	{
		myTexture = TextureAssetHandler::GetTexture(L"ParticleStar.dds");
	}

	return true;
}

void ParticleEmitter::Update(float aDeltaTime)
{
	//myEmitionTime += aDeltaTime;
	//if (myEmitionTime < 100000)
	if (myNummberOfAliveParticles < myParticles.size() && true) {
		for (int i = 0; i < myEmitterSettings.SpawnRate; i++)
		{
			if (myNummberOfAliveParticles >= myParticles.size())
				break;

			std::random_device rd;  //Will be used to obtain a seed for the random number engine
			std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
			std::uniform_real_distribution distrib(-5.0f, 5.0f);
			Vector4f dir;
			Vector4f targetDir = { myEmitterSettings.StartVelocity.x,myEmitterSettings.StartVelocity.y,myEmitterSettings.StartVelocity.z, 0 };
		look_for_stewie: dir = { distrib(gen), distrib(gen), distrib(gen), 0 }; dir += targetDir; if (dir.x == 0) if (dir.y == 0) if (dir.z == 0) goto look_for_stewie;

			myParticles[myNummberOfAliveParticles].Position = myPosition;
			myParticles[myNummberOfAliveParticles].Velocity = { dir.x, dir.y, dir.z };

			myParticles[myNummberOfAliveParticles].Color = myEmitterSettings.StartColor;
			myParticles[myNummberOfAliveParticles].LifeTime = 0.0f;
			myParticles[myNummberOfAliveParticles].Scale = { myEmitterSettings.StartSize,myEmitterSettings.StartSize,myEmitterSettings.StartSize };
			myParticles[myNummberOfAliveParticles].Position = myPosition;

			//myParticles[myNummberOfAliveParticles].Wake({ myPos.x * 100,myPos.y * 100,myPos.z }, dir, myParticleSpeed, myTargetTimeAlive, myUseFade, myRotationSpeed, myShouldShrink, myParticleSize, myParticleSizeYDivisor);
			//myParticles[myNummberOfAliveParticles]->Wake({ myPos.x *100,myPos.y *100,myPos.z }, dir, myParticleSpeed, myTargetTimeAlive, myUseFade, myRotationSpeed, myShouldShrink, myParticleSize, myParticleSizeYDivisor);
			myNummberOfAliveParticles++;
		}
	}

	for (unsigned int i = 0; i < myNummberOfAliveParticles; i++) {
		auto& particle = myParticles[i];
		particle.LifeTime += aDeltaTime;
		Vector4f speed = { particle.Velocity.x,particle.Velocity.y,particle.Velocity.z,  0 };
		particle.Position += speed * aDeltaTime;
		if (particle.LifeTime >= myEmitterSettings.LifeTime) {
			std::swap(myParticles[i], myParticles[myNummberOfAliveParticles - 1]);
			myNummberOfAliveParticles--;
		}
	}
}

void ParticleEmitter::SetAsResource() const
{
	HRESULT result = S_FALSE;

	D3D11_MAPPED_SUBRESOURCE bufferData;
	ZeroMemory(&bufferData, sizeof(D3D11_MAPPED_SUBRESOURCE));
	result = DX11::myContext->Map(
		myVertexBuffer.Get(),
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&bufferData
	);

	memcpy_s(bufferData.pData, sizeof(ParticleVertex) * myParticles.size(), &myParticles[0], sizeof(ParticleVertex) * myParticles.size());

	DX11::myContext->Unmap(myVertexBuffer.Get(), 0);

	DX11::myContext->IASetVertexBuffers(0, 1, myVertexBuffer.GetAddressOf(), &myStride, &myOffset);
	DX11::myContext->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(myPrimitiveTopology));
	DX11::myContext->IASetInputLayout(myInputLayout.Get());

	DX11::myContext->VSSetShader(myVertexShader.Get(), nullptr, 0);
	DX11::myContext->GSSetShader(myGeometryShader.Get(), nullptr, 0);
	DX11::myContext->PSSetShader(myPixelShader.Get(), nullptr, 0);

	if (myTexture)
	{
		myTexture->SetAsResource(0);
	}

}

void ParticleEmitter::Draw() const
{
	DX11::myContext->Draw(static_cast<UINT>(myNummberOfAliveParticles), 0);
}
