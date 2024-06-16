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

public:
	ID3D11DeviceContext* m_deviceContext = nullptr;

};

