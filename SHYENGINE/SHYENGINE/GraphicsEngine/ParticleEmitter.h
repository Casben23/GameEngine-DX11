#pragma once
#include "GraphicsEngine.h"

struct ParticleVertex
{
	Vector4f Position = { 0,0,0,1 };
	Vector4f Color = { 0,0,0,0 };
	Vector3f Velocity = { 0,0,0 };
	Vector3f Scale = { 1,1,1 };
	float LifeTime = 0;
};

struct EmitterSettingsData
{
	float SpawnRate = 1.0f;
	float SpawnAngle = 0.0f;
	float LifeTime;
	Vector3f StartVelocity;
	Vector3f EndVelocity;
	float GravityScale;
	float StartSize;
	float EndSize;
	Vector4f StartColor;
	Vector4f EndColor;
};

struct ParticleEmitterTemplate
{
	std::wstring Path;
	EmitterSettingsData EmitterSettings;
};

class ParticleEmitter
{
	friend class ParticleAssetHandler;
	friend class ParticleSystem;
	friend class ParticleSystemEmitter;

	EmitterSettingsData myEmitterSettings;

	std::vector<ParticleVertex> myParticles;
	ComPtr<ID3D11Buffer> myVertexBuffer;
	UINT myStride;
	UINT myOffset;
	ComPtr<ID3D11VertexShader> myVertexShader;
	ComPtr<ID3D11GeometryShader> myGeometryShader;
	ComPtr<ID3D11PixelShader> myPixelShader;
	UINT myPrimitiveTopology;
	ComPtr<ID3D11InputLayout> myInputLayout;

	std::shared_ptr<Texture> myTexture;
	Vector4f myPosition;

	int myNummberOfAliveParticles;

	void InitParticle(size_t aParticleIndex);

public:
	virtual ~ParticleEmitter() = default;

	virtual bool Init(const ParticleEmitterTemplate& aTemplate);
	virtual void Update(float aDeltaTime);

	virtual void SetAsResource() const;
	virtual void Draw() const;

	FORCEINLINE const EmitterSettingsData& GetEmitterSettings() const { return myEmitterSettings; }

};

