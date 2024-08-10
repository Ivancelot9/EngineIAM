#pragma once
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
#include "UserInterface.h" //Archivo de cabeza
#include "Actor.h"

class BaseApp{

public:
	BaseApp() = default;
	~BaseApp() = default;

	HRESULT 
	init();

	void 
	update();

	void 
	render();

	void 
	destroy();

	int 
	run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow,
		WNDPROC wndproc);

	void 
	CreateGrid(int width, int depth, float spacing);
private:

	Window                              m_window;                    // Ventana
	Device                              m_device;                    // Dispositivo
	DeviceContext                       m_deviceContext;             // Contexto del dispositivo
	SwapChain                           m_swapchain;                 // Cadena de intercambio
	Texture                             m_backBuffer;                // Textura de buffer trasero
	Texture                             m_depthStencil;              // Textura de stencil de profundidad
	DepthStencilView                    m_depthStencilView;          // Vista de stencil de profundidad
	RenderTargetView                    m_renderTargetView;          // Vista de destino de renderizado
	Viewport                            m_viewport;                  // Viewport
	ShaderProgram                       m_ShaderProgram;             // Programa de shaders

	std::vector<Buffer>                 m_vertexBuffers;             // Vectores de buffers de vértices
	std::vector<Buffer>                 m_indexBuffers;              // Vectores de buffers de índices

	Buffer                              m_CBBufferNeverChanges;      // Buffer constante que nunca cambia
	Buffer                              m_CBBufferChangeOnResize;    // Buffer constante que cambia al redimensionar
	Buffer                              m_CBBufferChangesEveryFrame; // Buffer constante que cambia cada cuadro

	std::vector<Texture>                modelTextures;               // Texturas del modelo
	UserInterface                       m_UserInterface;
	SamplerState                        m_sampler;                   // Estado del sampler
	ModelLoader                         m_model;                     // Cargador de modelos
	Texture                             m_default;                   // Textura predeterminada
	XMMATRIX                            m_View;                      // Matriz de vista
	XMMATRIX                            m_Projection;                // Matriz de proyección
	XMFLOAT4                            m_vMeshColor;              // Color del modelo
	CBNeverChanges                      cbNeverChanges;              // Estructura de constantes que nunca cambian
	CBChangeOnResize                    cbChangesOnResize;           // Estructura de constantes que cambian al redimensionar
	CBChangesEveryFrame                 cb;                          // Estructura de constantes que cambian cada cuadro


	//Vela Actor
	EngineUtilities::TSharedPointer<Actor> AVela;
	//Grid Actor
	MeshComponent                          MC;
	EngineUtilities::TSharedPointer<Actor> AGrid;
	std::vector<Texture>                   gridTexs;

};
