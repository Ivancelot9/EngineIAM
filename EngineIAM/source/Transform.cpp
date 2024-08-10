#include "Transform.h"
#include "DeviceContext.h"


void 
Transform::translate(const EngineUtilities::Vector3& translation) {
    // Suma el vector de traslaci�n a la posici�n actual del objeto.
    // Esto mueve el objeto en la direcci�n y magnitud especificadas por 'translation'.
    position = position + translation;
}

void
Transform::init() {
    // Inicializa la escala del objeto a 1 en todos los ejes (sin escalado).
    scale.x = 1;
    scale.y = 1;
    scale.z = 1;

    // Inicializa la matriz de transformaci�n a la matriz identidad.
    // La matriz identidad no aplica ninguna transformaci�n y es el punto de partida para cualquier transformaci�n.
    matrix = XMMatrixIdentity();
}

void 
Transform::update(float deltaTime) {
    // Crea una matriz de escala basada en los valores actuales de escala del objeto.
    XMMATRIX scaleMatrix = XMMatrixScaling(scale.x, scale.y, scale.z);

    // Crea una matriz de rotaci�n usando los �ngulos de rotaci�n actuales del objeto (en radianes).
    // La rotaci�n se aplica en el orden: Roll (Z), Pitch (X), Yaw (Y).
    XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

    // Crea una matriz de traslaci�n basada en la posici�n actual del objeto.
    XMMATRIX translationMatrix = XMMatrixTranslation(position.x, position.y, position.z);

    // Combina las matrices de escala, rotaci�n y traslaci�n en ese orden.
    // Esto da como resultado la matriz de transformaci�n final que se aplicar� al objeto.
    matrix = scaleMatrix * rotationMatrix * translationMatrix;
}

void 
Transform::render(DeviceContext deviceContext) {
    // Este m�todo est� vac�o actualmente, pero se puede utilizar para realizar
    // operaciones de renderizado espec�ficas para el Transform, como dibujar
    // gizmos de transformaci�n para depuraci�n.
}

void 
Transform::destroy() {
    // M�todo vac�o por ahora. Aqu� se pueden liberar recursos asociados al Transform,
    // aunque en este caso parece que no hay nada que liberar.
}

void 
Transform::ui(std::string wName) {
    // Comienza una nueva ventana ImGui con el nombre proporcionado 'wName'.
    ImGui::Begin(wName.c_str());

    // Dibuja controles de interfaz de usuario para modificar la posici�n, rotaci�n y escala del objeto.
    // Los controles permiten al usuario ajustar estos valores a trav�s de la interfaz gr�fica.
    UI.vec3Control("Position", const_cast<float*>(position.data()));
    UI.vec3Control("Rotation", const_cast<float*>(rotation.data()));
    UI.vec3Control("Scale", const_cast<float*>(scale.data()));

    // Finaliza la ventana ImGui.
    ImGui::End();
}

void 
Transform::ui_noWindow(std::string wName) {
    // Asigna un ID �nico para este conjunto de controles ImGui bas�ndose en el nombre 'wName'.
    ImGui::PushID(wName.c_str());

    // Dibuja controles de interfaz de usuario para modificar la posici�n, rotaci�n y escala del objeto,
    // pero sin crear una nueva ventana. Estos controles se muestran en el contexto actual de ImGui.
    UI.vec3Control("Position", const_cast<float*>(position.data()));
    UI.vec3Control("Rotation", const_cast<float*>(rotation.data()));
    UI.vec3Control("Scale", const_cast<float*>(scale.data()));

    // Quita el ID �nico asignado previamente.
    ImGui::PopID();
}




