//--------------------------------------------------------------------------------------
// File: EngineIAM.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "PreRequesites.h"  // Archivo de encabezado que contiene pre-requisitos
#include "Window.h"         // Archivo de encabezado para la ventana
#include "Device.h"         // Archivo de encabezado para el dispositivo
#include "DeviceContext.h"  // Archivo de encabezado para el contexto del dispositivo
#include "SwapChain.h"      // Archivo de encabezado para la cadena de intercambio
#include "Texture.h"        // Archivo de encabezado para las texturas
#include "DepthStencilView.h" // Archivo de encabezado para la vista de stencil de profundidad
#include "RenderTargetView.h" // Archivo de encabezado para la vista de destino de renderizado
#include "Viewport.h"       // Archivo de encabezado para el viewport
#include "ShaderProgram.h"  // Archivo de encabezado para el programa de shaders
#include "Buffer.h"         // Archivo de encabezado para el buffer
#include "SamplerState.h"   // Archivo de encabezado para el estado del sampler
#include "ModelLoader.h"    // Archivo de encabezado para cargar modelos
//#include "fbxsdk.h"         // Archivo de encabezado para el SDK de FBX
#include "UserInterface.h" //Archivo de cabeza
#include "Actor.h"
//#include <Transform.h>

//--------------------------------------------------------------------------------------
// Variables globales
//--------------------------------------------------------------------------------------
Window                              g_window;                    // Ventana
Device                              g_device;                    // Dispositivo
DeviceContext                       g_deviceContext;             // Contexto del dispositivo
SwapChain                           g_swapchain;                 // Cadena de intercambio
Texture                             g_backBuffer;                // Textura de buffer trasero
Texture                             g_depthStencil;              // Textura de stencil de profundidad
DepthStencilView                    g_depthStencilView;          // Vista de stencil de profundidad
RenderTargetView                    g_renderTargetView;          // Vista de destino de renderizado
Viewport                            g_viewport;                  // Viewport
ShaderProgram                       g_ShaderProgram;             // Programa de shaders

std::vector<Buffer>                 g_vertexBuffers;             // Vectores de buffers de vértices
std::vector<Buffer>                 g_indexBuffers;              // Vectores de buffers de índices

Buffer                              g_CBBufferNeverChanges;      // Buffer constante que nunca cambia
Buffer                              g_CBBufferChangeOnResize;    // Buffer constante que cambia al redimensionar
Buffer                              g_CBBufferChangesEveryFrame; // Buffer constante que cambia cada cuadro

std::vector<Texture>                modelTextures;               // Texturas del modelo
UserInterface                       g_UserInterface;
SamplerState                        g_sampler;                   // Estado del sampler
ModelLoader                         g_model;                     // Cargador de modelos
Texture                             g_default;                   // Textura predeterminada
XMMATRIX                            g_View;                      // Matriz de vista
XMMATRIX                            g_Projection;                // Matriz de proyección
XMFLOAT4                            g_vMeshColor(0.7f, 0.7f, 0.7f, 1.0f); // Color del modelo
//MeshComponent                       MC;
//Mesh                                g_mesh;                      // Malla del modelo
CBNeverChanges                      cbNeverChanges;              // Estructura de constantes que nunca cambian
CBChangeOnResize                    cbChangesOnResize;           // Estructura de constantes que cambian al redimensionar
CBChangesEveryFrame                 cb;                          // Estructura de constantes que cambian cada cuadro


//EngineUtilities::TSharedPointer<Actor> grid;
EngineUtilities::TSharedPointer<Actor> AVela;
//std::vector<Texture> gridTexs;

