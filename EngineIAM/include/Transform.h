#pragma once
#include "PreRequesites.h"
#include "Utilities/Vectors/Vector3.h"
#include "Component.h"
#include "UserInterface.h"


class Transform : public Component
{
public:
    //Constructor que inicializa posicion, rotattion y escala
    Transform() : position(), rotation(), scale(), matrix(), Component(ComponentType::TRANSFORM){}

    const EngineUtilities::Vector3& getPosition() const { return position; }
    void setPosition(const EngineUtilities::Vector3& newPos) { position = newPos;}

    const EngineUtilities::Vector3& getRotation() const { return rotation; }
    void setRotation(const EngineUtilities::Vector3& newRot) { rotation = newRot; }

    const EngineUtilities::Vector3& getScale() const { return scale; }
    void setScale(const EngineUtilities::Vector3& newScale) { scale = newScale; }

    void translate(const EngineUtilities::Vector3& translation);


    ~Transform() = default;

    void init();
    void update(float deltaTime);
    void render(DeviceContext deviceContext);
    void destroy();

    void ui(std::string wName);
    void ui_noWindow(std::string wName);

private: 
    EngineUtilities :: Vector3 position;
    EngineUtilities :: Vector3 rotation;
    EngineUtilities :: Vector3 scale;
    UserInterface UI;

public:
    XMMATRIX matrix;
};