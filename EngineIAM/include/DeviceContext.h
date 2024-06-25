#pragma once
#include "PreRequesites.h"

class DeviceContext
{
public:
	DeviceContext() =default;
	~DeviceContext() =default;

	void init();

	void update();

	void render();

	void destroy();

	void PSSetShaderResources(unsigned int StartSlot, unsigned int NumViews,  
		ID3D11ShaderResourceView* const* ppShaderResourceViews);

	void RSSetViewports(unsigned int NumViewports, const D3D11_VIEWPORT* pViewports);

	void IASetInputLayout(ID3D11InputLayout* pInputLayout);

	void VSSetShader(ID3D11VertexShader* pVertexShader,
		ID3D11ClassInstance* const* ppClassInstances, unsigned int NumClassInstances);

	void PSSetShader(ID3D11PixelShader* pPixelShader,
		ID3D11ClassInstance* const* ppClassInstances, unsigned int NumClassInstances);


public:
	ID3D11DeviceContext* m_deviceContext = nullptr;

};

