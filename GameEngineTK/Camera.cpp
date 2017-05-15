#include "pch.h"
#include "Camera.h"


using namespace DirectX;
using Microsoft::WRL::ComPtr;
using namespace DirectX::SimpleMath;


Camera::Camera(int Width, int Height)
{
	//	初期化==========================================
	//	カメラの位置（視点座標）
	m_eyepos = Vector3(0, 0, 5.0f);
	//	カメラの見ている先（注視点・参照点）
	m_refpos = Vector3(0, 0, 10);
	//	カメラの上方向ベクトル
	m_upvec = Vector3(0, 1.0f, 0);
	//	垂直方向視野角
	m_fovY = XMConvertToRadians(60.0f);
	//	アスペクト比（画面比率）
	m_aspect = (float)Width / Height;
	//	ニアクリップ（手前の表示限界距離）
	m_nearclip = 0.1f;
	//	ファークリップ（奥の表示限界距離）
	m_farclip = 1000.0f;

	//=======================================================
	//	ビュー行列の生成
	m_upvec.Normalize();	//長さを1に調整する
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	//	射影行列の生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);

}

Camera::~Camera()
{
}

//	更新
void Camera::Update()
{
	//	ビュー行列の生成
	m_upvec.Normalize();	//長さを1に調整する
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	//	射影行列の生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);

}

//	ビュー行列の取得
DirectX::SimpleMath::Matrix Camera::GetViewMatrix()
{
	//	ビュー行列の生成
	m_upvec.Normalize();	//長さを1に調整する
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	return m_view;
}

//	射影行列の取得
DirectX::SimpleMath::Matrix Camera::GetProjectionMatrix()
{
	//	射影行列の生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);

	return m_proj;
}

//	視点座標のセット
void Camera::SetEyePos(DirectX::SimpleMath::Vector3 eyepos)
{
	//	視点座標＝eyepos
	m_eyepos = eyepos;
}

void Camera::SetRefPos(DirectX::SimpleMath::Vector3 refpos)
{
	m_refpos = refpos;
}

void Camera::SetUpvec(DirectX::SimpleMath::Vector3 upvec)
{
	m_upvec = upvec;
}

void Camera::SetFovY(float fovY)
{
	m_fovY = fovY;
}

void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}

void Camera::SetNearclip(float nearclip)
{
	m_nearclip = nearclip;
}

void Camera::SetFarclip(float farclip)
{
	m_farclip = farclip;
}

