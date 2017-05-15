//
// Game.h
//

#pragma once

#include "StepTimer.h"
#include "DebugCamera.h"
#include "Camera.h"

#include <PrimitiveBatch.h>		//PrimitiveBatch
#include <VertexTypes.h>		//VertexPositionColor
#include <Effects.h>			//BasicEffect
#include <CommonStates.h>		//CommonStates
#include <SimpleMath.h>			//Vecter3
#include <Keyboard.h>			//キーボード

#include <Model.h>


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;

	//	プリミティブバッチ
	//std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> m_batch;
	//	エフェクト
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	//	入力
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	汎用ステート設定
	std::unique_ptr<DirectX::CommonStates> m_states;

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	//	デバッグカメラ
	std::unique_ptr<DebugCamera> m_debugCamera;

	//	エフェクトファクトリ
	std::unique_ptr<DirectX::EffectFactory> m_factory;
	//	モデル
	std::unique_ptr<DirectX::Model> m_modelSkydome;	//天球
	std::unique_ptr<DirectX::Model> m_modelGround;	//地面
	std::unique_ptr<DirectX::Model> m_modelSky;		//空球
	std::unique_ptr<DirectX::Model> m_modelTespot;	//ティーポット
	std::unique_ptr<DirectX::Model> m_modelHead;	//機体

	//	ワールド行列
	DirectX::SimpleMath::Matrix m_worldSky[20];		//空球
	DirectX::SimpleMath::Matrix m_worldTeaPot[20];	//ティーポット

	float m_angleSky = 0;	//角度

	float m_rotationTeapot = 0;	//回転

	float m_rad[20];		//角度
	float m_distance[20];	//距離

	float m_scale;
	float m_time;
	float m_val;

	std::unique_ptr<DirectX::Keyboard> m_keyboard;	//	キーボード

	DirectX::SimpleMath::Vector3 m_headPos;		//	自機の移動座標
	DirectX::SimpleMath::Matrix m_worldHead;	//	自機のワールド行列

	float headAngle;	//	旋回

	//	カメラ
	std::unique_ptr<Camera> m_Camera;
	DirectX::SimpleMath::Vector3 m_eyePos;


};