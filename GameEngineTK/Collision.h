//	�Փ˔��胉�C�u����

#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>

//	���N���X
class Sphere
{
public:
	//	���S���W
	DirectX::SimpleMath::Vector3 Center;
	//	���a
	float Radius;
	//	�R���X�g���N�^
	Sphere() {
		Radius = 1.0f;
	}
};

//	�����N���X
class Segment
{
public:
	//	�n�_���W
	DirectX::SimpleMath::Vector3 Start;
	//	�I�_���W
	DirectX::SimpleMath::Vector3 End;
};

bool CheckSphere2Sphere(const Sphere & _sphereA, const Sphere & _sphereB);
