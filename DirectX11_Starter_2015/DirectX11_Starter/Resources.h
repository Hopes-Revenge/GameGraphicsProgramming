#pragma once
#include "Mesh.h"
#include "Material.h"

class Resources
{
public:
	const static int MAX_NUM_MESHES = 50;//Max number of meshes we can load
	Resources(ID3D11Device* newDevice);
	~Resources();

	Mesh* GetMeshIfLoaded(const char* meshName);//Returns the mesh only if it is loaded
	bool IsMeshLoaded(const char* meshName);
	void LoadMesh(const char* meshName, const char* filePath);//Load a mesh for latter
	void AddMesh(Mesh* mesh);
	int FindMesh(const char* meshName);
private:
	ID3D11Device* device;
	Mesh* meshes[MAX_NUM_MESHES];
	int numberOfMeshes;
};

