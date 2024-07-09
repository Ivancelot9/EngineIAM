//--------------------------------------------------------------------------------------
// File: EngineIAM.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "PreRequesites.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "Texture.h"
#include "DepthStencilView.h"
#include "RenderTargetView.h"
#include "Viewport.h"
#include "ShaderProgram.h"
#include "Buffer.h"
#include "SamplerState.h"
#include "ModelLoader.h"
#include "fbxsdk.h"

//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
Window                              g_window;
Device                              g_device;
DeviceContext                       g_deviceContext;
SwapChain                           g_swapchain;
Texture                             g_backBuffer;
Texture                             g_depthStencil;
DepthStencilView                    g_depthStencilView;
RenderTargetView                    g_renderTargetView;
Viewport                            g_viewport;
ShaderProgram                       g_ShaderProgram;

std::vector<Buffer>                 g_vertexBuffers;
std::vector<Buffer>                 g_indexBuffers;

Buffer                              g_CBBufferNeverChanges;
Buffer                              g_CBBufferChangeOnResize;
Buffer                              g_CBBufferChangesEveryFrame;

std::vector<Texture>                modelTextures;

SamplerState                        g_sampler;
ModelLoader                         g_model;
Texture                             g_default;


XMMATRIX                            g_World;
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor( 0.7f, 0.7f, 0.7f, 1.0f );

Mesh                                g_mesh;
CBNeverChanges                      cbNeverChanges;
CBChangeOnResize                    cbChangesOnResize;
CBChangesEveryFrame                 cb;
//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
void Render();
void Update(float DeltaTime);

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

    if( FAILED( g_window.init( hInstance, nCmdShow, WndProc ) ) )
        return 0;

    if( FAILED( InitDevice() ) )
    {
        CleanupDevice();
        return 0;
    }

    // Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            // Update our time
            static float t = 0.0f;
            if (g_swapchain.m_driverType == D3D_DRIVER_TYPE_REFERENCE)
            {
                t += (float)XM_PI * 0.0125f;
            }
            else
            {
                static DWORD dwTimeStart = 0;
                DWORD dwTimeCur = GetTickCount();
                if (dwTimeStart == 0)
                    dwTimeStart = dwTimeCur;
                t = (dwTimeCur - dwTimeStart) / 1000.0f;
            }

            Update(t);
            Render();
        }
    }

    CleanupDevice();

    return ( int )msg.wParam;
}



