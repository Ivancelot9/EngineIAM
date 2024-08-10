#pragma once
#include "PreRequesites.h"

class Window
{
public:
    // Constructor por defecto
    Window() = default;

    // Destructor por defecto
    ~Window() = default;

    // Inicializa la ventana con la instancia de la aplicación, parámetros de visualización y procedimiento de ventana
    HRESULT 
    init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);

    // Actualiza el estado de la ventana (actualmente vacío)
    void 
    update();

    // Realiza operaciones de renderizado en la ventana (actualmente vacío)
    void 
    render();

    // Destruye la ventana y libera los recursos asociados
    void 
    destroy();

public:
    // Manejador de la ventana, identifica la ventana en el sistema
    HWND m_hWnd = nullptr;

    // Ancho de la ventana
    unsigned int m_width;

    // Alto de la ventana
    unsigned int m_height;

private:
    // Instancia de la aplicación
    HINSTANCE m_hInst = nullptr;

    // Estructura que define el tamaño y posición de la ventana
    RECT m_rect;

    // Nombre de la ventana que aparece en la barra de título
    std::string m_windowName = "Engine IAM";
};
