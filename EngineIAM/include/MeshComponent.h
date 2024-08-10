#pragma once
#include "PreRequesites.h"
#include "Component.h"
#include "DeviceContext.h"

class MeshComponent : public Component {
public:
    // Constructor que inicializa el n�mero de v�rtices e �ndices a 0
    // Y llama al constructor de la clase base Component con el tipo MESH
    MeshComponent() : m_numVertex(0), m_numIndex(0), Component(ComponentType::MESH) {}

    // Destructor virtual por defecto
    virtual
    ~MeshComponent() = default;

    // M�todo sobrescrito para actualizar el componente
    // En este caso, no se realiza ninguna operaci�n
    void 
    update(float deltaTime) override {}

    // M�todo sobrescrito para renderizar el componente
    // En este caso, no se realiza ninguna operaci�n
    void 
    render(DeviceContext deviceContext) override {}

public:
    // Nombre del mesh (malla), puede ser �til para identificarlo
    std::string m_name;

    // Vector que almacena los v�rtices de la malla
    std::vector<SimpleVertex> m_vertex;

    // Vector que almacena los �ndices de la malla
    // Los �ndices definen el orden en que los v�rtices se conectan para formar tri�ngulos
    std::vector<unsigned int> m_index;

    // N�mero de v�rtices en la malla
    int m_numVertex;

    // N�mero de �ndices en la malla
    int m_numIndex;
};
