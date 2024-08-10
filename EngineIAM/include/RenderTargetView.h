#pragma once
#include "PreRequesites.h"
class Device;
class Texture;
class DeviceContext;
class DepthStencilView;

// Clase para gestionar la vista del objetivo de renderizado (Render Target View)
class RenderTargetView
{
public:
    // Constructor por defecto
    RenderTargetView() = default;

    // Destructor por defecto
    ~RenderTargetView() = default;

    // Inicializa la vista del objetivo de renderizado con el dispositivo, buffer de respaldo y formato
    void 
    init(Device device, Texture backBuffer, DXGI_FORMAT Format);

    // Actualiza la vista del objetivo de renderizado (implementación específica aquí)
    void 
    update();

    // Renderiza usando el contexto de dispositivo y la vista de profundidad/estencil, con un color de limpieza
    void 
    render(DeviceContext& deviceContext, DepthStencilView& depthStencilView,
           unsigned int numViews, float ClearColor[4]);

    // Libera los recursos asociados con la vista del objetivo de renderizado
    void 
    destroy();

public:
    // Puntero al objeto ID3D11RenderTargetView
    ID3D11RenderTargetView* m_renderTargetView = nullptr;
};
