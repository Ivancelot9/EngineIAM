#pragma once
#include "PreRequesites.h"

class Device;
class DeviceContext;

class SamplerState {
public:
    // Constructor por defecto
    SamplerState() = default;

    // Destructor por defecto
    ~SamplerState() = default;

    // Método para inicializar el estado del sampler
    void 
    init(Device device);

    // Método para actualizar el estado del sampler (actualmente no implementado)
    void 
    update();

    // Método para aplicar el estado del sampler en el contexto de renderizado
    void 
    render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumSamplers);

    // Método para liberar los recursos asociados al sampler
    void
    destroy();

private:
    // Puntero al estado del sampler de Direct3D
    ID3D11SamplerState* m_sampler = nullptr;
};
