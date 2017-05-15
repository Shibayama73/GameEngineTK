#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	静的メンバ変数の初期化
const float FollowCamera::CAMERA_DISTANCE = 5.0f;

//	コンストラクタ
FollowCamera::FollowCamera(int width, int height)
	:Camera(width, height)
{
	//	初期化===============================
	//	追従対象の座標
	m_targetPos = Vector3(0, 0, 0);
	//	追従対象の回転角
	m_targetAngle = 0.0f;

}

//	更新
void FollowCamera::Update()
{
	//	カメラの設定（自機に追従するカメラ）
	//	視点・参照点の座標
	Vector3 eyepos, refpos;

	//	参照点座標の計算
	refpos = m_targetPos + Vector3(0, 2.0f, 0);
	//	自機からカメラまでの距離
	Vector3 cameraV(0, 0, CAMERA_DISTANCE);

	//	自機から後ろに回り込むための回転行列
	Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
	//	カメラへのベクトルを回転させる
	cameraV = Vector3::TransformNormal(cameraV, rotmat);

	//	カメラ座標を計算
	eyepos = refpos + cameraV;

	//	カメラに情報を渡す
	this->SetRefPos(refpos);
	this->SetEyePos(eyepos);

	//	カメラ(基底クラス)の更新
	Camera::Update();

}

//	追従対象の座標をセット
void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetPos)
{
	m_targetPos = targetPos;
}

//	追従対象の回転角をセット
void FollowCamera::SetTargetAngle(float targetAngle)
{
	m_targetAngle = targetAngle;
}

