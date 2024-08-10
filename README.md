EngineIAM
Motor en proceso de desarrollo para Arquitectura de Motores

Descripción

EngineIAM es un motor gráfico en desarrollo basado en Direct3D 11, una API de gráficos 3D de alto rendimiento proporcionada por Microsoft. Está diseñado para ofrecer una base sólida para el desarrollo de aplicaciones gráficas y videojuegos, facilitando la gestión y manipulación de recursos gráficos como texturas, shaders y buffers. Además, EngineIAM incluye componentes esenciales para la manipulación de entidades, componentes y transformaciones en el entorno gráfico.

Características

Gestión de Dispositivos y Contextos:

Device: Encargado de la creación y gestión de recursos en la GPU, garantizando un acceso eficiente a la memoria gráfica.
DeviceContext: Maneja el estado del pipeline gráfico y realiza las operaciones de renderizado.
SwapChain: Administra la cadena de intercambio para la presentación de imágenes en pantalla, facilitando la creación y gestión de vistas de renderizado.
Gestión de Recursos Gráficos:

Texture: Maneja texturas en 2D, incluyendo la carga de imágenes desde archivos y la creación de recursos de textura en la memoria GPU.
DepthStencilView: Maneja vistas de profundidad y stencil, cruciales para el renderizado preciso de escenas 3D.
SamplerState: Define los parámetros de muestreo de texturas para controlar cómo se filtran y aplican las texturas.
Definición de Vistas y Buffers:

Viewport: Define la región rectangular de la ventana de renderizado.
SimpleVertex: Define los datos básicos de vértice, como la posición y coordenadas de textura.
CBNeverChanges, CBChangeOnResize, CBChangesEveryFrame: Buffers constantes para pasar datos a los shaders, optimizados para diferentes frecuencias de cambio.
Componentes y Entidades:

Component: Clase base abstracta para todos los componentes del juego, que define métodos para actualizar y renderizar componentes.
Entity: Representa una entidad en el juego, que puede tener múltiples componentes y gestionar su estado activo y único identificador.
Actor: Deriva de Entity y añade funcionalidades específicas como la gestión de mallas (MeshComponent), texturas y buffers, así como métodos para actualizar y renderizar actores en la escena.
Transform: Maneja la posición, rotación y escala de un objeto en el espacio 3D. Incluye métodos para actualizar la matriz de transformación y controles de interfaz de usuario para manipular estas propiedades en tiempo real.
Sistema de Aplicación:

BaseApp: La clase principal que gestiona la inicialización, actualización, renderizado y destrucción del motor. Incluye la creación de la ventana, gestión de dispositivos gráficos, y manejo de buffers y texturas. También se encarga de la carga de modelos y la interfaz de usuario.
Requisitos

Sistema Operativo: Windows 7 o superior.
SDK: DirectX SDK (Direct3D 11).
Compilador: Visual Studio 2019 o superior.
Para más información detallada sobre el proyecto, incluyendo documentación técnica y avances, puedes visitar este enlace en Notion: https://www.notion.so/6ee3186f406742eb89bd4fc1cba436a2?v=a4ef2891633845bbafe92ef16ac95593&p=29bceca9345545a4a195d9987eb0e7c1&pm=s
