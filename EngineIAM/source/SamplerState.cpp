#include "SamplerState.h"
#include "Device.h"
#include "DeviceContext.h"

// Método para inicializar el SamplerState
void SamplerState::init(Device device) {
    // Verifica que el dispositivo no sea nulo
    if (device.m_device == nullptr) {
        ERROR("SamplerState", "init", "CHECK FOR Unsupported BindFlag");
        WARNING("ERROR: SamplerState::init : Error in data from params [CHECK FOR Device device]");
        exit(1);
    }

    // Crear el estado del sampler
    HRESULT hr = S_OK;
    D3D11_SAMPLER_DESC sampDesc;
    memset(&sampDesc, 0, sizeof(sampDesc)); // Inicializa la descripción del sampler con ceros

    // Configuración del filtro de textura para el sampler
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    // Configuración de la dirección de la textura para el sampler (modo wrap)
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    // Configuración de la función de comparación
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    // Configuración del nivel de detalle mínimo y máximo
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    // Crear el sampler state en el dispositivo
    hr = device.CreateSamplerState(&sampDesc, &m_sampler);

    // Verifica si la creación del sampler state falló
    if (FAILED(hr)) {
        ERROR("SamplerState", "init", "CHECK FOR CreateSamplerState");
        WARNING("ERROR: SamplerState::init : Error in data from params [CHECK FOR Device device]");
        exit(1);
    }
}

// Método para actualizar el SamplerState (actualmente vacío, placeholder para futuras actualizaciones)
void SamplerState::update() {
}

// Método para aplicar el SamplerState al pipeline gráfico
void SamplerState::render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumSamplers) {
    // Establece el sampler state en el pixel shader
    deviceContext.PSSetSamplers(StartSlot, NumSamplers, &m_sampler);
}

// Método para liberar los recursos del SamplerState
void SamplerState::destroy() {
    SAFE_RELEASE(m_sampler);
}