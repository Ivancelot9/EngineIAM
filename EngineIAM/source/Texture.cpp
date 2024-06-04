#include "Texture.h"
#include "Device.h"
#include "DeviceContext.h"

HRESULT Texture::init(Device device, std::string textureName)
{
	HRESULT hr = S_OK;
	if (device.m_device == nullptr)
	{
		ERROR("Texture", "init", "CHECK FOR Device device on texture loading method")
		exit(1);
	}
	// Load the Texture
	hr = D3DX11CreateShaderResourceViewFromFile(device.m_device, 
		textureName.c_str(), nullptr, nullptr,
		&m_textureFromImg, nullptr);

	if (FAILED(hr))
	{

		ERROR("Texture", "init", "Error in data from params [Check For string textureName -> Verifi correct texture name in file")
			exit(1);
	}
		return hr;
}

void Texture::init(Device device,
	               unsigned int width, 
	               unsigned int height, 
	               DXGI_FORMAT Format, 
	               unsigned int BindFlags)
{

	if (device.m_device == nullptr)
	{
		ERROR("Texture", "init", "CHECK FOR Device device on texture loading method")
			exit(1);
	}
	else if (width <= 0 || height <= 0)
	{
		ERROR("Texture", "init", "CHECK FOR unsigned int width or unsigned int height")
			exit(1);
	}

	HRESULT hr = S_OK;

	D3D11_TEXTURE2D_DESC desc;
	memset(&desc,0, sizeof(desc));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = Format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = BindFlags;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	hr = device.CreateTexture2D(&desc, nullptr, &m_texture);
	if (m_texture == nullptr)
	{
		ERROR("Texture", "init", "Error in data drom params [Check for m_texture]")
			exit(1);
	}
	else if (FAILED(hr))
	{
		ERROR("Texture","init", "Error in data drom resource[Check for CreateTexture2D]")
			exit(1);
	}
}

void Texture::update()
{
}

void Texture::render(DeviceContext& deviceContext, 
	unsigned int StartSlot,
	unsigned int NumViews)
{
	if (m_textureFromImg != nullptr)
	{
		ID3D11ShaderResourceView* nullSRV[] = { nullptr };
		deviceContext.PSSetShaderResources(StartSlot, NumViews, nullSRV);
		deviceContext.PSSetShaderResources(StartSlot, NumViews, &m_textureFromImg);
	}
}

void Texture::destroy()
{
	if (m_texture != nullptr)
	{
		SAFE_RELEASE(m_texture);
	}
	else if (m_textureFromImg != nullptr)
	{
		SAFE_RELEASE(m_textureFromImg);
	}
}
