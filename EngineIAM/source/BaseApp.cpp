#include "BaseApp.h"

HRESULT 
BaseApp::init(){
    HRESULT hr = S_OK;

    //Create SwapChain
    m_swapchain.init(m_device, m_deviceContext, m_backBuffer, m_window);
    // Create a render target view
    m_renderTargetView.init(m_device, m_backBuffer, DXGI_FORMAT_R8G8B8A8_UNORM);
    // Create depth stencil texture
    m_depthStencil.init(m_device, m_window.m_width,
        m_window.m_height,
        DXGI_FORMAT_D24_UNORM_S8_UINT,
        D3D11_BIND_DEPTH_STENCIL);
    //Create the depth stencil view
    m_depthStencilView.init(m_device, m_depthStencil, DXGI_FORMAT_D24_UNORM_S8_UINT);
    // Setup the viewport
    m_viewport.init(m_window);


    // Define the input layout
    std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;

    D3D11_INPUT_ELEMENT_DESC position;
    position.SemanticName = "POSITION";
    position.SemanticIndex = 0;
    position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    position.InputSlot = 0;
    position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
    position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    position.InstanceDataStepRate = 0;
    Layout.push_back(position);

    D3D11_INPUT_ELEMENT_DESC texcoord;
    texcoord.SemanticName = "TEXCOORD";
    texcoord.SemanticIndex = 0;
    texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;
    texcoord.InputSlot = 0;
    texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
    texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    texcoord.InstanceDataStepRate = 0;
    Layout.push_back(texcoord);

    m_ShaderProgram.init(m_device, "EngineIAM.fx", Layout);

    //Create Grid
    CreateGrid(50, 50, 25.0f);

    m_model.LoadModel("Models/Vela2.fbx");


    // Inicialización de Constant Buffers
    m_CBBufferNeverChanges.init(m_device, sizeof(CBNeverChanges));

    m_CBBufferChangeOnResize.init(m_device, sizeof(CBChangeOnResize));

    Texture Vela_Char_BaseColor;
    Vela_Char_BaseColor.init(m_device, "Textures/Vela/Vela_Char_BaseColor.png", ExtensionType::PNG);

    Texture Vela_Corneas_BaseColor;
    Vela_Corneas_BaseColor.init(m_device, "Textures/Vela/Vela_Corneas_BaseColor.png", ExtensionType::PNG);

    Texture Vela_Gun_BaseColor;
    Vela_Gun_BaseColor.init(m_device, "Textures/Vela/Vela_Gun_BaseColor.png", ExtensionType::PNG);

    Texture Vela_Legs_BaseColor;
    Vela_Legs_BaseColor.init(m_device, "Textures/Vela/Vela_Legs_BaseColor.png", ExtensionType::PNG);

    Texture Vela_Mechanical_BaseColor;
    Vela_Mechanical_BaseColor.init(m_device, "Textures/Vela/Vela_Mechanical_BaseColor.png", ExtensionType::PNG);

    Texture Vela_Plate_BaseColor;
    Vela_Plate_BaseColor.init(m_device, "Textures/Vela/Vela_Plate_BaseColor.png", ExtensionType::PNG);

    Texture Vela_Visor_BaseColor;
    Vela_Visor_BaseColor.init(m_device, "Textures/Vela/Vela_Visor_BaseColor.png", ExtensionType::PNG);

    modelTextures.push_back(Vela_Corneas_BaseColor);
    modelTextures.push_back(Vela_Gun_BaseColor);
    modelTextures.push_back(Vela_Visor_BaseColor);
    modelTextures.push_back(Vela_Legs_BaseColor);
    modelTextures.push_back(Vela_Mechanical_BaseColor);
    modelTextures.push_back(Vela_Char_BaseColor);
    modelTextures.push_back(Vela_Plate_BaseColor);

    m_default.init(m_device, "Textures/Default.png", ExtensionType::PNG);

    // Initialize the view matrix
    XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
    XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    m_View = XMMatrixLookAtLH(Eye, At, Up);

    cbNeverChanges.mView = XMMatrixTranspose(m_View);


    // Initialize the projection matrix
    m_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, m_window.m_width / (FLOAT)m_window.m_height, 0.01f, 100.0f);

    cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);

    // Set Vela Actor
    AVela = EngineUtilities::MakeShared<Actor>(m_device);

    if (!AVela.isNull()) {
        MESSAGE("Actor", "Actor", "Actor accessed successfully.")

            AVela->getComponent<Transform>()->setPosition(EngineUtilities::Vector3(-0.9f, -2.0f, 2.0f));
        AVela->getComponent<Transform>()->setRotation(EngineUtilities::Vector3(XM_PI / -2.0f, 0.0f, XM_PI / 2.0f));
        AVela->getComponent<Transform>()->setScale(EngineUtilities::Vector3(.03f, .03f, .03f));
        AVela->setMesh(m_device, m_model.meshes);
        AVela->setTextures(modelTextures);
    }
    else {
        MESSAGE("Actor", "Actor", "Actor resource not found.")
    }

    AGrid = EngineUtilities::MakeShared<Actor>(m_device);
    if (!AGrid.isNull()) {
        std::vector<MeshComponent> gridMesh;
        gridMesh.push_back(MC);
        AGrid->setMesh(m_device, gridMesh);
        gridTexs.push_back(m_default);
        AGrid->setTextures(gridTexs);
        AGrid->getComponent<Transform>()->setPosition(EngineUtilities::Vector3(0.0f,
            -2.0f,
            0.0f));
        AGrid->getComponent<Transform>()->setScale(EngineUtilities::Vector3(.03f,
            .03f,
            .03f));
        MESSAGE("Actor", "Actor", "Actor accessed successfully.")
    }
    else {
        MESSAGE("Actor", "Actor", "Actor resource not found.")
    }

    m_UserInterface.init(m_window.m_hWnd, m_device.m_device, m_deviceContext.m_deviceContext);
    return S_OK;
}

