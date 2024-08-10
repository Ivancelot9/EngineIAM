#pragma once

class DeviceContext; // Declaraci�n adelantada de la clase DeviceContext

// Enumeraci�n que define los diferentes tipos de componentes que se pueden tener en el sistema
enum ComponentType {
    NONE = 0,       // Tipo de componente no especificado
    TRANSFORM = 1,  // Componente de transformaci�n (posici�n, rotaci�n, escala)
    MESH = 2,       // Componente de malla (geometr�a 3D)
    MATERIAL = 3    // Componente de material (texturas, propiedades de superficie)
};

/**
 * @class Component
 * @brief Clase base abstracta para todos los componentes del juego.
 *
 * Esta clase sirve como una interfaz para los diferentes tipos de componentes que se pueden
 * agregar a las entidades en el juego. Los componentes son unidades modulares que encapsulan
 * funcionalidad espec�fica, como transformaciones, mallas o materiales.
 */
class Component {
public:
    // Constructor por defecto
    Component() = default;

    /**
     * @brief Constructor que inicializa el tipo de componente
     * @param type Tipo de componente seg�n la enumeraci�n ComponentType
     */
    Component(const ComponentType type) : m_type(type) {}

    // Destructor virtual por defecto
    virtual
    ~Component() = default;

    /**
     * @brief M�todo virtual puro para actualizar el componente
     * @param deltaTime Tiempo transcurrido desde la �ltima actualizaci�n
     *
     * Este m�todo debe ser implementado por las clases derivadas para definir c�mo el componente
     * se actualiza cada ciclo de juego.
     */
    virtual void 
    update(float deltaTime) = 0;

    /**
     * @brief M�todo virtual puro para renderizar el componente
     * @param deviceContext Contexto del dispositivo de renderizado
     *
     * Este m�todo debe ser implementado por las clases derivadas para definir c�mo el componente
     * se renderiza en pantalla.
     */
    virtual void 
    render(DeviceContext deviceContext) = 0;

    /**
     * @brief Obtiene el tipo de componente
     * @return Tipo de componente (ComponentType)
     */
    ComponentType getType() const { return m_type; }

protected:
    ComponentType m_type; // Tipo de Componente, definido por la enumeraci�n ComponentType

};

