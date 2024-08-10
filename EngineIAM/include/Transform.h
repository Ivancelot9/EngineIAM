#pragma once
#include "PreRequesites.h"
#include "Utilities/Vectors/Vector3.h"
#include "Component.h"
#include "UserInterface.h"


class Transform : public Component{
public:
    // Constructor que inicializa posición, rotación y escala a sus valores por defecto.
    // También inicializa la matriz de transformación y llama al constructor de la clase base `Component` con el tipo `TRANSFORM`.
    Transform() : position(), rotation(), scale(), matrix(), Component(ComponentType::TRANSFORM) {}

    // Devuelve una referencia constante a la posición actual del transform
    const 
    EngineUtilities::Vector3& getPosition() const { return position; }

    // Establece una nueva posición para el transform
    void 
    setPosition(const EngineUtilities::Vector3& newPos) { position = newPos; }

    // Devuelve una referencia constante a la rotación actual del transform
    const 
    EngineUtilities::Vector3& getRotation() const { return rotation; }

    // Establece una nueva rotación para el transform
    void 
    setRotation(const EngineUtilities::Vector3& newRot) { rotation = newRot; }

    // Devuelve una referencia constante a la escala actual del transform
    const 
    EngineUtilities::Vector3& getScale() const { return scale; }

    // Establece una nueva escala para el transform
    void
    setScale(const EngineUtilities::Vector3& newScale) { scale = newScale; }

    // Método para traducir (mover) el transform por una cantidad especificada
    void 
    translate(const EngineUtilities::Vector3& translation);

    // Destructor por defecto
    ~Transform() = default;

    // Inicializa el transform (posiblemente config. iniciales)
    void 
    init();

    // Actualiza el transform según el tiempo transcurrido (`deltaTime`)
    void 
    update(float deltaTime);

    // Renderiza el transform, posiblemente dibujando algún tipo de representación visual de la transformación
    void 
    render(DeviceContext deviceContext);

    // Destruye el transform, liberando cualquier recurso que pueda estar en uso
    void 
    destroy();

    // Métodos para la interfaz de usuario, permiten modificar propiedades del transform desde la UI
    void
    ui(std::string wName);

    void 
    ui_noWindow(std::string wName);

private:
    // Atributos de la transformación: posición, rotación y escala
    EngineUtilities::Vector3 position;
    EngineUtilities::Vector3 rotation;
    EngineUtilities::Vector3 scale;

    // Interfaz de usuario asociada con este componente
    UserInterface UI;

public:
    // Matriz de transformación que combina posición, rotación y escala para transformaciones en 3D
    XMMATRIX matrix;
};