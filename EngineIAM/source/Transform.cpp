#include "Transform.h"
#include "DeviceContext.h"


void 
Transform::translate(const EngineUtilities::Vector3& translation) {
    // Suma el vector de traslación a la posición actual del objeto.
    // Esto mueve el objeto en la dirección y magnitud especificadas por 'translation'.
    position = position + translation;
}

void
Transform::init() {
    // Inicializa la escala del objeto a 1 en todos los ejes (sin escalado).
    scale.x = 1;
    scale.y = 1;
    scale.z = 1;

    // Inicializa la matriz de transformación a la matriz identidad.
    // La matriz identidad no aplica ninguna transformación y es el punto de partida para cualquier transformación.
    matrix = XMMatrixIdentity();
}

void 
Transform::update(float deltaTime) {
    // Crea una matriz de escala basada en los valores actuales de escala del objeto.
    XMMATRIX scaleMatrix = XMMatrixScaling(scale.x, scale.y, scale.z);

    // Crea una matriz de rotación usando los ángulos de rotación actuales del objeto (en radianes).
    // La rotación se aplica en el orden: Roll (Z), Pitch (X), Yaw (Y).
    XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

    // Crea una matriz de traslación basada en la posición actual del objeto.
    XMMATRIX translationMatrix = XMMatrixTranslation(position.x, position.y, position.z);

    // Combina las matrices de escala, rotación y traslación en ese orden.
    // Esto da como resultado la matriz de transformación final que se aplicará al objeto.
    matrix = scaleMatrix * rotationMatrix * translationMatrix;
}

void 
Transform::render(DeviceContext deviceContext) {
    // Este método está vacío actualmente, pero se puede utilizar para realizar
    // operaciones de renderizado específicas para el Transform, como dibujar
    // gizmos de transformación para depuración.
}

void 
Transform::destroy() {
    // Método vacío por ahora. Aquí se pueden liberar recursos asociados al Transform,
    // aunque en este caso parece que no hay nada que liberar.
}

void 
Transform::ui(std::string wName) {
    // Comienza una nueva ventana ImGui con el nombre proporcionado 'wName'.
    ImGui::Begin(wName.c_str());

    // Dibuja controles de interfaz de usuario para modificar la posición, rotación y escala del objeto.
    // Los controles permiten al usuario ajustar estos valores a través de la interfaz gráfica.
    UI.vec3Control("Position", const_cast<float*>(position.data()));
    UI.vec3Control("Rotation", const_cast<float*>(rotation.data()));
    UI.vec3Control("Scale", const_cast<float*>(scale.data()));

    // Finaliza la ventana ImGui.
    ImGui::End();
}

void 
Transform::ui_noWindow(std::string wName) {
    // Asigna un ID único para este conjunto de controles ImGui basándose en el nombre 'wName'.
    ImGui::PushID(wName.c_str());

    // Dibuja controles de interfaz de usuario para modificar la posición, rotación y escala del objeto,
    // pero sin crear una nueva ventana. Estos controles se muestran en el contexto actual de ImGui.
    UI.vec3Control("Position", const_cast<float*>(position.data()));
    UI.vec3Control("Rotation", const_cast<float*>(rotation.data()));
    UI.vec3Control("Scale", const_cast<float*>(scale.data()));

    // Quita el ID único asignado previamente.
    ImGui::PopID();
}




