#pragma once
#include "PreRequesites.h"
#include "Component.h"
#include "DeviceContext.h"

class MeshComponent : public Component {
public:
    // Constructor que inicializa el número de vértices e índices a 0
    // Y llama al constructor de la clase base Component con el tipo MESH
    MeshComponent() : m_numVertex(0), m_numIndex(0), Component(ComponentType::MESH) {}

    // Destructor virtual por defecto
    virtual
    ~MeshComponent() = default;

    // Método sobrescrito para actualizar el componente
    // En este caso, no se realiza ninguna operación
    void 
    update(float deltaTime) override {}

    // Método sobrescrito para renderizar el componente
    // En este caso, no se realiza ninguna operación
    void 
    render(DeviceContext deviceContext) override {}

public:
    // Nombre del mesh (malla), puede ser útil para identificarlo
    std::string m_name;

    // Vector que almacena los vértices de la malla
    std::vector<SimpleVertex> m_vertex;

    // Vector que almacena los índices de la malla
    // Los índices definen el orden en que los vértices se conectan para formar triángulos
    std::vector<unsigned int> m_index;

    // Número de vértices en la malla
    int m_numVertex;

    // Número de índices en la malla
    int m_numIndex;
};
