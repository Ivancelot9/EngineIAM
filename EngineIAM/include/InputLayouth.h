#pragma once
#include "PreRequesites.h"

class Device;
class DeviceContext;

class InputLayout
{
public:
    // Constructor y destructor por defecto.
    InputLayout() = default;
    ~InputLayout() = default;

    // Inicializa el InputLayout con un dispositivo, una descripci�n de la disposici�n de entrada, 
    // y los datos del shader de v�rtices.
    void init(Device device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout, ID3DBlob* VertexShaderData);

    // M�todo de actualizaci�n del InputLayout. Dependiendo del contexto de tu aplicaci�n, 
    // este m�todo podr�a contener l�gica para actualizar el estado del InputLayout.
    void update();

    // Renderiza el InputLayout utilizando un DeviceContext. Configura el InputLayout en la tuber�a gr�fica.
    void render(DeviceContext& deviceContext);

    // Destruye y libera los recursos asociados con el InputLayout para evitar fugas de memoria.
    void destroy();

public:
    // Puntero al layout de entrada de DirectX 11.
    ID3D11InputLayout* m_inputLayout = nullptr;
};