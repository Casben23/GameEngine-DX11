#include "GraphicsEngine.pch.h"
#include "ParticleAssetHandler.h"
#include <fstream>
#include "ParticleEmitter.h"
#include "ParticleSystem.h"
#include <filesystem>

bool ParticleAssetHandler::LoadSystemTemplate(const std::wstring& someFilePath)
{
	auto path = L"ParticleSystemTemplates/" + someFilePath;

	nlohmann::json data;
	std::ifstream f(path);
	f >> data;
	ParticleSystemTemplate tem;
	tem.Path = path;

	for (int i = 0; i < data["Size"]; i++) {
		std::string str = data[std::to_string(i)];
		std::filesystem::path name(str);
		tem.EmitterFiles.push_back(name);
	}

	std::pair mapEntry = { someFilePath, tem };
	mySystemMap.insert(mapEntry);
	for (const auto& filepath : tem.EmitterFiles) {
		bool found = false;
		for (auto i = myEmitterTemplates.begin(); i != myEmitterTemplates.end(); i++)
			if (i->first == filepath + L".json") {
				found = true;
				break;
			}
		if (!found)
			LoadEmitterTemplate(filepath + L".json");
	}
	return false;
}

bool ParticleAssetHandler::LoadEmitterTemplate(const std::wstring& someFilePath)
{

	// TODO: Check if nlohmanns crash och just tuta och kör if file not found

	auto path = L"ParticleSystemTemplates/EmitterTemplates/" + someFilePath;
	nlohmann::json data;
	std::ifstream f(path);
	f >> data;	
	EmitterSettingsData settings;
	settings.GravityScale = data["GravityScale"];
	settings.SpawnRate = data["SpawnRate"];
	settings.LifeTime = data["LifeTime"];
	settings.StartSize = data["StartSize"];
	settings.EndSize = data["EndSize"];
	settings.SpawnAngle = data["SpawnAngle"];
	settings.StartColor = { data["StartColor"]["r"], data["StartColor"]["g"], data["StartColor"]["b"], data["StartColor"]["a"], };
	settings.EndColor = { data["EndColor"]["r"], data["EndColor"]["g"], data["EndColor"]["b"], data["EndColor"]["a"], };
	settings.StartVelocity = { data["StartVelocity"]["x"], data["StartVelocity"]["y"], data["StartVelocity"]["z"] };
	settings.EndVelocity = { data["EndVelocity"]["x"], data["EndVelocity"]["y"], data["EndVelocity"]["z"] };;

	ParticleEmitterTemplate emTemp;
	emTemp.EmitterSettings = settings;
	emTemp.Path = path;

	std::pair mapEntry = { someFilePath, emTemp };
	myEmitterTemplates.insert(mapEntry);

	return true;
}

std::shared_ptr<ParticleSystem> ParticleAssetHandler::GetParticleSystem(const std::wstring& aSystemName)
{
	for (auto i = mySystemMap.begin(); i != mySystemMap.end(); i++)
		if (i->first == aSystemName) {
			auto theSystemThatIsToBeReturnedByThisFunction = std::make_shared<ParticleSystem>();
			for (const auto& e : i->second.EmitterFiles) {
				auto t = myEmitterTemplates[e];
				ParticleSystemEmitter emi_t;
				ParticleEmitter emi;
				emi.Init(t);
				theSystemThatIsToBeReturnedByThisFunction->myEmitters.push_back(emi);
			}
			return theSystemThatIsToBeReturnedByThisFunction;
		}
	LoadSystemTemplate(aSystemName);
	for (auto i = mySystemMap.begin(); i != mySystemMap.end(); i++)
		if (i->first == aSystemName) {
			auto theSystemThatIsToBeReturnedByThisFunction = std::make_shared<ParticleSystem>();
			for (const auto& e : i->second.EmitterFiles) {
				ParticleEmitterTemplate t = myEmitterTemplates[e+L".json"];
				ParticleSystemEmitter emi_t;
				ParticleEmitter emi;
				emi.Init(t);
				theSystemThatIsToBeReturnedByThisFunction->myEmitters.push_back(emi);
			}
			return theSystemThatIsToBeReturnedByThisFunction;
		}

	return nullptr;
}
