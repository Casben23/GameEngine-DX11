#pragma once
#include <unordered_map>
#include "Tools/json.hpp"
#include "ParticleEmitter.h"
#include "ParticleSystem.h"

class ParticleAssetHandler
{
public:
	static bool LoadSystemTemplate(const std::wstring& someFilePath);
	static bool LoadEmitterTemplate(const std::wstring& someFilePath);
	static std::shared_ptr<ParticleSystem> GetParticleSystem(const std::wstring& aSystemName);

private: 
	typedef std::unordered_map<std::wstring, ParticleEmitterTemplate> EmitterTemplateMap;
	typedef std::unordered_map<std::wstring, ParticleSystemTemplate> SystemTemplateMap;

	inline static EmitterTemplateMap myEmitterTemplates{};
	inline static SystemTemplateMap mySystemMap{};

};

