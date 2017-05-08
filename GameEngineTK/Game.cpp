//
// Game.cpp
//

#include "pch.h"
#include "Game.h"


extern void ExitGame();

using namespace DirectX;

using Microsoft::WRL::ComPtr;

using namespace DirectX::SimpleMath;

Game::Game() :
    m_window(0),
    m_outputWidth(800),
    m_outputHeight(600),
    m_featureLevel(D3D_FEATURE_LEVEL_9_1)
{
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_window = window;
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateDevice();

    CreateResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

	//	初期化はここから=================================================
	//m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(m_d3dContext.Get());		//	Get()で生ポインタを渡す
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionNormal>>(m_d3dContext.Get());		//	Get()で生ポインタを渡す

	m_effect = std::make_unique<BasicEffect>(m_d3dDevice.Get());		//	Get()で生ポインタを渡す

	m_effect->SetProjection(XMMatrixOrthographicOffCenterRH(0,m_outputWidth, m_outputHeight, 0, 0, 1));
	m_effect->SetVertexColorEnabled(true);

	void const* shaderByteCode;
	size_t byteCodeLength;

	m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	m_d3dDevice->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_inputLayout.GetAddressOf());

	//	汎用ステート設定生成
	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());

	//	デバッグカメラ生成
	m_debugCamera = std::make_unique<DebugCamera>(m_outputWidth, m_outputHeight);

	//	エフェクトファクトリ作成
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	//	テクスチャファイル指定
	m_factory->SetDirectory(L"Resources");
	//	モデル生成
	m_modelSkydome = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/Skydome.cmo", *m_factory);
	//m_modelGround = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/Ground.cmo", *m_factory);
	m_modelGround = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/Ground200.cmo", *m_factory);
	
	m_modelSky = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/sky.cmo", *m_factory);

	//	ティーポットの生成
	//m_modelTespot = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/Teapot.cmo", *m_factory);
	
	//	機体
	m_modelHead = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/head.cmo", *m_factory);

	//	球内での位置設定
	for (int i = 0; i < 20; i++)
	{
		m_rad[i] = rand() / XM_2PI;
		m_distance[i] = rand() % 100;
	}

	m_scale = rand() / XM_2PI;
	m_time = 0;


	m_keyboard = std::make_unique<Keyboard>();

	headAngle = 0.0f;
	//====================================================================

}

// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	// TODO: Add your game logic here.
	elapsedTime;

	//	毎フレーム処理はここから
	m_debugCamera->Update();	//デバッグカメラ更新

	//	回転用のカウント
	//m_angleSky += 0.01f;
	m_rotationTeapot += 1.0f;

	//	空球ワールド行列の計算
	//	スケーリング
	Matrix scalemat = Matrix::CreateScale(1.0f);	//倍




	//m_time++;

	//float val;
	//if (m_time % 600 == 0)
	//{
	//	m_scale = rand() / XM_2PI;
	//	for(float i=0.0f;i<60;i+=0.01f)
	//	val = sinf(m_scale);					//0-1
	//}
	//else
	//{
	//	m_scale = rand() / XM_2PI;
	//	for (float i = 0.0f; i<60; i += 0.01f)
	//	val = sinf(m_scale) + 1.0f;			//0-2
	//}
	////float val3 = (sinf(m_scale) + 1.0f)*50.0f;	//0-100
	////float scal = val * val2 * val3;

	//Matrix scalemat = Matrix::CreateScale(val);



	//m_time += 0.01f;
	//if (m_time / 60.0f == 0.0f)
	//{
	//	m_scale = rand() / XM_2PI;
	//	m_val = sinf(m_scale);					//0-1
	//}
	//else if (m_time / 60.0f == 1.0f)
	//{
	//	m_scale = rand() / XM_2PI;
	//	m_val = sinf(m_scale) + 1.0f;			//0-2
	//}
	//else if (m_time / 60.0f == 2.0f)
	//{
	//	m_scale = rand() / XM_2PI;
	//	m_val = (sinf(m_scale) + 1.0f)*50.0f;	//0-100
	//}
	//else
	//{
	//	m_val = m_val;
	//}
	////float scal = val * val2 * val3;

	//Matrix scalemat = Matrix::CreateScale(m_val);







	//2====================================================================================
	//for (int i = 0; i < 20; i++)
	//{
	//	//	ロール
	//	Matrix rotmatz = Matrix::CreateRotationZ(XMConvertToRadians(0.0f));
	//	//	ピッチ（仰角）
	//	Matrix rotmatx = Matrix::CreateRotationX(XMConvertToRadians(0.0f));
	//	//	ヨー（方位角）
	//	Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(0.0f + m_rotationTeapot));

	//	//	回転行列の合成(zxy)
	//	Matrix rotmat = rotmatx * rotmatz * rotmaty;

	//	//	平行移動
	//	Matrix transmat = Matrix::CreateTranslation(cosf(m_rad[i])*m_distance[i], 0, sinf(m_rad[i])*m_distance[i]);
	//	m_worldTeaPot[i] = scalemat * rotmat * transmat;

	//}


	//1=================================================================================
	//for (int i = 0; i < 20; i++)
	//{
	//	//	ロール
	//	Matrix rotmatz = Matrix::CreateRotationZ(XMConvertToRadians(0.0f));		//初期36*i
	//	//	ピッチ（仰角）
	//	Matrix rotmatx = Matrix::CreateRotationX(XMConvertToRadians(0.0f));		//初期90
	//	//	ヨー（方位角）
	//	Matrix rotmaty;
	//	if (i < 10)
	//		rotmaty = Matrix::CreateRotationY(XMConvertToRadians(36.0f*i) + m_angleSky);
	//	else
	//		rotmaty = Matrix::CreateRotationY(XMConvertToRadians(36.0f*i) - m_angleSky);

	//	//	回転行列の合成(zxy)
	//	Matrix rotmat = rotmatx * rotmatz * rotmaty;

	//	//	平行移動
	//	Matrix transmat;
	//	if (i < 10)
	//		transmat = Matrix::CreateTranslation(20, 0, 0);
	//	else
	//	{
	//		transmat = Matrix::CreateTranslation(40, 0, 0);
	//	}
	//	
	//	//	ワールド行列の合成(S*R*T)
	//	m_worldSky[i] = scalemat * transmat* rotmat;
	//}

	//	キーボードの状態取得
	Keyboard::State key = m_keyboard->GetState();

	//	Wキーが押されてるとき前進
	if (key.W)
	{
		//	移動ベクトル(Z座標前進)
		Vector3 moveV(0, 0, -0.1f);

		//	移動ベクトルを自機の角度分回転させる
		moveV = Vector3::TransformNormal(moveV, m_worldHead);
		//Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(headAngle));
		//moveV = Vector3::TransformNormal(moveV, rotmaty);

		//	自機の座標を移動
		m_headPos += moveV;
	}
	//	Sキーが押されてるとき後退
	if (key.S)
	{
		//	移動ベクトル(Z座標後退)
		Vector3 moveV(0, 0, 0.1f);


		//	移動ベクトルを自機の角度分回転させる
		moveV = Vector3::TransformNormal(moveV, m_worldHead);
		//Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(headAngle));
		//moveV = Vector3::TransformNormal(moveV, rotmaty);


		//	自機の座標を移動
		m_headPos += moveV;
	}
	//	Aキーが押されてるとき左旋回
	if (key.A)
	{
		headAngle += 0.1f;
		////	移動ベクトル左(X座標後退)
		//Vector3 moveV(-0.1f, 0, 0);
		////	自機の座標を移動
		//m_headPos += moveV;
	}
	//	Dキーが押されてるとき右旋回
	if (key.D)
	{
		headAngle -= 0.1f;

		////	移動ベクトル左(X座標前進)
		//Vector3 moveV(0.1f, 0, 0);
		////	自機の座標を移動
		//m_headPos += moveV;
	}

	{//	自機のワールド行列を計算

	 	//	ロール
	 	Matrix rotmatz = Matrix::CreateRotationZ(XMConvertToRadians(0.0f));
	 	//	ピッチ（仰角）
	 	Matrix rotmatx = Matrix::CreateRotationX(XMConvertToRadians(0.0f));
	 	//	ヨー（方位角）
	 	Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(0.0f)+headAngle);

	 	//	回転行列の合成(zxy)
	 	Matrix rotmat = rotmatx * rotmatz * rotmaty;

		//	平行移動
		Matrix transmat = Matrix::CreateTranslation(m_headPos);
		m_worldHead = rotmat * transmat;

	}


}

