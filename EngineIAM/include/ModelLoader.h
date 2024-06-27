#pragma once
#include "PreRequesites.h"
#include "fbxsdk.h"

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

	bool LoadModel(const std::string& filePath);
	const std::vector<SimpleVertex>& GetVertices() const { return vertices; }
	const std::vector<uint32_t>& GetIndices() const { return indices; }

	void ProcessNode(FbxNode* node);
	void ProcessMesh(FbxMesh* mesh);

private:
	FbxManager* lSdkManager;
	FbxScene* lScene;
	std::vector<SimpleVertex> vertices;
	std::vector<unsigned int> indices;

};