//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
    HRESULT hr = S_OK;

    //Create SwapChain
    g_swapchain.init(g_device, g_deviceContext, g_backBuffer, g_window);
    // Create a render target view
    g_renderTargetView.init(g_device, g_backBuffer, DXGI_FORMAT_R8G8B8A8_UNORM);
    // Create depth stencil texture
    g_depthStencil.init(g_device, g_window.m_width,
        g_window.m_height,
        DXGI_FORMAT_D24_UNORM_S8_UINT,
        D3D11_BIND_DEPTH_STENCIL);
   //Create the depth stencil view
    g_depthStencilView.init(g_device, g_depthStencil, DXGI_FORMAT_D24_UNORM_S8_UINT);
    // Setup the viewport
    g_viewport.init(g_window);
  

    // Define the input layout
    std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;

    D3D11_INPUT_ELEMENT_DESC position;
    position.SemanticName = "POSITION";
    position.SemanticIndex = 0;
    position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    position.InputSlot = 0;
    position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
    position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    position.InstanceDataStepRate = 0;
    Layout.push_back(position);

    D3D11_INPUT_ELEMENT_DESC texcoord;
    texcoord.SemanticName = "TEXCOORD";
    texcoord.SemanticIndex = 0;
    texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;
    texcoord.InputSlot = 0;
    texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
    texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    texcoord.InstanceDataStepRate = 0;
    Layout.push_back(texcoord);

    g_ShaderProgram.init(g_device, "EngineIAM.fx", Layout);

    g_model.LoadModel("Models/Vela2.fbx");


    // Create vertex buffer
    for (auto& mesh : g_model.meshes)
    {
        Buffer vertexBuffer;
        vertexBuffer.init(g_device, mesh, D3D11_BIND_VERTEX_BUFFER);
        g_vertexBuffers.push_back(vertexBuffer);
        /*g_mesh.name = "HollowKnight";
        g_mesh.vertex = g_model.GetVertices();*/

        /*for (const SimpleVertex& vertex : vertices)
        {
            g_mesh.vertex.push_back(vertex);
        }*/

        //// NOTA: El static_cast<unsigned int›
        //se está utilizando aquí para convertir el resultado del método size() 
        //    de un std::vector a un tipo unsigned int.
        //    El método size() devuelve un valor del tipo std::size_t, 
        //    que es un tipo específico de tamaño no negativo.En algunas 
        //    plataformas, std : size_t puede ser de un tamaño diferente a unsigned int. /

       //g_mesh.numVertex  = static_cast<unsigned int>(g_mesh.vertex.size());
       // // Create vertex buffer
       // g_vertexBuffer.init(g_device, g_mesh, D3D11_BIND_VERTEX_BUFFER);

       // // Create index buffer
        Buffer indexBuffer;
        indexBuffer.init(g_device, mesh, D3D11_BIND_INDEX_BUFFER);
        g_indexBuffers.push_back(indexBuffer);
    }
   // g_mesh.index = g_model.GetIndices();
   // g_mesh.numIndex = static_cast<unsigned int>(g_mesh.index.size());
   //

   // g_indexBuffer.init(g_device, g_mesh, D3D11_BIND_INDEX_BUFFER);

    // Inicialización de Constant Buffers
    g_CBBufferNeverChanges.init(g_device, sizeof(CBNeverChanges));

    g_CBBufferChangeOnResize.init(g_device, sizeof(CBChangeOnResize));

    g_CBBufferChangesEveryFrame.init(g_device, sizeof(CBChangesEveryFrame));


    //g_default.init(g_device, "Textures/Default.png", ExtensionType::PNG);
    //// Load the Texture
    //g_modelTexture.init(g_device, "seafloor.dds");
    //Create SamplerState
    g_sampler.init(g_device);

    // Initialize the world matrices
    g_World = XMMatrixIdentity();

    Texture Vela_Char_BaseColor;
    Vela_Char_BaseColor.init(g_device, "Textures/Vela/Vela_Char_BaseColor.png", ExtensionType::PNG);

    Texture Vela_Corneas_BaseColor;
    Vela_Corneas_BaseColor.init(g_device, "Textures/Vela/Vela_Corneas_BaseColor.png", ExtensionType::PNG);

    Texture Vela_Gun_BaseColor;
    Vela_Gun_BaseColor.init(g_device, "Textures/Vela/Vela_Gun_BaseColor.png", ExtensionType::PNG);

    Texture Vela_Legs_BaseColor;
    Vela_Legs_BaseColor.init(g_device, "Textures/Vela/Vela_Legs_BaseColor.png", ExtensionType::PNG);

    Texture Vela_Mechanical_BaseColor;
    Vela_Mechanical_BaseColor.init(g_device, "Textures/Vela/Vela_Mechanical_BaseColor.png", ExtensionType::PNG);

    Texture Vela_Plate_BaseColor;
    Vela_Plate_BaseColor.init(g_device, "Textures/Vela/Vela_Plate_BaseColor.png", ExtensionType::PNG);

    Texture Vela_Visor_BaseColor;
    Vela_Visor_BaseColor.init(g_device, "Textures/Vela/Vela_Visor_BaseColor.png", ExtensionType::PNG);

    modelTextures.push_back(Vela_Corneas_BaseColor);
    modelTextures.push_back(Vela_Gun_BaseColor);
    modelTextures.push_back(Vela_Visor_BaseColor);
    modelTextures.push_back(Vela_Legs_BaseColor);
    modelTextures.push_back(Vela_Mechanical_BaseColor);
    modelTextures.push_back(Vela_Char_BaseColor);
    modelTextures.push_back(Vela_Plate_BaseColor);

    // Initialize the view matrix
    XMVECTOR Eye = XMVectorSet( 0.0f, 3.0f, -6.0f, 0.0f );
    XMVECTOR At = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    XMVECTOR Up = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    g_View = XMMatrixLookAtLH( Eye, At, Up );

    cbNeverChanges.mView = XMMatrixTranspose( g_View );
  

    // Initialize the projection matrix
    g_Projection = XMMatrixPerspectiveFovLH( XM_PIDIV4, g_window.m_width / (FLOAT)g_window.m_height, 0.01f, 100.0f );
    
    cbChangesOnResize.mProjection = XMMatrixTranspose( g_Projection );

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
    if (g_deviceContext.m_deviceContext) g_deviceContext.m_deviceContext->ClearState();
    
    g_sampler.destroy();
    for (auto& tex : modelTextures)
    {
        tex.destroy();
    }
    g_default.destroy();
    g_CBBufferNeverChanges.destroy();
    g_CBBufferChangeOnResize.destroy();
    g_CBBufferChangesEveryFrame.destroy();
  
    for (auto& vertexBuffer : g_vertexBuffers)
    {
        vertexBuffer.destroy();
    }
    for (auto& indexBuffer : g_indexBuffers)
    {
        indexBuffer.destroy();
    }

    g_ShaderProgram.destroy();

    g_depthStencil.destroy();
    g_depthStencilView.destroy();

    g_renderTargetView.destroy();

    g_swapchain.destroy();
    g_deviceContext.destroy();
    g_device.destroy();

}

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message )
    {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}