// Draws the scene.
void Game::Render()
{
	uint16_t indices[]=
	{
		0,1,2,
		2,1,3
	};

	VertexPositionNormal vertices[] =
	{
		{ Vector3(-1,+1,0),Vector3(0,0,1) },
		{ Vector3(-1,-1,0),Vector3(0,0,1) },
		{ Vector3(+1,+1,0),Vector3(0,0,1) },
		{Vector3(+1,-1,0),Vector3(0,0,1)},
	};

    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();	//	画面をクリアする

    // TODO: Add your rendering code here.
	//	描画処理はここから====================================================
	//	設定
	m_d3dContext->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
	m_d3dContext->OMSetDepthStencilState(m_states->DepthNone(), 0);	//	奥行
	m_d3dContext->RSSetState(m_states->CullClockwise());

	//	ビュー行列生成
	//m_view = Matrix::CreateLookAt(
	//	Vector3(0.f, 0.f, 2.f),	//カメラ視点
	//	Vector3(0,0,0),			//カメラ参照視点
	//	Vector3(0,1,0));		//上方向ベクトル
	//	デバッグカメラからビュー行列取得
	m_view = m_debugCamera->GetCameraMatrix();

	//	プロジェクション行列生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(
		XM_PI / 4.f,									//視野角(上下方向)
		float(m_outputWidth) / float(m_outputHeight),	//アスペクト比 
		0.1f,											//ニアクリップ(距離の制限)
		500.f);											//ファークリップ(距離の制限)

	m_effect->SetView(m_view);
	m_effect->SetProjection(m_proj);

	m_effect->Apply(m_d3dContext.Get());
	m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	//	モデルの描画
	m_modelSkydome->Draw(m_d3dContext.Get(), *m_states, m_world, m_view, m_proj);
	//m_modelGround->Draw(m_d3dContext.Get(), *m_states, m_world, m_view, m_proj);
	m_modelGround->Draw(m_d3dContext.Get(), *m_states, Matrix::Identity, m_view, m_proj);
	/*for (int i = 0; i < 20; i++)
	{
		m_modelSky->Draw(m_d3dContext.Get(), *m_states, m_worldSky[i], m_view, m_proj);
	}*/


	//for (int i = 0; i < 20; i++)
	//{
	//	//	ティーポットの描画
	//	m_modelTespot->Draw(m_d3dContext.Get(), *m_states, m_worldTeaPot[i], m_view, m_proj);
	//}

	//	機体
	m_modelHead->Draw(m_d3dContext.Get(), *m_states, m_worldHead, m_view, m_proj);



	//	描画
	m_batch->Begin();

	m_batch->DrawIndexed(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, indices,6, vertices, 4);

	//VertexPositionColor v1(Vector3(0.f, 0.5f, 0.5f), Colors::Red);
	//VertexPositionColor v2(Vector3(0.5f, -0.5f, 0.5f), Colors::Blue);
	//VertexPositionColor v3(Vector3(-0.5f, -0.5f, 0.5f), Colors::Yellow);
	//m_batch->DrawTriangle(v1, v2, v3);

	/*VertexPositionColor v1(SimpleMath::Vector3(400.f, 150.f, 0.f), Colors::Red);
	VertexPositionColor v2(SimpleMath::Vector3(600.f, 450.f, 0.f), Colors::Blue);
	VertexPositionColor v3(SimpleMath::Vector3(200.f, 450.f, 0.f), Colors::Yellow);
	m_batch->DrawTriangle(v1, v2, v3);*/

	//m_batch->DrawLine(
	//	VertexPositionColor(SimpleMath::Vector3(0, 0, 0), SimpleMath::Color(1,1,1)),
	//	VertexPositionColor(SimpleMath::Vector3(800, 600, 0), SimpleMath::Color(1, 0, 0))
	//);

	m_batch->End();

	//=======================================================================

    Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    // Clear the views.
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    // Set the viewport.
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
    m_d3dContext->RSSetViewports(1, &viewport);
}

// Presents the back buffer contents to the screen.
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = m_swapChain->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
        OnDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}

