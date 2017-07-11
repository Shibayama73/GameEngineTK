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

//	�O�p�`�N���X
class Triangle
{
public:
	//	���_���W
	DirectX::SimpleMath::Vector3 P0;
	DirectX::SimpleMath::Vector3 P1;
	DirectX::SimpleMath::Vector3 P2;
	//	�@���x�N�g��
	DirectX::SimpleMath::Vector3 Normal;

};

bool CheckSphere2Sphere(const Sphere & _sphereA, const Sphere & _sphereB);

// 3�_����O�p�`���\�z
void ComputeTriangle(const DirectX::SimpleMath::Vector3 & _p0, const DirectX::SimpleMath::Vector3 & _p1, const DirectX::SimpleMath::Vector3 & _p2, Triangle * _triangle);

// ���Ɩ@���t���O�p�`�̓�����`�F�b�N
bool CheckSphere2Triangle(const Sphere& _sphere, const Triangle& _triangle, DirectX::SimpleMath::Vector3 *_inter);
// �����i�L���j�Ɩ@���t���O�p�`�̓�����`�F�b�N
bool CheckSegment2Triangle(const Segment & _segment, const Triangle & _triangle, DirectX::SimpleMath::Vector3 * _inter);
