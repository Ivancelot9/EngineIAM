#include "SamplerState.h"
#include "Device.h"
#include "DeviceContext.h"

// M�todo para inicializar el SamplerState
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
    memset(&sampDesc, 0, sizeof(sampDesc)); // Inicializa la descripci�n del sampler con ceros

    // Configuraci�n del filtro de textura para el sampler
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    // Configuraci�n de la direcci�n de la textura para el sampler (modo wrap)
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    // Configuraci�n de la funci�n de comparaci�n
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    // Configuraci�n del nivel de detalle m�nimo y m�ximo
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    // Crear el sampler state en el dispositivo
    hr = device.CreateSamplerState(&sampDesc, &m_sampler);

    // Verifica si la creaci�n del sampler state fall�
    if (FAILED(hr)) {
        ERROR("SamplerState", "init", "CHECK FOR CreateSamplerState");
        WARNING("ERROR: SamplerState::init : Error in data from params [CHECK FOR Device device]");
        exit(1);
    }
}

// M�todo para actualizar el SamplerState (actualmente vac�o, placeholder para futuras actualizaciones)
void SamplerState::update() {
}

// M�todo para aplicar el SamplerState al pipeline gr�fico
void SamplerState::render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumSamplers) {
    // Establece el sampler state en el pixel shader
    deviceContext.PSSetSamplers(StartSlot, NumSamplers, &m_sampler);
}

// M�todo para liberar los recursos del SamplerState
void SamplerState::destroy() {
    SAFE_RELEASE(m_sampler);
}