/// <summary>
/// ３Dオブジェクトのクラス
/// </summary>
#pragma once

#include <windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>
#include <Effects.h>			//BasicEffect
#include <CommonStates.h>		//CommonStates
#include <SimpleMath.h>			//Vecter3
#include <Model.h>

#include "Camera.h"

class Obj3d
{
public:
	//	静的メンバ関数
	static void InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext,
		Camera* camera);

private:
	//	静的メンバ変数
	//	デバイス
	static Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	//	デバイスコンテキスト
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext;
	//	カメラ
	static Camera* m_Camera;
	//	汎用ステート設定
	static std::unique_ptr<DirectX::CommonStates> m_states;
	//	エフェクトファクトリ
	static std::unique_ptr<DirectX::EffectFactory> m_factory;



public:
	//	コンストラクタ
	Obj3d();
	//	コピーコンストラクタ
	//Obj3d(const Obj3d& obj);

	//	CMOモデルを読み込む
	void LoadModel(const wchar_t* fileName);
	//	更新
	void Update();
	//	描画
	void Draw();

	//	メンバ関数
	//setter
	//	スケーリング(XYZ)
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	//	回転角(XYZ)→フラグをオフ
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation) { m_rotation = rotation; m_UseQuaternion = false; }
	//	回転角(クォータニオン)→フラグをオン
	void SetRotationQ(const DirectX::SimpleMath::Quaternion& rotationQ) { m_rotationQ = rotationQ; m_UseQuaternion = true; }
	//	平行移動(XYZ)
	void SetTranslation(const DirectX::SimpleMath::Vector3& translation) { m_translation = translation; }
	//	ワールド行列
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { m_world = world; }
	//	親の3Dオブジェクト
	void SetObjParent(Obj3d* objParentle) { m_ObjParent = objParentle; }

	//getter
	//	スケーリング(XYZ)
	const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; }
	//	回転角(XYZ)
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_rotation; }
	//	平行移動(XYZ)
	const DirectX::SimpleMath::Vector3& GetTranslation() { return m_translation; }
	//	ワールド行列
	const DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }

private:
	//	メンバ変数
	//	モデル
	//std::unique_ptr<DirectX::Model> m_modelSkydome;	//天球
	//std::unique_ptr<DirectX::Model> m_modelGround;	//地面
	//std::unique_ptr<DirectX::Model> m_modelSky;		//空球
	//std::unique_ptr<DirectX::Model> m_modelTespot;	//ティーポット
	std::unique_ptr<DirectX::Model> m_modelHead;	//機体
	//	スケーリング(XYZ)
	DirectX::SimpleMath::Vector3 m_scale;
	//	回転角(XYZ)
	DirectX::SimpleMath::Vector3 m_rotation;
	//	回転角(クォータニオン)
	DirectX::SimpleMath::Quaternion m_rotationQ;
	//	平行移動(XYZ)
	//DirectX::SimpleMath::Vector3 m_headPos;		//	自機の移動座標
	DirectX::SimpleMath::Vector3 m_translation;		//	自機の移動座標
	//	ワールド行列
	DirectX::SimpleMath::Matrix m_world;			//	自機のワールド行列
	//DirectX::SimpleMath::Matrix m_worldHead2;	//	自機のワールド行列2
	//	親のObj3dへのポインタ
	Obj3d* m_ObjParent;
	//	回転をクォータニオンで扱うフラグ
	bool m_UseQuaternion;

};
