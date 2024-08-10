#pragma once
#include "PreRequesites.h"
#include "Entity.h"
#include "Buffer.h"
#include "Texture.h"
#include "SamplerState.h"
#include "Transform.h"

class Device;
class MeshComponent;

class Actor : public Entity {
public:
    // Constructor por defecto
    Actor() = default;

    // Constructor que inicializa un actor con un dispositivo específico
    Actor(Device device);

    // Destructor virtual por defecto
    virtual 
    ~Actor() = default;

    // Método para actualizar el actor en cada frame
    void 
    update(float deltaTime, DeviceContext deviceContext) override;

    // Método para renderizar el actor en cada frame
    void 
    render(DeviceContext deviceContext) override;

    // Método para destruir recursos asociados con el actor
    void 
    destroy();

    /**
     * @brief Método para obtener un componente específico del actor
     *
     * @tparam T Tipo de componente que se desea obtener
     * @return std::shared_ptr<T> Puntero compartido al componente solicitado
     */
    template <typename T>
    std::shared_ptr<T> getComponent();

    // Método para configurar la malla del actor
    void 
    setMesh(Device device, std::vector<MeshComponent> meshes);

    // Método para configurar las texturas del actor
    void 
    setTextures(std::vector<Texture> textures);

    // Método para obtener el nombre del actor
    std::string getName() { return m_name; }

private:
    // Vector que contiene las mallas asociadas al actor
    std::vector<MeshComponent> m_meshes;

    // Vector que contiene las texturas asociadas al actor
    std::vector<Texture> m_textures;

    // Estado del sampler usado para aplicar texturas
    SamplerState m_sampler;

    // Buffers que contienen la información de los vértices y los índices de la malla
    std::vector<Buffer> m_vertexBuffer;
    std::vector<Buffer> m_indexBuffers;

    // Buffer que contiene la información del modelo (transformaciones, etc.)
    Buffer m_modelBuffer;

    // Estructura que contiene los datos que cambian cada frame
    CBChangesEveryFrame model;

    // Nombre del actor
    std::string m_name = "Actor";
};

template <typename T>
inline std::shared_ptr<T> Actor::getComponent()
{
    // Recorre la lista de componentes del actor
    for (auto& component : components)
    {
        // Intenta convertir el componente actual al tipo T
        std::shared_ptr<T> specificComponent = std::dynamic_pointer_cast<T>(component);

        // Si la conversión es exitosa, retorna el componente
        if (specificComponent)
        {
            return specificComponent;
        }
    }

    // Si no se encuentra el componente del tipo T, retorna nullptr
    return nullptr;
}