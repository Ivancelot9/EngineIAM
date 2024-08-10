
#include "BaseApp.h"

// Crear una instancia global de BaseApp
BaseApp app;

// Declaraci�n externa de la funci�n que maneja mensajes de ventana para ImGui
extern 
IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
                                                      UINT msg,
                                                      WPARAM wParam,
                                                      LPARAM lParam);

// Funci�n de ventana que procesa mensajes del sistema y de la aplicaci�n
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

// Declaraci�n de la funci�n de ventana WndProc (duplicada aqu� por error y deber�a eliminarse)
LRESULT 
CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Funci�n principal de Windows que inicia la aplicaci�n
int
WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    // Ejecutar la aplicaci�n
    return app.run(hInstance, hPrevInstance, lpCmdLine, nCmdShow, WndProc);
}


