/// <summary>
/// 自機に追従するカメラクラス
/// </summary>
#pragma once

#include <Windows.h>
#include "Camera.h"
#include <Keyboard.h>

class FollowCamera :public Camera
{
public:
	//	自機とカメラの距離
	static const float CAMERA_DISTANCE;
	//	コンストラクタ
	FollowCamera(int width, int height);
	//	更新
	void Update() override;
	//	追従対象の座標をセット
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetPos);
	//	追従対象の回転角をセット
	void SetTargetAngle(float targetAngle);
	//	キーボードをセット
	void SetKeyboard(DirectX::Keyboard* keyboard);

protected:
	//	追従対象の座標
	DirectX::SimpleMath::Vector3 m_targetPos;
	//	追従対象の回転角
	float m_targetAngle;
	//	キーボード
	DirectX::Keyboard* m_keyboard;
	//	キーボードトラッカー
	DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;

private:
	//	FPSフラグ
	bool m_isFPS;

};