// These are the resources that depend on the device.
void Game::CreateDevice()
{
    UINT creationFlags = 0;

#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    static const D3D_FEATURE_LEVEL featureLevels [] =
    {
        // TODO: Modify for supported Direct3D feature levels (see code below related to 11.1 fallback handling).
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // Create the DX11 API device object, and get a corresponding context.
    HRESULT hr = D3D11CreateDevice(
        nullptr,                                // specify nullptr to use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        featureLevels,
        _countof(featureLevels),
        D3D11_SDK_VERSION,
        m_d3dDevice.ReleaseAndGetAddressOf(),   // returns the Direct3D device created
        &m_featureLevel,                        // returns feature level of device created
        m_d3dContext.ReleaseAndGetAddressOf()   // returns the device immediate context
        );

    if (hr == E_INVALIDARG)
    {
        // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it.
        hr = D3D11CreateDevice(nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            creationFlags,
            &featureLevels[1],
            _countof(featureLevels) - 1,
            D3D11_SDK_VERSION,
            m_d3dDevice.ReleaseAndGetAddressOf(),
            &m_featureLevel,
            m_d3dContext.ReleaseAndGetAddressOf()
            );
    }

    DX::ThrowIfFailed(hr);

#ifndef NDEBUG
    ComPtr<ID3D11Debug> d3dDebug;
    if (SUCCEEDED(m_d3dDevice.As(&d3dDebug)))
    {
        ComPtr<ID3D11InfoQueue> d3dInfoQueue;
        if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
        {
#ifdef _DEBUG
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
            D3D11_MESSAGE_ID hide [] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                // TODO: Add more message IDs here as needed.
            };
            D3D11_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumIDs = _countof(hide);
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
    }
#endif

    // DirectX 11.1 if present
    if (SUCCEEDED(m_d3dDevice.As(&m_d3dDevice1)))
        (void)m_d3dContext.As(&m_d3dContext1);

    // TODO: Initialize device dependent objects here (independent of window size).
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateResources()
{
    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews [] = { nullptr };
    m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_d3dContext->Flush();

    UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
    UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
    DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    UINT backBufferCount = 2;

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            OnDeviceLost();

            // Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
            // and correctly set up the new device.
            return;
        }
        else
        {
            DX::ThrowIfFailed(hr);
        }
    }
    else
    {
        // First, retrieve the underlying DXGI Device from the D3D Device.
        ComPtr<IDXGIDevice1> dxgiDevice;
        DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

        // Identify the physical adapter (GPU or card) this device is running on.
        ComPtr<IDXGIAdapter> dxgiAdapter;
        DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

        // And obtain the factory object that created it.
        ComPtr<IDXGIFactory1> dxgiFactory;
        DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

        ComPtr<IDXGIFactory2> dxgiFactory2;
        if (SUCCEEDED(dxgiFactory.As(&dxgiFactory2)))
        {
            // DirectX 11.1 or later

            // Create a descriptor for the swap chain.
            DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
            swapChainDesc.Width = backBufferWidth;
            swapChainDesc.Height = backBufferHeight;
            swapChainDesc.Format = backBufferFormat;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferCount = backBufferCount;

            DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = { 0 };
            fsSwapChainDesc.Windowed = TRUE;

            // Create a SwapChain from a Win32 window.
            DX::ThrowIfFailed(dxgiFactory2->CreateSwapChainForHwnd(
                m_d3dDevice.Get(),
                m_window,
                &swapChainDesc,
                &fsSwapChainDesc,
                nullptr,
                m_swapChain1.ReleaseAndGetAddressOf()
                ));

            DX::ThrowIfFailed(m_swapChain1.As(&m_swapChain));
        }
        else
        {
            DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
            swapChainDesc.BufferCount = backBufferCount;
            swapChainDesc.BufferDesc.Width = backBufferWidth;
            swapChainDesc.BufferDesc.Height = backBufferHeight;
            swapChainDesc.BufferDesc.Format = backBufferFormat;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.OutputWindow = m_window;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.Windowed = TRUE;

            DX::ThrowIfFailed(dxgiFactory->CreateSwapChain(m_d3dDevice.Get(), &swapChainDesc, m_swapChain.ReleaseAndGetAddressOf()));
        }

        // This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
        DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
    }

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain1.Reset();
    m_swapChain.Reset();
    m_d3dContext1.Reset();
    m_d3dContext.Reset();
    m_d3dDevice1.Reset();
    m_d3dDevice.Reset();

    CreateDevice();

    CreateResources();
}