//Update everyframe
void Update(float DeltaTime)
{

    // Rotate cube around the origin
    XMVECTOR translation = XMVectorSet(0.0f, -2.0f, 0.0f, 0.0f); // Traslación en x=1, y=2, z=3
    XMVECTOR rotation = XMQuaternionRotationRollPitchYaw(XMConvertToRadians(260), XMConvertToRadians(DeltaTime * 50), 0.0f); // Rotación en X=180, Y=180, Z=0
    XMVECTOR scale = XMVectorSet(.03f, .03f, .03f, 0.0f); // Escala por 2 en x, y, z

    // Combinar las transformaciones en una matriz de mundo
    g_World = XMMatrixScalingFromVector(scale) * XMMatrixRotationQuaternion(rotation) * XMMatrixTranslationFromVector(translation);
    // Rotate cube around the origin

    //g_World = XMMatrixRotationZ(DeltaTime);
    // Modify the color
   /* g_vMeshColor.x = (sinf(DeltaTime * 1.0f) + 1.0f) * 0.5f;
    g_vMeshColor.y = (cosf(DeltaTime * 3.0f) + 1.0f) * 0.5f;
    g_vMeshColor.z = (sinf(DeltaTime * 5.0f) + 1.0f) * 0.5f;*/
    //Update Constant Buffers
    g_CBBufferNeverChanges.update(g_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
    g_CBBufferChangeOnResize.update(g_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

    cb.mWorld = XMMatrixTranspose(g_World);
    cb.vMeshColor = g_vMeshColor;
    g_CBBufferChangesEveryFrame.update(g_deviceContext, 0, nullptr, &cb, 0, 0);
}
//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
    // Clear the back buffer
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
    g_renderTargetView.render(g_deviceContext, g_depthStencilView, 1, ClearColor);

    g_viewport.render(g_deviceContext);
    // Clear the depth buffer to 1.0 (max depth)
    //
    //g_deviceContext.m_deviceContext->ClearDepthStencilView( g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );
    g_depthStencilView.render(g_deviceContext);
    
    // Render the models

    g_ShaderProgram.render(g_deviceContext);
   
    for (size_t i = 0; i < g_model.meshes.size(); i++)
    {
        g_vertexBuffers[i].render(g_deviceContext, 0, 1);
        g_indexBuffers[i].render(g_deviceContext, DXGI_FORMAT_R32_UINT);
        if (i <= modelTextures.size() - 1)
        {
            modelTextures[i].render(g_deviceContext, 0, 1);
        }
        else
        {
            g_default.render(g_deviceContext, 0, 1);
        }

        g_default.render(g_deviceContext, 0, 1);

        g_sampler.render(g_deviceContext, 0, 1);

        g_CBBufferNeverChanges.render(g_deviceContext, 0, 1); // Slot 0
        g_CBBufferChangeOnResize.render(g_deviceContext, 1, 1); // Slot 1
        g_CBBufferChangesEveryFrame.renderModel(g_deviceContext, 2, 1); // Slot 2
        //Set primitve topology
        g_deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        g_deviceContext.m_deviceContext->DrawIndexed(g_model.meshes[i].numIndex, 0, 0);
    }




   
    g_swapchain.present();
}
