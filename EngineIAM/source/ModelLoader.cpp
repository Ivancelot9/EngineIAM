#include "ModelLoader.h"

ModelLoader::ModelLoader() : lSdkManager(nullptr), lScene(nullptr)
{
    // Inicialización del SDK manager de FBX
    lSdkManager = FbxManager::Create();
    if (!lSdkManager)
    {
        ERROR("ModelLoader", "FbxManager::()", "Unable to create FBX Manager!");
    }
    else
    {
        MESSAGE("ModelLoader", "ModelLoader", "Autodesk FBX SDK version " << lSdkManager->GetVersion());
    }

    // Crear los IOSettings para manejar la configuración de importación/exportación
    FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
    lSdkManager->SetIOSettings(ios);

    // Crear una nueva escena FBX
    lScene = FbxScene::Create(lSdkManager, "myScene");
}

ModelLoader::~ModelLoader()
{
    // Liberar el SDK manager y sus recursos
    if (lSdkManager)
        lSdkManager->Destroy();
}

bool ModelLoader::LoadModel(const std::string& filePath)
{
    // Crear un importador para cargar el archivo FBX
    FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

    // Inicializar el importador con el archivo especificado y la configuración del SDK manager
    if (!lImporter->Initialize(filePath.c_str(), -1, lSdkManager->GetIOSettings()))
    {
        MESSAGE("ModelLoader", "LoadModel", "Unable to initialize FBX importer for file: " << filePath.c_str())
            ERROR("ModelLoader", "LoadModel", "Error returned: " << lImporter->GetStatus().GetErrorString());
        return false;
    }

    // Importar la escena FBX
    if (!lImporter->Import(lScene))
    {
        ERROR("ModelLoader", "lImporter->Import", "Unable to import the FBX Scene from file: " << filePath.c_str());
        lImporter->Destroy();
        return false;
    }

    // Liberar la memoria del importador
    lImporter->Destroy();

    MESSAGE("ModelLoader", "LoadModel", "Successfully imported the FBX scene from file: " << filePath.c_str());

    // Procesar la escena FBX para extraer la geometría y los materiales
    FbxNode* rootNode = lScene->GetRootNode();
    if (rootNode)
    {
        // Recorrer todos los nodos hijos del nodo raíz y procesarlos
        for (int i = 0; i < rootNode->GetChildCount(); i++)
        {
            ProcessNode(rootNode->GetChild(i));
        }
    }

    // Obtener y procesar los materiales de la escena
    int materialCount = lScene->GetMaterialCount();
    for (int i = 0; i < materialCount; ++i)
    {
        FbxSurfaceMaterial* material = lScene->GetMaterial(i);
        ProcessMaterials(material);
    }

    return true;
}

void ModelLoader::ProcessNode(FbxNode* node)
{
    // Verificar si el nodo tiene un atributo asociado
    if (node->GetNodeAttribute())
    {
        // Verificar si el atributo es de tipo malla (mesh)
        if (node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
        {
            // Procesar la malla contenida en el nodo
            ProcessMesh(node);
        }
    }

    // Recorrer recursivamente los nodos hijos
    for (int i = 0; i < node->GetChildCount(); i++)
    {
        ProcessNode(node->GetChild(i));
    }
}

void ModelLoader::ProcessMesh(FbxNode* node)
{
    // Obtener la malla del nodo
    FbxMesh* mesh = node->GetMesh();
    if (!mesh) return; // Salir si el nodo no contiene una malla

    std::vector<SimpleVertex> vertices;
    std::vector<UINT> indices;

    // Procesar los vértices de la malla
    for (int i = 0; i < mesh->GetControlPointsCount(); i++) {
        FbxVector4* controlPoint = mesh->GetControlPoints();
        SimpleVertex vertex;
        vertex.Pos = XMFLOAT3((float)controlPoint[i][0],
            (float)controlPoint[i][1],
            (float)controlPoint[i][2]);
        vertices.push_back(vertex);
    }

    // Procesar las coordenadas de textura (UVs)
    if (mesh->GetElementUVCount() > 0) {
        FbxGeometryElementUV* uvElement = mesh->GetElementUV(0);
        FbxGeometryElement::EMappingMode mappingMode = uvElement->GetMappingMode();
        FbxGeometryElement::EReferenceMode referenceMode = uvElement->GetReferenceMode();
        int polyIndexCounter = 0;

        for (int polyIndex = 0; polyIndex < mesh->GetPolygonCount(); polyIndex++) {
            int polySize = mesh->GetPolygonSize(polyIndex);
            for (int vertIndex = 0; vertIndex < polySize; vertIndex++) {
                int controlPointIndex = mesh->GetPolygonVertex(polyIndex, vertIndex);

                int uvIndex = -1;
                if (mappingMode == FbxGeometryElement::eByControlPoint) {
                    if (referenceMode == FbxGeometryElement::eDirect) {
                        uvIndex = controlPointIndex;
                    }
                    else if (referenceMode == FbxGeometryElement::eIndexToDirect) {
                        uvIndex = uvElement->GetIndexArray().GetAt(controlPointIndex);
                    }
                }
                else if (mappingMode == FbxGeometryElement::eByPolygonVertex) {
                    if (referenceMode == FbxGeometryElement::eDirect || referenceMode == FbxGeometryElement::eIndexToDirect) {
                        uvIndex = uvElement->GetIndexArray().GetAt(polyIndexCounter);
                        polyIndexCounter++;
                    }
                }

                if (uvIndex != -1) {
                    FbxVector2 uv = uvElement->GetDirectArray().GetAt(uvIndex);
                    vertices[controlPointIndex].Tex = XMFLOAT2((float)uv[0], -(float)uv[1]);
                }
            }
        }
    }

    // Procesar los índices de la malla
    for (int i = 0; i < mesh->GetPolygonCount(); i++) {
        for (int j = 0; j < mesh->GetPolygonSize(i); j++) {
            indices.push_back(mesh->GetPolygonVertex(i, j));
        }
    }

    // Crear una estructura de malla y almacenarla en el vector de mallas
    Mesh meshData;
    meshData.vertex = vertices;
    meshData.index = indices;
    meshData.name = node->GetName();
    meshData.numVertex = vertices.size();
    meshData.numIndex = indices.size();

    meshes.push_back(meshData);
}

void ModelLoader::ProcessMaterials(FbxSurfaceMaterial* material)
{
    // Procesar el material para obtener las texturas asociadas
    if (material)
    {
        FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
        if (prop.IsValid())
        {
            int textureCount = prop.GetSrcObjectCount<FbxTexture>();
            for (int i = 0; i < textureCount; ++i)
            {
                FbxTexture* texture = FbxCast<FbxTexture>(prop.GetSrcObject<FbxTexture>(i));
                if (texture)
                {
                    textureFileNames.push_back(texture->GetName());
                }
            }
        }
    }
}