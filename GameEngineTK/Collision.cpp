#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// ���Ƌ��̓����蔻��
/// </summary>
/// <param name="_sphereA">��A</param>
/// <param name="_sphereB">��B</param>
/// <returns>true:�������Ă���Afalse:�������Ă��Ȃ�</returns>
bool CheckSphere2Sphere(const Sphere& _sphereA, const Sphere& _sphereB)
{
	//	A����B�Ɍ������x�N�g��
	Vector3 sub = _sphereB.Center - _sphereA.Center;
	
	//	A��B�̋����̌v�Z
	//float distance = sqrtf(sub.x * sub.x + sub.y * sub.y + sub.z * sub.z);
	//	A��B�̋����̂Q��̌v�Z
	float distanceSqare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	//	���a�̘a�̌v�Z
	//float radius = _sphereA.Radius + _sphereB.Radius;
	//	���a�̘a�̂Q��̌v�Z
	float radiusSquare = radiusSquare * radiusSquare;
	
	//	���������a�̘a���傫���Ƃ�
	if (distanceSqare > radiusSquare) {
		//�������Ă��Ȃ�
		return false;
	}
	//	�������Ă���
	return true;
}
