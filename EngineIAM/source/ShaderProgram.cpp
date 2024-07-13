#include "ShaderProgram.h"
#include "Device.h"
#include "DeviceContext.h"

void ShaderProgram::init(Device device, std::string fileName, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout)
{
    // Verificar si el dispositivo Direct3D es válido
    if (device.m_device == nullptr)
    {
        // Enviar un mensaje de error si el dispositivo no es válido y finalizar el programa
        ERROR("ShaderProgram", "init", "CHECK FOR Device Device")
            exit(1);
    }
    // Verificar si el layout tiene al menos un elemento
    else if (Layout.size() <= 1)
    {
        // Enviar un mensaje de error si el layout no tiene suficientes elementos y finalizar el programa
        ERROR("ShaderProgram", "init", "CHECK FOR vector<D3D11_INPUT_ELEMENT_DESC> Layout.size()")
            exit(1);
    }

    // Almacenar el nombre del archivo del shader
    m_shaderFileName = fileName;

    // Crear el shader de vértices utilizando el dispositivo
    CreateShader(device, ShaderType::VERTEX_SHADER);

    // Crear el Input Layout que describe la estructura de los datos de entrada del vértice
    CreateInputLayout(device, Layout);

    // Crear el shader de píxeles utilizando el dispositivo
    CreateShader(device, ShaderType::PIXEL_SHADER);
}

void ShaderProgram::render(DeviceContext& deviceContext)
{
    // Establecer el Input Layout en el contexto del dispositivo
    m_inputLayout.render(deviceContext);

    // Establecer el shader de vértices en el contexto del dispositivo
    deviceContext.VSSetShader(m_VertexShader, nullptr, 0);

    // Establecer el shader de píxeles en el contexto del dispositivo
    deviceContext.PSSetShader(m_PixelShader, nullptr, 0);
}

void ShaderProgram::destroy()
{
    // Liberar el recurso del shader de vértices
    SAFE_RELEASE(m_VertexShader);

    // Destruir el Input Layout
    m_inputLayout.destroy();

    // Liberar el recurso del shader de píxeles
    SAFE_RELEASE(m_PixelShader);
}

HRESULT ShaderProgram::CompileShaderFromFile(char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    // Configurar las banderas de compilación del shader
    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
    // Si está en modo de depuración, habilitar más verificaciones
#endif

    ID3DBlob* pErrorBlob = nullptr;

    // Compilar el shader desde el archivo especificado
    hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);

    // Manejar errores de compilación y mostrar mensajes de error si ocurren
    if (FAILED(hr))
    {
        if (pErrorBlob != NULL)
            OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
        if (pErrorBlob) pErrorBlob->Release();
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

void ShaderProgram::CreateInputLayout(Device device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout)
{
    // Inicializar el Input Layout con los datos del shader de vértices compilado
    m_inputLayout.init(device, Layout, m_vertexShaderData);

    // Liberar el recurso del shader de vértices compilado
    m_vertexShaderData->Release();
}

void ShaderProgram::CreateShader(Device device, ShaderType type)
{
    HRESULT hr = S_OK;
    ID3DBlob* shaderData = nullptr;

    // Determinar el punto de entrada y el modelo del shader basado en el tipo de shader (vértices o píxeles)
    const char* shaderEntryPoint = (type == PIXEL_SHADER) ? "PS" : "VS";
    const char* shaderModel = (type == PIXEL_SHADER) ? "ps_4_0" : "vs_4_0";

    // Compilar el shader desde el archivo especificado
    hr = CompileShaderFromFile(m_shaderFileName.data(), shaderEntryPoint, shaderModel, &shaderData);

    // Manejar errores de compilación y mostrar mensajes de error si ocurren
    if (FAILED(hr))
    {
        MessageBox(nullptr, "The FX cannot be compiled. Please Run this Executable from the directory that contains the FX file.", "Error", MB_OK);
        ERROR("ShaderProgram", "CreateShader", "CHECK FOR CompileShaderFromFile()");
        exit(1);
    }

    // Crear el shader correspondiente (vértices o píxeles) y verificar errores de creación
    if (type == PIXEL_SHADER)
    {
        hr = device.CreatePixelShader(shaderData->GetBufferPointer(), shaderData->GetBufferSize(), nullptr, &m_PixelShader);
    }
    else
    {
        hr = device.CreateVertexShader(shaderData->GetBufferPointer(), shaderData->GetBufferSize(), nullptr, &m_VertexShader);
    }

    // Manejar errores de creación del shader y mostrar mensajes de error si ocurren
    if (FAILED(hr))
    {
        shaderData->Release();
        ERROR("ShaderProgram", "CreateShader", "CHECK FOR device.Createshader()");
        exit(1);
    }

    // Almacenar los datos del shader compilado para su uso posterior
    if (type == PIXEL_SHADER)
    {
        m_pixelShaderData = shaderData;
    }
    else
    {
        m_vertexShaderData = shaderData;
    }
}