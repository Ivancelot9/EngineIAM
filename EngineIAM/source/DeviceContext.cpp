#include "DeviceContext.h"

void 
DeviceContext::destroy()
{
	SAFE_RELEASE(m_deviceContext);
}

void DeviceContext::PSSetShaderResources(unsigned int StartSlot, 
	unsigned int NumViews, 
	ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	if (ppShaderResourceViews == nullptr)
	{
		ERROR("DeviceContext", "PSSetShaderResources", "Check for ID3D11ShaderResourceView* const* ppShaderResourceViews")
			exit(1);
	}
	else
	{
		m_deviceContext->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);

	}
}
