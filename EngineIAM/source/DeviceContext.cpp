#include "DeviceContext.h"


void
DeviceContext::destroy()
{
    // Libera el contexto del dispositivo para evitar fugas de memoria.
    SAFE_RELEASE(m_deviceContext);
}

void
DeviceContext::PSSetShaderResources(unsigned int StartSlot, unsigned int NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
    // Verifica si el puntero a los recursos de shader es nulo.
    if (ppShaderResourceViews == nullptr)
    {
        // Registra un error y termina el programa si el puntero es nulo.
        ERROR("DeviceContext", "PSSetShaderResources", "Check for ID3D11ShaderResourceView* const* ppShaderResourceViews");
        exit(1);
    }
    else
    {
        // Establece los recursos de shader para la etapa de píxeles.
        m_deviceContext->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }
}

void
DeviceContext::RSSetViewports(unsigned int NumViewports, const D3D11_VIEWPORT* pViewports)
{
    // Verifica si el puntero a los viewports es nulo.
    if (pViewports == nullptr)
    {
        // Registra un error y termina el programa si el puntero es nulo.
        ERROR("DeviceContext", "RSSetViewports", "CHECK for const D3D11_VIEWPORT* pViewports");
        exit(1);
    }
    else
    {
        // Establece los viewports para la etapa de rasterización.
        m_deviceContext->RSSetViewports(NumViewports, pViewports);
    }
}

void
DeviceContext::IASetInputLayout(ID3D11InputLayout* pInputLayout)
{
    // Verifica si el puntero al layout de entrada es nulo.
    if (pInputLayout == nullptr)
    {
        // Registra un error y termina el programa si el puntero es nulo.
        ERROR("DeviceContext", "IASetInputLayout", "CHECK FOR ID3D11InputLayout* pInputLayout");
        exit(1);
    }
    else
    {
        // Establece el layout de entrada para la etapa de ensamblaje.
        m_deviceContext->IASetInputLayout(pInputLayout);
    }
}

void
DeviceContext::VSSetShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstances, unsigned int NumClassInstances)
{
    // Verifica si el puntero al shader de vértices es nulo.
    if (pVertexShader == nullptr)
    {
        // Registra un error y termina el programa si el puntero es nulo.
        ERROR("DeviceContext", "VSSetShader", "CHECK FOR ID3D11VertexShader* pVertexShader");
        exit(1);
    }
    else
    {
        // Establece el shader de vértices para la etapa de vértices.
        m_deviceContext->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
    }
}

void
DeviceContext::PSSetShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstances, unsigned int NumClassInstances)
{
    // Verifica si el puntero al shader de píxeles es nulo.
    if (pPixelShader == nullptr)
    {
        // Registra un error y termina el programa si el puntero es nulo.
        ERROR("DeviceContext", "PSSetShader", "CHECK FOR ID3D11PixelShader* pPixelShader");
        exit(1);
    }
    else
    {
        // Establece el shader de píxeles para la etapa de píxeles.
        m_deviceContext->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
    }
}

void
DeviceContext::UpdateSubresource(ID3D11Resource* pDstResource, unsigned int DstSubresource, const D3D11_BOX* pDstBox, const void* pSrcData, unsigned int SrcRowPitch, unsigned int SrcDepthPitch)
{
    // Actualiza los sub-recursos de un recurso de destino con los datos proporcionados.
    m_deviceContext->UpdateSubresource(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}

void
DeviceContext::IASetVertexBuffers(unsigned int StartSlot, unsigned int NumBuffers, ID3D11Buffer* const* ppVertexBuffers, const unsigned int* pStrides, const unsigned int* pOffsets)
{
    // Establece los búferes de vértices para la etapa de ensamblaje de entrada.
    m_deviceContext->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}

void
DeviceContext::IASetIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, unsigned int Offset)
{
    // Establece el búfer de índices para la etapa de ensamblaje de entrada.
    m_deviceContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
}

void
DeviceContext::PSSetSamplers(unsigned int StartSlot, unsigned int NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
    // Verifica si el puntero a los estados del muestreador es nulo.
    if (ppSamplers == nullptr)
    {
        // Registra un error si el puntero es nulo.
        ERROR("DeviceContext", "PSSetSamplers", "Check for ID3D11SamplerState* const* ppSamplers");
    }
    else
    {
        // Establece los estados del muestreador para la etapa de píxeles.
        m_deviceContext->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
    }
}




