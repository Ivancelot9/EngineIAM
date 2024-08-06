#pragma once
#include "PreRequesites.h"
#include "Component.h"
//#include "Transform.h"

class DeviceContext;
class Entity
{
public:
	
	virtual ~Entity() = default;
	virtual void update(float deltaTime, DeviceContext deviceContext) = 0;
	virtual void render(DeviceContext deviceContext) = 0;
	template <typename T>
	void addComponent(std::shared_ptr<T> component) {

		static_assert(std::is_base_of <Component, T>::value, "T must be derived free Component");
		components.push_back(component);
	}

	template <typename T>
	std::shared_ptr<T> getComponent()
	{
		for (auto& component : componets)
		{
			std::shared_ptr<T> specificComponet = std::dynamic_pointer_cast<T>(component);
			if (specificComponet)
			{
				return specificComponet;
			}
		}
		return nullptr;
	}



protected:
	bool isActive; //Indica si la entidad esta activada
	std::string id; //Identificador unico de la identidad
	std::vector<std::shared_ptr<Component>> components; //Lista de componentes de la identidad

};

