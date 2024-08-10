#pragma once
#include "PreRequesites.h"

class Window
{
public:
    // Constructor por defecto
    Window() = default;

    // Destructor por defecto
    ~Window() = default;

    // Inicializa la ventana con la instancia de la aplicaci�n, par�metros de visualizaci�n y procedimiento de ventana
    HRESULT 
    init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);

    // Actualiza el estado de la ventana (actualmente vac�o)
    void 
    update();

    // Realiza operaciones de renderizado en la ventana (actualmente vac�o)
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
    // Instancia de la aplicaci�n
    HINSTANCE m_hInst = nullptr;

    // Estructura que define el tama�o y posici�n de la ventana
    RECT m_rect;

    // Nombre de la ventana que aparece en la barra de t�tulo
    std::string m_windowName = "Engine IAM";
};
