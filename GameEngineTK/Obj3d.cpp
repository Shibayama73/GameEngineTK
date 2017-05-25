#include "Obj3d.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	静的メンバ変数の定義(実態)
//	デバイス
Microsoft::WRL::ComPtr<ID3D11Device> Obj3d::m_d3dDevice;
//	デバイスコンテキスト
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Obj3d::m_d3dContext;
//	カメラ
Camera* Obj3d::m_Camera;
//	汎用ステート設定
std::unique_ptr<DirectX::CommonStates> Obj3d::m_states;
//	エフェクトファクトリ
std::unique_ptr<DirectX::EffectFactory> Obj3d::m_factory;

void Obj3d::InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, Camera * camera)
{
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
	m_Camera = camera;

	//	汎用ステート設定生成
	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());
	//	エフェクトファクトリ作成
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	//	テクスチャファイル指定
	m_factory->SetDirectory(L"Resources");


}

Obj3d::Obj3d()
{
	//	メンバ変数の初期化
//	m_translation = Vector3(0, 0, 30);
	m_scale = Vector3(1, 1, 1);
	m_ObjParent = nullptr;

}

void Obj3d::LoadModel(const wchar_t * fileName)
{
	//	CMOからモデルの読み込み
	//	モデル生成
//	m_modelSkydome = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/Skydome.cmo", *m_factory);
	//m_modelGround = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/Ground.cmo", *m_factory);
//	m_modelGround = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/Ground200.cmo", *m_factory);
//	m_modelSky = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/sky.cmo", *m_factory);
	//	ティーポットの生成
	//m_modelTespot = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/Teapot.cmo", *m_factory);
	//	機体
	//m_modelHead = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/head.cmo", *m_factory);
	m_modelHead = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);

}

void Obj3d::Update()
{
	//	ワールド行列の計算
	//{//	自機のワールド行列を計算
	// //	ロール
	//	Matrix rotmatz = Matrix::CreateRotationZ(XMConvertToRadians(0.0f));
	//	//	ピッチ（仰角）
	//	Matrix rotmatx = Matrix::CreateRotationX(XMConvertToRadians(0.0f));
	//	//	ヨー（方位角）
	//	Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(0.0f) + headAngle);

	//	//	回転行列の合成(zxy)
	//	Matrix rotmat = rotmatx * rotmatz * rotmaty;

	//	//	平行移動
	//	Matrix transmat = Matrix::CreateTranslation(m_translation);
	//	m_worldHead = rotmat * transmat;

	//}
	{//	自機2のワールド行列を計算

	 //	ワールド行列の計算
		Matrix scalemat = Matrix::CreateScale(m_scale);
		Matrix rotmatZ = Matrix::CreateRotationZ(m_rotation.z);
		Matrix rotmatX = Matrix::CreateRotationX(m_rotation.x);
		Matrix rotmatY = Matrix::CreateRotationY(m_rotation.y);
		Matrix rotmat = rotmatZ * rotmatX * rotmatY;
		Matrix transmat = Matrix::CreateTranslation(m_translation);

		//	ワールド座標の合成
		m_world = scalemat * rotmat * transmat;
		//	親の行列を掛ける(子供の行列＊親の行列)
		if (m_ObjParent)
		{
			m_world *= m_ObjParent->GetWorld();
		}

	}
}

void Obj3d::Draw()
{
	//	描画
	//	設定
	m_d3dContext->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
	m_d3dContext->OMSetDepthStencilState(m_states->DepthNone(), 0);	//	奥行
	m_d3dContext->RSSetState(m_states->CullClockwise());

	
	//	モデルの描画
//	m_modelSkydome->Draw(m_d3dContext.Get(), *m_states, m_world, m_view, m_proj);
	//m_modelGround->Draw(m_d3dContext.Get(), *m_states, m_world, m_view, m_proj);
//	m_modelGround->Draw(m_d3dContext.Get(), *m_states, Matrix::Identity, m_view, m_proj);
	/*for (int i = 0; i < 20; i++)
	{
		m_modelSky->Draw(m_d3dContext.Get(), *m_states, m_worldSky[i], m_view, m_proj);
	}*/


	//for (int i = 0; i < 20; i++)
	//{
	//	//	ティーポットの描画
	//	m_modelTespot->Draw(m_d3dContext.Get(), *m_states, m_worldTeaPot[i], m_view, m_proj);
	//}
	if (m_modelHead)
	{
		//	機体
		m_modelHead->Draw(m_d3dContext.Get(), *m_states, m_world, m_Camera->GetViewMatrix(), m_Camera->GetProjectionMatrix());
		//m_modelHead->Draw(m_d3dContext.Get(), *m_states, m_worldHead2, m_view, m_proj);
	}

}
