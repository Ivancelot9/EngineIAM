#pragma once
#include "PreRequesites.h"

//Declaraciones directas - Forward Declarations
class Device;
class DeviceContext;
class Window;
class Texture;

class SwapChain
{
public:
    // Constructor por defecto
    SwapChain() = default;

    // Destructor por defecto
    ~SwapChain() = default;

    // M�todo para inicializar el SwapChain
    // Inicializa el SwapChain utilizando el dispositivo, el contexto del dispositivo, el back buffer y la ventana
    void 
    init(Device& device, DeviceContext& deviceContext, Texture& backBuffer,
         Window  window);

    // M�todo para actualizar el estado del SwapChain (actualmente no implementado)
    void 
    update();

    // M�todo para realizar el renderizado (actualmente no implementado)
    void 
    render();

    // M�todo para destruir el SwapChain y liberar los recursos asociados
    void 
    destroy();

    // M�todo para presentar el SwapChain en la pantalla
    void 
    present();

public:
    // Puntero al SwapChain de Direct3D
    IDXGISwapChain* m_SwapChain = nullptr;

    // Tipo de driver de Direct3D
    D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;

private:
    // Nivel de caracter�sticas de Direct3D (por defecto es 11.0)
    D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;

};

