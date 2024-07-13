# EngineIAM
Motor en proceso de desarrollo para Arquitectura de Motores

# Descripción
Este proyecto es un motor gráfico desarrollado utilizando Direct3D 11, una API de gráficos 3D de alto rendimiento proporcionada por Microsoft. 
El motor está diseñado para proporcionar una base sólida para el desarrollo de aplicaciones gráficas y juegos, permitiendo una fácil gestión 
y manipulación de recursos gráficos como texturas, shaders, y buffers.

# Características
Gestión de Dispositivos y Contextos:

-Device: Encargado de la creación y gestión de recursos en la GPU.

-DeviceContext: Maneja el estado del pipeline y realiza las operaciones de renderizado.

-SwapChain: Administra la cadena de intercambio necesaria para la presentación de imágenes en pantalla, 
facilitando la creación de la vista de renderizado.

-Texture: Gestión de texturas en 2D, incluyendo la carga de imágenes desde archivos y la creación de recursos 
de textura en la memoria GPU.

-DepthStencilView: Manejo de vistas de profundidad y stencil, esenciales para el renderizado 
correcto de escenas 3D.

-Viewport: Define la región rectangular de la ventana de renderizado donde se dibuja la escena.

-SimpleVertex: Define los datos de vértice básicos, incluyendo posición y coordenadas de textura.

-CBNeverChanges, CBChangeOnResize, CBChangesEveryFrame: Buffers constantes utilizados para pasar datos a los shaders, 
optimizados para diferentes frecuencias de cambio (nunca, en redimensionado, cada frame).

# Requisitos
Sistema Operativo: Windows 7 o superior.

SDK: DirectX SDK (Direct3D 11).

Compilador: Visual Studio 2019 o superior.
