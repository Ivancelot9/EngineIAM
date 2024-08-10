#include "SwapChain.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Window.h"
#include "Texture.h"

void 
SwapChain::init(Device& device, DeviceContext& deviceContext, Texture& backBuffer,
                Window window)
{
    // Verifica que el puntero de la ventana no sea nulo
    if (window.m_hWnd == nullptr)
    {
        ERROR("SwapChain", "init", "Check for Window window")
            exit(1);
    }

    // Establece los flags para la creación del dispositivo
    unsigned int createDeviceFlags = 0;
#ifdef _DEBUG
    // Habilita el debug en el dispositivo si estamos en modo debug
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    // Define los tipos de driver que se intentarán utilizar
    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,   // Driver de hardware
        D3D_DRIVER_TYPE_WARP,       // Driver de software (para pruebas)
        D3D_DRIVER_TYPE_REFERENCE,  // Driver de referencia (para depuración)
    };
    unsigned int numDriverTypes = ARRAYSIZE(driverTypes);

    // Define los niveles de características (feature levels) soportados
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,  // Direct3D 11.0
        D3D_FEATURE_LEVEL_10_1,  // Direct3D 10.1
        D3D_FEATURE_LEVEL_10_0,  // Direct3D 10.0
    };
    unsigned int numFeatureLevels = ARRAYSIZE(featureLevels);

    // Configura la descripción del swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    memset(&sd, 0, sizeof(sd)); // Inicializa la estructura con ceros
    sd.BufferCount = 1; // Número de buffers en el swap chain
    sd.BufferDesc.Width = window.m_width; // Ancho del buffer
    sd.BufferDesc.Height = window.m_height; // Alto del buffer
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Formato de los colores
    sd.BufferDesc.RefreshRate.Numerator = 60; // Frecuencia de refresco
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Uso del buffer
    sd.OutputWindow = window.m_hWnd; // Ventana de salida
    sd.SampleDesc.Count = 1; // Muestras por píxel
    sd.SampleDesc.Quality = 0; // Calidad de muestreo
    sd.Windowed = TRUE; // Modo ventana (no pantalla completa)

    HRESULT hr = S_OK;
    // Intenta crear el dispositivo y el swap chain con diferentes tipos de drivers
    for (unsigned int driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        m_driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain(nullptr,
            m_driverType,
            nullptr,
            createDeviceFlags,
            featureLevels,
            numFeatureLevels,
            D3D11_SDK_VERSION, &sd,
            &m_SwapChain,
            &device.m_device,
            &m_featureLevel,
            &deviceContext.m_deviceContext);

        // Si la creación fue exitosa, sale del bucle
        if (SUCCEEDED(hr)) {
            break;
        }
    }
    // Si falló la creación, muestra un error y termina el programa
    if (FAILED(hr))
    {
        ERROR("SwapChain", "init", "Check for ID3D11CreateSwapChain()")
            exit(1);
    }

    // Crea una vista de renderizado (render target view) usando el buffer de intercambio
    hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer.m_texture);
    if (FAILED(hr)) {
        ERROR("SwapChain", "init", "m_SwapChain->GetBuffer()")
            exit(1);
    }
}

void 
SwapChain::update()
{
    // Método para actualizar el estado del SwapChain (actualmente no implementado)
}

void 
SwapChain::render()
{
    // Método para realizar el renderizado (actualmente no implementado)
}

void 
SwapChain::destroy()
{
    // Libera el recurso del SwapChain de forma segura
    SAFE_RELEASE(m_SwapChain);
}

void
SwapChain::present()
{
    // Presenta el contenido del SwapChain en la pantalla
    m_SwapChain->Present(0, 0);
}