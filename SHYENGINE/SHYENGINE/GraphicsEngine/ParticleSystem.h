#pragma once
#include <string>
#include <vector>
#include "ParticleEmitter.h"
#include "SceneObject.h"

struct ParticleSystemTemplate 
{
	std::wstring Path;
	std::vector<std::wstring> EmitterFiles;
};

struct ParticleSystemEmitter 
{
	ParticleEmitter Emitter;
	EmitterSettingsData Settings;
	Matrix4x4f Transform;
};

class ParticleSystem : public SceneObject{
public:
	void Update(float aDeltaTime);
	__forceinline const std::vector<ParticleEmitter>& GetEmitters() const { return myEmitters; }
	void SetLocation2(Vector4f aPos) {
		for (auto& e : myEmitters)
			e.myPosition = aPos;
	}
private:
	friend class ParticleAssetHandler;
	std::vector<ParticleEmitter> myEmitters;
};