void 
BaseApp::update(){

    m_UserInterface.update();
    bool show_demo_window = true;

    ImGui::ShowDemoWindow(&show_demo_window);
   
    m_CBBufferNeverChanges.update(m_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
    m_CBBufferChangeOnResize.update(m_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

    // Actualizar info logica del mesh
    AVela->getComponent<Transform>()->ui_noWindow("Transform");
    AVela->update(0, m_deviceContext);
    AGrid->update(0, m_deviceContext);
    
}

void
BaseApp::render(){
    // Clear the back buffer
    float ClearColor[4] = { 0.85f, 0.85f, 0.85f, 1.0f }; // red, green, blue, alpha
    m_renderTargetView.render(m_deviceContext, m_depthStencilView, 1, ClearColor);

    // Set Viewport
    m_viewport.render(m_deviceContext);
    // Clear the depth buffer to 1.0 (max depth)
    m_depthStencilView.render(m_deviceContext);

    // Render the cube
    m_ShaderProgram.render(m_deviceContext);

    // Render the models
    AVela->render(m_deviceContext);
    AGrid->render(m_deviceContext);


    // Actualizar constant buffers
    m_CBBufferNeverChanges.render(m_deviceContext, 0, 1);
    m_CBBufferChangeOnResize.render(m_deviceContext, 1, 1);

    m_UserInterface.render();

    m_swapchain.present();
}

void 
BaseApp::destroy(){
    if (m_deviceContext.m_deviceContext) m_deviceContext.m_deviceContext->ClearState();

    AVela->destroy();
    AGrid->destroy();

    //m_default.destroy();
    m_CBBufferNeverChanges.destroy();
    m_CBBufferChangeOnResize.destroy();

    m_ShaderProgram.destroy();
    m_depthStencil.destroy();
    m_depthStencilView.destroy();
    m_renderTargetView.destroy();
    m_swapchain.destroy();
    m_deviceContext.destroy();
    // Release UI
    m_UserInterface.destroy();

    m_device.destroy();

}

int
BaseApp::run(HINSTANCE hInstance, HINSTANCE hPrevInstance,
             LPWSTR lpCmdLine, int nCmdShow,
             WNDPROC wndproc){

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (FAILED(m_window.init(hInstance, nCmdShow, wndproc)))
        return 0;

    if (FAILED(init()))
    {
        destroy();
        return 0;
    }

    // Main message loop
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            update();
            render();
        }
    }

    destroy();

    return (int)msg.wParam;
}

void 
BaseApp::CreateGrid(int width, int depth, float spacing){

    MC.m_vertex.clear();
    MC.m_index.clear();
    float halfLineWidth = 0.8 * 0.5f;
    for (int i = -width; i <= width; ++i)
    {
        //Create vertices for a vertical line as two triangules
        MC.m_vertex.push_back({ XMFLOAT3(i * spacing - halfLineWidth, 0, -depth * spacing),
                                XMFLOAT2(0.0f, 0.0f) });
        MC.m_vertex.push_back({ XMFLOAT3(i * spacing + halfLineWidth, 0, -depth * spacing),
                                XMFLOAT2(0.0f, 0.0f) });
        MC.m_vertex.push_back({ XMFLOAT3(i * spacing - halfLineWidth, 0, depth * spacing),
                                XMFLOAT2(0.0f, 0.0f) });
        MC.m_vertex.push_back({ XMFLOAT3(i * spacing + halfLineWidth, 0, depth * spacing),
                                XMFLOAT2(0.0f, 0.0f) });

        MC.m_index.push_back(MC.m_vertex.size() - 4);
        MC.m_index.push_back(MC.m_vertex.size() - 3);
        MC.m_index.push_back(MC.m_vertex.size() - 2);

        MC.m_index.push_back(MC.m_vertex.size() - 3);
        MC.m_index.push_back(MC.m_vertex.size() - 2);
        MC.m_index.push_back(MC.m_vertex.size() - 1);
    }

    for (int i = -depth; i <= depth; ++i)
    {
        //Create vertices for a horizontal line as two triangules
        MC.m_vertex.push_back({ XMFLOAT3(-width * spacing,0, i * spacing - halfLineWidth),
                               XMFLOAT2(0.0f, 0.0f) });
        MC.m_vertex.push_back({ XMFLOAT3(width * spacing,0, i * spacing - halfLineWidth),
                              XMFLOAT2(0.0f, 0.0f) });
        MC.m_vertex.push_back({ XMFLOAT3(-width * spacing,0, i * spacing + halfLineWidth),
                              XMFLOAT2(0.0f, 0.0f) });
        MC.m_vertex.push_back({ XMFLOAT3(width * spacing,0, i * spacing + halfLineWidth),
                              XMFLOAT2(0.0f, 0.0f) });


        MC.m_index.push_back(MC.m_vertex.size() - 4);
        MC.m_index.push_back(MC.m_vertex.size() - 3);
        MC.m_index.push_back(MC.m_vertex.size() - 2);

        MC.m_index.push_back(MC.m_vertex.size() - 3);
        MC.m_index.push_back(MC.m_vertex.size() - 2);
        MC.m_index.push_back(MC.m_vertex.size() - 1);
    }

    MC.m_numVertex = MC.m_vertex.size();
    MC.m_numIndex = MC.m_index.size();
}



