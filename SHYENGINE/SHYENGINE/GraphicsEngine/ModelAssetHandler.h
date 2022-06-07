#include <vector>
#include <unordered_map>
#include <memory>
#include "FBXImporterStructs.h"
#include "FBXImporter.h"
#include "ModelInstance.h"

class Material;
class Model;

class ModelAssetHandler
{
	static std::unordered_map<const char*, std::shared_ptr<Model>> myModelRegistry;
	static std::unordered_map<std::wstring, std::shared_ptr<Material>> myMaterialRegistry;

	bool InitUnitCube();

public:
	
	bool Initialize();
	std::shared_ptr<ModelInstance> GetModelInstance(const char* aModelName) const;
	bool LoadModel(const char* someFilePath) const;
};
