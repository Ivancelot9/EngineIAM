#pragma once
#include "PreRequesites.h"
#include "InputLayouth.h"

class Device;
class DeviceContext;

class ShaderProgram{
public:
    // Constructor por defecto
    ShaderProgram() = default;

    // Destructor por defecto
    ~ShaderProgram() = default;

    // M�todo para inicializar el programa de shader, cargando el archivo de shader y configurando el layout de entrada
    void 
    init(Device device, std::string fileName,
         std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

    // M�todo para actualizar el estado del shader (actualmente no implementado)
    void 
    update();

    // M�todo para renderizar utilizando el contexto del dispositivo
    void 
    render(DeviceContext& deviceContext);

    // M�todo para liberar los recursos asociados al shader
    void 
    destroy();

    // M�todo para compilar un shader desde un archivo
    HRESULT CompileShaderFromFile(char* szFileName, LPCSTR szEntryPoint,
                                  LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

    // M�todo para crear un layout de entrada a partir de una descripci�n dada
    void 
    CreateInputLayout(Device device,
                      std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

    // M�todo para crear un shader del tipo especificado
    void 
    CreateShader(Device device, ShaderType type);

public:
    // Puntero al shader de v�rtices
    ID3D11VertexShader* m_VertexShader = nullptr;

    // Puntero al shader de p�xeles
    ID3D11PixelShader* m_PixelShader = nullptr;

    // Objeto que representa el layout de entrada utilizado por los shaders
    InputLayout m_inputLayout;

private:
    // Nombre del archivo de shader utilizado para inicializaci�n
    std::string m_shaderFileName;

    // Puntero al blob que contiene los datos del shader de v�rtices compilado
    ID3DBlob* m_vertexShaderData = nullptr;

    // Puntero al blob que contiene los datos del shader de p�xeles compilado
    ID3DBlob* m_pixelShaderData = nullptr;
};

