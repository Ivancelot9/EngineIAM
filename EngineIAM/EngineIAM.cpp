
#include "BaseApp.h"

// Crear una instancia global de BaseApp
BaseApp app;

// Declaración externa de la función que maneja mensajes de ventana para ImGui
extern 
IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
                                                      UINT msg,
                                                      WPARAM wParam,
                                                      LPARAM lParam);

// Función de ventana que procesa mensajes del sistema y de la aplicación
LRESULT 
CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    // Verificar si ImGui puede manejar el mensaje
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    PAINTSTRUCT ps;
    HDC hdc;

    // Manejar diferentes mensajes de la ventana
    switch (message) {
    case WM_PAINT:
        // Comenzar la pintura en la ventana
        hdc = BeginPaint(hWnd, &ps);
        // Finalizar la pintura en la ventana
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        // Enviar un mensaje de salida cuando la ventana se destruye
        PostQuitMessage(0);
        break;

    default:
        // Procesar mensajes predeterminados
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

// Declaración de la función de ventana WndProc (duplicada aquí por error y debería eliminarse)
LRESULT 
CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Función principal de Windows que inicia la aplicación
int
WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    // Ejecutar la aplicación
    return app.run(hInstance, hPrevInstance, lpCmdLine, nCmdShow, WndProc);
}


