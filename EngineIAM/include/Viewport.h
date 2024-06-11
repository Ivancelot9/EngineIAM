#pragma once
#include "PreRequesites.h"
class Window;
class DeviceContext;

class Viewport
{
public:
	Viewport() = default;
	~Viewport() = default;

	void init(Window window);
	void update();
	void render(DeviceContext& deviceContext);
	void destroy();


public:
	D3D11_VIEWPORT m_viewport;

};

