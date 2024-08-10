#pragma once
#include "PreRequesites.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include <imgui_internal.h>

class Window;
class SwapChain;
class Texture;

class UserInterface{
public:
    // Constructor por defecto
    UserInterface() = default;

    // Destructor por defecto
    ~UserInterface() = default;

    // Inicializa la interfaz de usuario con una ventana, un dispositivo Direct3D y un contexto de dispositivo
    void
    init(void* window, ID3D11Device* device, ID3D11DeviceContext* deviceContext);

    // Actualiza el estado de la interfaz de usuario
    void 
    update();

    // Renderiza la interfaz de usuario
    void 
    render();

    // Libera los recursos utilizados por la interfaz de usuario
    void 
    destroy();

    // Control deslizante para valores en un rango de tres dimensiones
    void 
    vec3Control(const std::string& label,
                float* values,
                float resetValues = 0.0f,
                float columnWidth = 100.0f);

    // Crea una barra de menú en la interfaz de usuario
    void 
    menuBar(Window window, SwapChain swapChain, Texture& backBuffer);

    // Renderiza una textura en la interfaz de usuario
    void 
    Renderer(Window window, ID3D11ShaderResourceView* renderTexture);

    // Crea un contenedor para el inspector en la interfaz de usuario (comentado)
    // void Inspector(std::vector<Model> & models, int index);

    // Crea un contenedor para el inspector en la interfaz de usuario
    void 
    inspectorContainer();

    // Crea un área de salida para mensajes o información en la interfaz de usuario
    void 
    output();

    // Aplica un estilo oscuro a la interfaz de usuario
    void     
    darkStyle();

    // Aplica un estilo gris a la interfaz de usuario
    void 
    greyStyle();

    // Aplica un estilo de creador de juegos a la interfaz de usuario
    void 
    GameMakerStyle();

    // Aplica un estilo de Visual Studio a la interfaz de usuario
    void 
    visualStudioStyle();

    // Crea una herramienta de información emergente (tooltip) con un icono y un texto
    void 
    ToolTip(std::string icon, std::string tip);

    // Crea una herramienta de información emergente (tooltip) con solo texto
    void 
    ToolTip(std::string tip);

    // Crea y gestiona datos para las herramientas de información emergente
    void 
    toolTipData();

    // Crea una barra de herramientas en la interfaz de usuario
    void 
    ToolBar();

    // Cierra la aplicación desde la interfaz de usuario
    void 
    closeApp();

    // Renderiza una ventana transparente a pantalla completa
    void 
    RenderFullScreenTransparentWindow();

private:
    // Variables de estado para los valores de los checkboxes
    bool checkboxValue = true;
    bool checkboxValue2 = false;

    // Nombres de objetos en la interfaz de usuario
    std::vector<const char*> m_objectsNames;

    // Datos de las herramientas de información emergente
    std::vector<const char*> m_tooltips;

    // Variable de estado para mostrar un popup de salida
    bool show_exit_popup = false;
};