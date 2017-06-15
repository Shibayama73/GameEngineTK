//	衝突判定ライブラリ

#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>

//	球クラス
class Sphere
{
public:
	//	中心座標
	DirectX::SimpleMath::Vector3 Center;
	//	半径
	float Radius;
	//	コンストラクタ
	Sphere() {
		Radius = 1.0f;
	}
};

//	線分クラス
class Segment
{
public:
	//	始点座標
	DirectX::SimpleMath::Vector3 Start;
	//	終点座標
	DirectX::SimpleMath::Vector3 End;
};

bool CheckSphere2Sphere(const Sphere & _sphereA, const Sphere & _sphereB);
