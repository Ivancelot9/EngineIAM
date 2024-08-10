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

    // Método para inicializar el programa de shader, cargando el archivo de shader y configurando el layout de entrada
    void 
    init(Device device, std::string fileName,
         std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

    // Método para actualizar el estado del shader (actualmente no implementado)
    void 
    update();

    // Método para renderizar utilizando el contexto del dispositivo
    void 
    render(DeviceContext& deviceContext);

    // Método para liberar los recursos asociados al shader
    void 
    destroy();

    // Método para compilar un shader desde un archivo
    HRESULT CompileShaderFromFile(char* szFileName, LPCSTR szEntryPoint,
                                  LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

    // Método para crear un layout de entrada a partir de una descripción dada
    void 
    CreateInputLayout(Device device,
                      std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

    // Método para crear un shader del tipo especificado
    void 
    CreateShader(Device device, ShaderType type);

public:
    // Puntero al shader de vértices
    ID3D11VertexShader* m_VertexShader = nullptr;

    // Puntero al shader de píxeles
    ID3D11PixelShader* m_PixelShader = nullptr;

    // Objeto que representa el layout de entrada utilizado por los shaders
    InputLayout m_inputLayout;

private:
    // Nombre del archivo de shader utilizado para inicialización
    std::string m_shaderFileName;

    // Puntero al blob que contiene los datos del shader de vértices compilado
    ID3DBlob* m_vertexShaderData = nullptr;

    // Puntero al blob que contiene los datos del shader de píxeles compilado
    ID3DBlob* m_pixelShaderData = nullptr;
};

