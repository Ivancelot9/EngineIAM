#pragma once
#include "PreRequesites.h"

class Device;
class DeviceContext;

class SamplerState
{
public:
	SamplerState() = default;
	~SamplerState() = default;


	void init(Device device);
	void update();
	void render(DeviceContext& deviceContext, unsigned int StartSlot,
		unsigned int NumSamplers);
	void destroy();

private:
	ID3D11SamplerState* m_sampler = nullptr;

};
