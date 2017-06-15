#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// 球と球の当たり判定
/// </summary>
/// <param name="_sphereA">球A</param>
/// <param name="_sphereB">球B</param>
/// <returns>true:当たっている、false:当たっていない</returns>
bool CheckSphere2Sphere(const Sphere& _sphereA, const Sphere& _sphereB)
{
	//	AからBに向かうベクトル
	Vector3 sub = _sphereB.Center - _sphereA.Center;
	
	//	AとBの距離の計算
	//float distance = sqrtf(sub.x * sub.x + sub.y * sub.y + sub.z * sub.z);
	//	AとBの距離の２乗の計算
	float distanceSqare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	//	半径の和の計算
	//float radius = _sphereA.Radius + _sphereB.Radius;
	//	半径の和の２乗の計算
	float radiusSquare = radiusSquare * radiusSquare;
	
	//	距離が半径の和より大きいとき
	if (distanceSqare > radiusSquare) {
		//当たっていない
		return false;
	}
	//	当たっている
	return true;
}
