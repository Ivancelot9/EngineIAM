#pragma once
#include "PreRequesites.h"
#include "Utilities/Vectors/Vector3.h"
#include "Component.h"
#include "UserInterface.h"


class Transform : public Component{
public:
    // Constructor que inicializa posici�n, rotaci�n y escala a sus valores por defecto.
    // Tambi�n inicializa la matriz de transformaci�n y llama al constructor de la clase base `Component` con el tipo `TRANSFORM`.
    Transform() : position(), rotation(), scale(), matrix(), Component(ComponentType::TRANSFORM) {}

    // Devuelve una referencia constante a la posici�n actual del transform
    const 
    EngineUtilities::Vector3& getPosition() const { return position; }

    // Establece una nueva posici�n para el transform
    void 
    setPosition(const EngineUtilities::Vector3& newPos) { position = newPos; }

    // Devuelve una referencia constante a la rotaci�n actual del transform
    const 
    EngineUtilities::Vector3& getRotation() const { return rotation; }

    // Establece una nueva rotaci�n para el transform
    void 
    setRotation(const EngineUtilities::Vector3& newRot) { rotation = newRot; }

    // Devuelve una referencia constante a la escala actual del transform
    const 
    EngineUtilities::Vector3& getScale() const { return scale; }

    // Establece una nueva escala para el transform
    void
    setScale(const EngineUtilities::Vector3& newScale) { scale = newScale; }

    // M�todo para traducir (mover) el transform por una cantidad especificada
    void 
    translate(const EngineUtilities::Vector3& translation);

    // Destructor por defecto
    ~Transform() = default;

    // Inicializa el transform (posiblemente config. iniciales)
    void 
    init();

    // Actualiza el transform seg�n el tiempo transcurrido (`deltaTime`)
    void 
    update(float deltaTime);

    // Renderiza el transform, posiblemente dibujando alg�n tipo de representaci�n visual de la transformaci�n
    void 
    render(DeviceContext deviceContext);

    // Destruye el transform, liberando cualquier recurso que pueda estar en uso
    void 
    destroy();

    // M�todos para la interfaz de usuario, permiten modificar propiedades del transform desde la UI
    void
    ui(std::string wName);

    void 
    ui_noWindow(std::string wName);

private:
    // Atributos de la transformaci�n: posici�n, rotaci�n y escala
    EngineUtilities::Vector3 position;
    EngineUtilities::Vector3 rotation;
    EngineUtilities::Vector3 scale;

    // Interfaz de usuario asociada con este componente
    UserInterface UI;

public:
    // Matriz de transformaci�n que combina posici�n, rotaci�n y escala para transformaciones en 3D
    XMMATRIX matrix;
};