#pragma once
#include "PreRequesites.h"

class Device;
class DeviceContext;
class MeshComponent;
///                <summary>
/// Buffer:es un área de memoria que se utiliza para 
/// almacenar datos temporales mientras se procesan. 
/// Los buffers son fundamentales para la eficiencia y la gestión 
/// de recursos en la representación de gráficos. 
///                  </summary>
class Buffer{
public:
	Buffer() = default;
	~Buffer() = default;

	//Inicializa vertex y index buffers
	void 
	init(Device device, MeshComponent mesh, unsigned int bindFlag);

	//Inicializa los Constant Buffers
	void 
	init(Device device, unsigned int ByteWidth);

	//Actualizar logica del Constant Buffer
	void 
	update(DeviceContext& deviceContex, unsigned int DstSubresource, 
		        const D3D11_BOX* pDstBox,
		        const void* pSrcData,
		        unsigned int SrcRowPitch,
		        unsigned int SrcDepthPitch); 
	//Actualiza el render en el Buffer
	void 
	render(DeviceContext& deviceContext, unsigned int StartSlot,
		unsigned int NumBuffers);
	//Actualiza el render index buffer
	void 
	render(DeviceContext& deviceContext, DXGI_FORMAT format);
	//Actualiza en render el constant buffer
	void 
	renderModel(DeviceContext& deviceContext,
		             unsigned int StartSlot,
		             unsigned int NumBuffers);

	void 
	destroy();

private:
	void 
	createBuffer(Device& device, D3D11_BUFFER_DESC& desc,
		         D3D11_SUBRESOURCE_DATA* initData);
	
private:
	ID3D11Buffer* m_buffer = nullptr;
	unsigned int m_stride = 0;
	unsigned int m_offset = 0;
	unsigned int m_bindFlag = 0;
};

