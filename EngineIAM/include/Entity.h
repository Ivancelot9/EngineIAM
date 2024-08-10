#pragma once
#include "PreRequesites.h"
#include "Component.h"


class DeviceContext;
class Entity {
public:
    // Destructor virtual para asegurar la correcta destrucci�n de objetos derivados de Entity
    virtual
    ~Entity() = default;

    // M�todo virtual puro para actualizar la entidad
    // Cada clase derivada debe implementar c�mo se actualizar� con el paso del tiempo
    virtual void 
    update(float deltaTime, DeviceContext deviceContext) = 0;

    // M�todo virtual puro para renderizar la entidad
    // Cada clase derivada debe implementar c�mo se renderizar�
    virtual void 
    render(DeviceContext deviceContext) = 0;

    // M�todo para a�adir un componente a la entidad
    // T debe ser un tipo que derive de la clase Component
    template <typename T>
    void 
    addComponent(std::shared_ptr<T> component) {
        // Verifica en tiempo de compilaci�n que T sea un derivado de Component
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

        // A�ade el componente a la lista de componentes de la entidad
        components.push_back(component);
    }

    // M�todo para obtener un componente espec�fico de la entidad
    // Busca y devuelve el primer componente que sea del tipo T
    template <typename T>
    std::shared_ptr<T> getComponent() {
        // Recorre la lista de componentes
        for (auto& component : components) {
            // Intenta convertir el componente actual al tipo T usando dynamic_pointer_cast
            std::shared_ptr<T> specificComponent = std::dynamic_pointer_cast<T>(component);

            // Si la conversi�n es exitosa (el componente es del tipo T), lo devuelve
            if (specificComponent) {
                return specificComponent;
            }
        }
        // Si no se encuentra ning�n componente del tipo T, devuelve un puntero nulo
        return nullptr;
    }

protected:
    // Variable que indica si la entidad est� activa o no
    bool isActive;

    // Identificador �nico de la entidad, �til para identificarla en un conjunto de entidades
    std::string id;

    // Lista de componentes que pertenecen a la entidad
    // Los componentes son compartidos a trav�s de std::shared_ptr para gestionar su ciclo de vida
    std::vector<std::shared_ptr<Component>> components;
};
