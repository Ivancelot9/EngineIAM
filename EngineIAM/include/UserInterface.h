#pragma once
#include "PreRequesites.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include <imgui_internal.h>


class UserInterface
{
public:
    UserInterface() = default;
    ~UserInterface() = default;

    void init(void* window, ID3D11Device* device, ID3D11DeviceContext* deviceContext);

    void update();

    void render();

    void destroy();

   


private:

};