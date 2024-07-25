#pragma once

class DeviceContext;

enum ComponentType
{
	NONE = 0,//Tipo de componotente no especificado
	TRANSFORM = 1,//Componente de tranformacion
	MESH = 2,//Componente de Malla
	MATERIAL = 3///Compoende de Material
};
class Component
{
public:
	/**
	* @class Component
	* @brief Clase base abstracta para todos los componentes del juego
	* 
	*/
	Component() = default;
	Component(const ComponentType type) : m_type(type){}
	virtual	~Component() = default;
	virtual void update(float deltaTime) = 0;
	virtual void render(DeviceContext deviceContext) = 0;
	ComponentType getType() const { return m_type; }

protected:
	ComponentType m_type; // Tipo de Componente

};

