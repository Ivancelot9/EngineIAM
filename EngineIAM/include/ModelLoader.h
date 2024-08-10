#pragma once
#include "PreRequesites.h"
#include "fbxsdk.h"
#include "MeshComponent.h"

class ModelLoader
{
public:
    // Constructor y destructor: manejan la inicializaci�n y limpieza de recursos del SDK de FBX.
    ModelLoader();
    ~ModelLoader();

    // Carga un modelo desde un archivo FBX dado el path.
    // Devuelve true si la carga fue exitosa, false si hubo alg�n error.
    bool LoadModel(const std::string& filePath);

    // Obtiene los v�rtices procesados del modelo cargado.
    const std::vector<SimpleVertex>& GetVertices() const { return vertices; }

    // Obtiene los �ndices de los v�rtices procesados del modelo cargado.
    const std::vector<uint32_t>& GetIndices() const { return indices; }

    // Obtiene los nombres de archivos de texturas asociados con el modelo.
    std::vector<std::string> GetTextureFileNames() const { return textureFileNames; }

    // Procesa un nodo en la escena FBX, generalmente llamado recursivamente para procesar todos los subnodos.
    void ProcessNode(FbxNode* node);

    // Procesa un mesh dentro de un nodo FBX. Extrae v�rtices, �ndices y otros datos relevantes.
    void ProcessMesh(FbxNode* node);

    // Procesa los materiales asociados con el mesh y extrae la informaci�n necesaria (texturas, propiedades, etc.).
    void ProcessMaterials(FbxSurfaceMaterial* material);

private:
    // Puntero al manager del SDK de FBX, necesario para manejar la memoria y otros recursos de FBX.
    FbxManager* lSdkManager;

    // Puntero a la escena FBX que contiene todos los datos del modelo cargado.
    FbxScene* lScene;

    // V�rtices del modelo despu�s de haber sido procesados desde el archivo FBX.
    std::vector<SimpleVertex> vertices;

    // �ndices para los v�rtices, usados para definir las caras del mesh.
    std::vector<unsigned int> indices;

    // Nombres de los archivos de texturas asociados con el modelo.
    std::vector<std::string> textureFileNames;

public:
    // Almacena los diferentes componentes de mesh procesados del modelo cargado.
    std::vector<MeshComponent> meshes;
};