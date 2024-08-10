#pragma once
#include "PreRequesites.h"

class
    DeviceContext {
public:
    DeviceContext() = default;
    ~DeviceContext() = default;

    // Inicializa el contexto del dispositivo.
    void
    init();

    // Actualiza el estado del contexto del dispositivo.
    void
    update();

    // Renderiza el contenido usando el contexto del dispositivo.
    void
    render();

    // Libera los recursos asociados con el contexto del dispositivo.
    void
    destroy();

    // Establece los recursos de shader para la etapa de p�xeles (Pixel Shader).
    void
    PSSetShaderResources(unsigned int StartSlot, unsigned int NumViews,
                         ID3D11ShaderResourceView* const* ppShaderResourceViews);

    // Configura las �reas de vista para la etapa de rasterizaci�n (Rasterizer State).
    void
    RSSetViewports(unsigned int NumViewports, const D3D11_VIEWPORT* pViewports);

    // Define el dise�o de entrada para la etapa de ensamblaje de entrada (Input Assembler).
    void
    IASetInputLayout(ID3D11InputLayout* pInputLayout);

    // Establece el shader de v�rtices (Vertex Shader) y sus instancias de clase.
    void
    VSSetShader(ID3D11VertexShader* pVertexShader,
            ID3D11ClassInstance* const* ppClassInstances, unsigned int NumClassInstances);

    // Establece el shader de p�xeles (Pixel Shader) y sus instancias de clase.
    void
    PSSetShader(ID3D11PixelShader* pPixelShader,
                ID3D11ClassInstance* const* ppClassInstances, unsigned int NumClassInstances);

    // Actualiza una sub-recurso en una textura, b�fer, etc.
    void
    UpdateSubresource(ID3D11Resource* pDstResource,
                      unsigned int DstSubresource,
                      const D3D11_BOX* pDstBox, const void* pSrcData,
                      unsigned int SrcRowPitch,
                      unsigned int SrcDepthPitch);

    // Establece los b�feres de v�rtices para la etapa de ensamblaje de entrada (Input Assembler).
    void
    IASetVertexBuffers(unsigned int StartSlot, unsigned int NumBuffers,
                       ID3D11Buffer* const* ppVertexBuffers,
                       const unsigned int* pStrides,
                       const unsigned int* pOffsets);

    // Establece el b�fer de �ndices para la etapa de ensamblaje de entrada (Input Assembler).
    void
        IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
                         DXGI_FORMAT Format,
                         unsigned int Offset);

    // Establece los estados del muestreador para la etapa de p�xeles (Pixel Shader).
    void
        PSSetSamplers(unsigned int StartSlot, unsigned int NumSamplers,
                      ID3D11SamplerState* const* ppSamplers);

public:
    // Puntero al contexto del dispositivo de DirectX 11.
    ID3D11DeviceContext* m_deviceContext = nullptr;
};

