#pragma once
#include "PreRequesites.h"
class Window;
class DeviceContext;

class Viewport {
public:
    // Constructor por defecto
    Viewport() = default;

    // Destructor por defecto
    ~Viewport() = default;

    // Inicializa el viewport utilizando las dimensiones de la ventana
    void 
    init(Window window);

    // Actualiza el estado del viewport (actualmente vac�o)
    void 
    update();

    // Configura el viewport en el contexto del dispositivo para el renderizado
    void 
    render(DeviceContext& deviceContext);

    // Libera cualquier recurso asociado con el viewport (actualmente vac�o)
    void 
    destroy();

public:
    // Estructura de Direct3D que define las dimensiones y par�metros del viewport
    D3D11_VIEWPORT m_viewport;
};
