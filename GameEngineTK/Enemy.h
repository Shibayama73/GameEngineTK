//	�G�N���X
#pragma once
#include "DebugCamera.h"
#include "FollowCamera.h"

#include <SimpleMath.h>			//Vecter3
#include "Obj3d.h"
#include "CollisionNode.h"

class Enemy
{
	//	�G�p�[�c
	enum PLAYER_PARTS
	{
		ENEMY_PARTS_TIRE,		//�y��
		ENEMY_PARTS_HEAD,		//����
		ENEMY_PARTS_ARM_RIGHT,	//�E�r
		ENEMY_PARTS_ARM_LEFT,	//���r
		ENEMY_PARTS_TOP,		//����

		ENEMY_PARTS_NUM		//���v
	};

public:
	//	������
	void Initialize();
	//	�X�V
	void Update();
	//	�`��
	void Draw();


	void SetTranslation(DirectX::SimpleMath::Vector3 trans) { m_headPos = trans; }
	void SetRotation(DirectX::SimpleMath::Vector3 angle) { m_headPos = angle; }


	//	���s�ړ�(XYZ)
	const DirectX::SimpleMath::Vector3& GetTranslation() { return m_ObjEnemy[0].GetTranslation(); }
	//	��]�p(XYZ)
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_ObjEnemy[0].GetRotation(); }

	//	�G�{�̂̓����蔻��擾
	const SphereNode& GetCollisionNodeBody() { return m_CollisionNodeBody; }

private:
	//	���@�̈ړ����W
	DirectX::SimpleMath::Vector3 m_headPos;
	//	���@�̃��[���h�s��
	DirectX::SimpleMath::Matrix m_worldHead;
	//	���@�I�u�W�F�N�g
	std::vector<Obj3d> m_ObjEnemy;
	//	���
	bool m_enemyState;
	//	sin�p�̊p�x
	float m_cycle;

	//	�^�C�}�[
	int m_timer;
	//	�ڕW�p�x
	float m_distAngle;
	//	�G�{�̂̓����蔻��
	SphereNode m_CollisionNodeBody;

};

