#pragma once
//Librerias STD
#include <string>
#include <sstream>
#include <windows.h>
#include <d3d11.h>
#include <vector>


//Librerias DirectX
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>

//Third Parties
#include "resource.h"

// MACRO for safe release of resources
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

#define WARNING( s )                         \
{                                            \
   std::wostringstream os_;                  \
   os_ << s;                                  \
   OutputDebugStringW( os_.str().c_str() );  \
}

#define MESSAGE( classObj, method, state )   \
{                                            \
   std::wostringstream os_;                  \
   os_ << classObj << "::" << method << " : " << "[CREATION OF RESOURCE " << ": " << state << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
}

#define ERROR( classObj, method, errorMSG )  \
{                                            \
   std::wostringstream os_;                  \
   os_ << "ERROR : " << classObj << "::" << method << " : " << "  Error in data from params [" << errorMSG << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
   exit(1);                                  \
}


//Structuras
struct SimpleVertex
{
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;
};

struct CBNeverChanges
{
    XMMATRIX mView;
};

struct CBChangeOnResize
{
    XMMATRIX mProjection;
};

struct CBChangesEveryFrame
{
    XMMATRIX mWorld;
    XMFLOAT4 vMeshColor;
};

enum ShaderType
{
    PIXEL_SHADER = 0,
    VERTEX_SHADER = 1
};
enum ExtensionType
{
    DDS = 0,
    PNG = 1,
    JPG = 2
};

struct Mesh
{
    std::string name;
    std::vector <SimpleVertex> vertex;
    std::vector <unsigned int> index;
    int numVertex;
    int numIndex;
};