//EngineUtilities
//---------------
// -----------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
void Render();
void Update(double DeltaTime);

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


    //// Create vertex buffer
    //for (auto& mesh : g_model.meshes)
    //{
    //    Buffer vertexBuffer;
    //    vertexBuffer.init(g_device, mesh, D3D11_BIND_VERTEX_BUFFER);
    //    g_vertexBuffers.push_back(vertexBuffer);
    //   
    //   // // Create index buffer
    //    Buffer indexBuffer;
    //    indexBuffer.init(g_device, mesh, D3D11_BIND_INDEX_BUFFER);
    //    g_indexBuffers.push_back(indexBuffer);
    //}
  

    // Inicialización de Constant Buffers
    g_CBBufferNeverChanges.init(g_device, sizeof(CBNeverChanges));

    g_CBBufferChangeOnResize.init(g_device, sizeof(CBChangeOnResize));

    /*g_CBBufferChangesEveryFrame.init(g_device, sizeof(CBChangesEveryFrame));*/

    ////Create SamplerState
    //g_sampler.init(g_device);

    //// Initialize the world matrices
    //g_World = XMMatrixIdentity();

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

    g_default.init(g_device, "Textures/Default.png", ExtensionType::PNG);

    // Initialize the view matrix
    XMVECTOR Eye = XMVectorSet( 0.0f, 3.0f, -6.0f, 0.0f );
    XMVECTOR At = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    XMVECTOR Up = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    g_View = XMMatrixLookAtLH( Eye, At, Up );

    cbNeverChanges.mView = XMMatrixTranspose( g_View );
  

    // Initialize the projection matrix
    g_Projection = XMMatrixPerspectiveFovLH( XM_PIDIV4, g_window.m_width / (FLOAT)g_window.m_height, 0.01f, 100.0f );
    
    cbChangesOnResize.mProjection = XMMatrixTranspose( g_Projection );

    // Set Vela Actor
    AVela = EngineUtilities::MakeShared<Actor>(g_device);

    if (!AVela.isNull()) {
        MESSAGE("Actor", "Actor", "Actor accessed successfully.")

        AVela->getComponent<Transform>()->setPosition(EngineUtilities::Vector3(-0.9f, -2.0f, 2.0f));
        AVela->getComponent<Transform>()->setRotation(EngineUtilities::Vector3(XM_PI / -2.0f, 0.0f, XM_PI / 2.0f));
        AVela->getComponent<Transform>()->setScale(EngineUtilities::Vector3(.03f, .03f, .03f));
        AVela->setMesh(g_device, g_model.meshes);
        AVela->setTextures(modelTextures);
    }
    else {
        MESSAGE("Actor", "Actor", "Actor resource not found.")
    }

   /* grid = EngineUtilities::MakeShared<Actor>(g_device);
    if (!grid.isNull()) {
        MESSAGE("Actor", "Actor", "Actor accessed successfully.")
            std::vector<MeshComponent> gridMesh;
        gridMesh.push_back(MC);
        grid->setMesh(g_device, gridMesh);
        gridTexs.push_back(g_default);
        grid->setTextures(gridTexs);
        grid->getComponent<Transform>()->setPosition(EngineUtilities::Vector3(0.0f, -2.0f, 0.0f));
        grid->getComponent<Transform>()->setScale(EngineUtilities::Vector3(.03f, .03f, .03f));
    }
    else {
        MESSAGE("Actor", "Actor", "Actor resource not found.")
    }*/
    g_UserInterface.init(g_window.m_hWnd, g_device.m_device, g_deviceContext.m_deviceContext);
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
    if (g_deviceContext.m_deviceContext) g_deviceContext.m_deviceContext->ClearState();

    AVela->destroy();
    //grid->destroy();

    //g_default.destroy();
    g_CBBufferNeverChanges.destroy();
    g_CBBufferChangeOnResize.destroy();

    g_ShaderProgram.destroy();
    g_depthStencil.destroy();
    g_depthStencilView.destroy();
    g_renderTargetView.destroy();
    g_swapchain.destroy();
    g_deviceContext.destroy();
    // Release UI
    g_UserInterface.destroy();

    g_device.destroy();

}

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;
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
void Update(double DeltaTime)
{
    g_UserInterface.update();
    bool show_demo_window = true;

   ImGui::ShowDemoWindow(&show_demo_window);
    //ImGui::Begin("Test");

   /*ImGui::End();*/
   // Update constant Buffers
   g_CBBufferNeverChanges.update(g_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
   g_CBBufferChangeOnResize.update(g_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

   // Actualizar info logica del mesh
   AVela->getComponent<Transform>()->ui_noWindow("Transform");
   AVela->update(0, g_deviceContext);
   //grid->update(0, g_deviceContext);
   //EngineUtilities::Vector3 translation(0.0f, 0.0f, DeltaTime);
   //AVela->getComponent<Transform>()->translate(translation);
   //AVela->getComponent<Transform>()->setRotation(Vector3f(XM_PI / -2.0f, DeltaTime, XM_PI / 2.0f));
}
//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
    // Clear the back buffer
    float ClearColor[4] = { 0.85f, 0.85f, 0.85f, 1.0f }; // red, green, blue, alpha
    g_renderTargetView.render(g_deviceContext, g_depthStencilView, 1, ClearColor);

    // Set Viewport
    g_viewport.render(g_deviceContext);
    // Clear the depth buffer to 1.0 (max depth)
    g_depthStencilView.render(g_deviceContext);

    // Render the cube
    g_ShaderProgram.render(g_deviceContext);

    // Render the models
    AVela->render(g_deviceContext);
    //grid->render(g_deviceContext);

    //for (size_t i = 0; i < 7; i++) {
    //	//g_vertexBuffers[i].render(g_deviceContext, 0, 1);
        //g_indexBuffers[i].render(g_deviceContext, DXGI_FORMAT_R32_UINT);
        //if (i <= modelTextures.size() - 1)
        //{
        //	modelTextures[i].render(g_deviceContext, 0, 1);
        //}
        //else {
        //	g_default.render(g_deviceContext, 0, 1);
        //}
        //g_default.render(g_deviceContext, 0, 1);
        //g_sampler.render(g_deviceContext, 0, 1);
    //
    //
    //	//g_deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    //	//g_deviceContext.m_deviceContext->DrawIndexed(g_model.meshes[i].m_numIndex, 0, 0);
    //}

    // Actualizar constant buffers
    g_CBBufferNeverChanges.render(g_deviceContext, 0, 1);
    g_CBBufferChangeOnResize.render(g_deviceContext, 1, 1);

    g_UserInterface.render();

    g_swapchain.present();
}
