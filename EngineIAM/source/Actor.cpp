#include "Actor.h"
#include "MeshComponent.h"
#include "Device.h"
#include "Transform.h"

Actor::Actor(Device device) {
    // Crear e inicializar un componente de transformación y agregarlo al actor
    std::shared_ptr<Transform> transform = std::make_shared<Transform>();
    addComponent(transform);

    // Crear e inicializar un componente de malla y agregarlo al actor
    std::shared_ptr<MeshComponent> Mesh = std::make_shared<MeshComponent>();
    addComponent(Mesh);

    // Inicializar el buffer del modelo con el tamaño de la estructura CBChangesEveryFrame
    m_modelBuffer.init(device, sizeof(CBChangesEveryFrame));

    // Inicializar el estado del sampler
    m_sampler.init(device);
}

void 
Actor::update(float deltaTime, DeviceContext deviceContext) {
    // Actualizar el componente de transformación
    getComponent<Transform>()->update(deltaTime);

    // Actualizar la matriz del modelo con la transformación actual
    model.mWorld = XMMatrixTranspose(getComponent<Transform>()->matrix);

    // Definir el color de la malla
    model.vMeshColor = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);

    // Actualizar el buffer del modelo con los datos actuales
    m_modelBuffer.update(deviceContext, 0, nullptr, &model, 0, 0);
}

void 
Actor::render(DeviceContext deviceContext) {
    // Iterar sobre las mallas del actor y renderizarlas
    for (unsigned int i = 0; i < m_meshes.size(); i++) {
        // Renderizar el buffer de vértices
        m_vertexBuffer[i].render(deviceContext, 0, 1);

        // Renderizar el buffer de índices
        m_indexBuffers[i].render(deviceContext, DXGI_FORMAT_R32_UINT);

        // Renderizar la textura asociada, si existe
        if (m_textures.size() > 0) {
            if (i <= m_textures.size() - 1) {
                m_textures[i].render(deviceContext, 0, 1);
            }
            else {
                // Renderizar textura por defecto si hay menos texturas que mallas
                // m_default.render(deviceContext, 0, 1);
            }
        }

        // Renderizar el sampler
        m_sampler.render(deviceContext, 0, 1);

        // Renderizar el buffer del modelo
        m_modelBuffer.renderModel(deviceContext, 2, 1);

        // Configurar la topología de primitivos para el dibujo
        deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        // Dibujar los índices de la malla
        deviceContext.m_deviceContext->DrawIndexed(m_meshes[i].m_numIndex, 0, 0); // Referencia para los índices
    }
}

void 
Actor::destroy() {
    // Limpiar los buffers de vértices
    for (auto& vertexBuffer : m_vertexBuffer) {
        vertexBuffer.destroy();
    }

    // Limpiar los buffers de índices
    for (auto& indexBuffer : m_indexBuffers) {
        indexBuffer.destroy();
    }

    // Limpiar las texturas
    for (auto& tex : m_textures) {
        tex.destroy();
    }

    // Limpiar el buffer del modelo y el sampler
    m_modelBuffer.destroy();
    m_sampler.destroy();
}

void 
Actor::setMesh(Device device, std::vector<MeshComponent> meshes) {
    // Configurar las mallas del actor
    m_meshes = meshes;

    // Inicializar los buffers de vértices e índices para cada malla
    for (auto& mesh : m_meshes) {
        Buffer vertexBuffer;
        vertexBuffer.init(device, mesh, D3D11_BIND_VERTEX_BUFFER);
        m_vertexBuffer.push_back(vertexBuffer);

        Buffer indexBuffer;
        indexBuffer.init(device, mesh, D3D11_BIND_INDEX_BUFFER);
        m_indexBuffers.push_back(indexBuffer);
    }
}

void 
Actor::setTextures(std::vector<Texture> textures) {
    // Configurar las texturas del actor
    m_textures = textures;
}