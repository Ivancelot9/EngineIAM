#include "RenderTargetView.h"
#include "Device.h"
#include "DeviceContext.h"
#include "DepthStencilView.h"
#include "Texture.h"

void 
RenderTargetView::init(Device device, Texture backBuffer, DXGI_FORMAT Format)
{
    // Verifica si el dispositivo es válido (no nulo)
    if (device.m_device == nullptr)
    {
        ERROR("RenderTargetView", "init", "Check for Device device")
            exit(1); // Termina el programa si el dispositivo es nulo
    }
    // Verifica si el buffer de textura es válido (no nulo)
    else if (backBuffer.m_texture == nullptr)
    {
        ERROR("RenderTargetView", "init", "Check for Texture backBuffer")
            exit(1); // Termina el programa si el buffer de textura es nulo
    }

    HRESULT hr = S_OK; // Variable para almacenar el resultado de las operaciones

    // Configuración de la descripción de la vista del objetivo de renderizado
    D3D11_RENDER_TARGET_VIEW_DESC desc = {};
    desc.Format = Format; // Establece el formato de la vista del objetivo de renderizado
    desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; // Configura la vista como una textura 2D

    // Crea la vista del objetivo de renderizado usando el dispositivo y la descripción
    hr = device.CreateRenderTargetView(backBuffer.m_texture, &desc, &m_renderTargetView);

    // Verifica si la creación de la vista del objetivo de renderizado fue exitosa
    if (FAILED(hr))
    {
        ERROR("RenderTargetView", "init", "Check for CreateRenderTargetView")
            exit(1); // Termina el programa si la creación de la vista falla
    }
}

void
RenderTargetView::update()
{
    // Método vacío para actualizaciones futuras de la vista del objetivo de renderizado
    // Implementar la lógica de actualización si es necesario
}

void
RenderTargetView::render(DeviceContext& deviceContext, DepthStencilView& depthStencilView, unsigned int numViews, float ClearColor[4])
{
    // Limpia la vista del objetivo de renderizado con el color especificado
    deviceContext.m_deviceContext->ClearRenderTargetView(m_renderTargetView, ClearColor);

    // Establece la vista del objetivo de renderizado y la vista de profundidad/estencil para el contexto de dispositivo
    deviceContext.m_deviceContext->OMSetRenderTargets(numViews,
        &m_renderTargetView, depthStencilView.m_depthStencilView);
}

void
RenderTargetView::destroy()
{
    // Libera los recursos asociados con la vista del objetivo de renderizado
    SAFE_RELEASE(m_renderTargetView);
}
