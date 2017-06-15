#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// ‹…‚Æ‹…‚Ì“–‚½‚è”»’è
/// </summary>
/// <param name="_sphereA">‹…A</param>
/// <param name="_sphereB">‹…B</param>
/// <returns>true:“–‚½‚Á‚Ä‚¢‚éAfalse:“–‚½‚Á‚Ä‚¢‚È‚¢</returns>
bool CheckSphere2Sphere(const Sphere& _sphereA, const Sphere& _sphereB)
{
	//	A‚©‚çB‚ÉŒü‚©‚¤ƒxƒNƒgƒ‹
	Vector3 sub = _sphereB.Center - _sphereA.Center;
	
	//	A‚ÆB‚Ì‹——£‚ÌŒvZ
	//float distance = sqrtf(sub.x * sub.x + sub.y * sub.y + sub.z * sub.z);
	//	A‚ÆB‚Ì‹——£‚Ì‚Qæ‚ÌŒvZ
	float distanceSqare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	//	”¼Œa‚Ì˜a‚ÌŒvZ
	//float radius = _sphereA.Radius + _sphereB.Radius;
	//	”¼Œa‚Ì˜a‚Ì‚Qæ‚ÌŒvZ
	float radiusSquare = radiusSquare * radiusSquare;
	
	//	‹——£‚ª”¼Œa‚Ì˜a‚æ‚è‘å‚«‚¢‚Æ‚«
	if (distanceSqare > radiusSquare) {
		//“–‚½‚Á‚Ä‚¢‚È‚¢
		return false;
	}
	//	“–‚½‚Á‚Ä‚¢‚é
	return true;
}
