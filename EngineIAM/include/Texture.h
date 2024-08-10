#pragma once
#include "PreRequesites.h"

class Device;
class DeviceContext;

class Texture{
public:
	Texture() = default;
	~Texture() = default;
	/// <summary>
	/// 
	/// </summary>
	/// Brief: Crea una textura a partir de una imagen (.dds) desde nuestro ordenador
	/// <param name="device"></param> Lllamamos al DEvice paea poder generar recuersos en la memoria
	/// <param name="textureName"></param>Almacenar el nombre de la textura
	HRESULT 
    init(Device device, std::string textureName, ExtensionType extensionType);
	/// <summary>
/// Brief: Este metodo es el reposable de crear Textura en 2D 
/// </summary>
	void 
	init(Device device, unsigned int width, unsigned int height, 
		 DXGI_FORMAT Format, unsigned int BindFlags);


	void 
    update();
/// <summary>
/// Brief: Este metodoco carga la actualizacion de la logica de la textura
/// </summary>

	void 
	render(DeviceContext & deviceContext,
		   unsigned int StartSlot, unsigned int NumViews);
/// <summary>
/// Brief: Este metodo se encarga de dibujar los recursos en la pantalla
/// </summary>

	/// <summary>
	/// Este metodo se encarga de realizar los recursos almacenados en la memoria de la clase
	/// </summary>
	void 
	destroy();


public:
	ID3D11Texture2D* m_texture = nullptr;//Esta variable maneja un recurso de textura como datos
	ID3D11ShaderResourceView* m_textureFromImg;//Esta variable maneja un recurso de textura como datos de imagen

};

