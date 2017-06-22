//	�v���C���[�N���X
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

void Enemy::Initialize()
{
	//	���@�p�[�c�̓ǂݍ���
	m_ObjEnemy.resize(ENEMY_PARTS_NUM);
	m_ObjEnemy[ENEMY_PARTS_TIRE].LoadModel(L"Resources/tire.cmo");
	m_ObjEnemy[ENEMY_PARTS_HEAD].LoadModel(L"Resources/head.cmo");
	m_ObjEnemy[ENEMY_PARTS_ARM_RIGHT].LoadModel(L"Resources/arm_right.cmo");
	m_ObjEnemy[ENEMY_PARTS_ARM_LEFT].LoadModel(L"Resources/arm_right.cmo");
	m_ObjEnemy[ENEMY_PARTS_TOP].LoadModel(L"Resources/top.cmo");

	//	�e�q�֌W�̍\�z(�q�p�[�c�ɐe��ݒ�)
	m_ObjEnemy[ENEMY_PARTS_HEAD].SetObjParent(&m_ObjEnemy[ENEMY_PARTS_TIRE]);
	m_ObjEnemy[ENEMY_PARTS_ARM_RIGHT].SetObjParent(&m_ObjEnemy[ENEMY_PARTS_HEAD]);
	m_ObjEnemy[ENEMY_PARTS_ARM_LEFT].SetObjParent(&m_ObjEnemy[ENEMY_PARTS_HEAD]);
	m_ObjEnemy[ENEMY_PARTS_TOP].SetObjParent(&m_ObjEnemy[ENEMY_PARTS_HEAD]);

	//	�q�p�[�c�̐e����̃I�t�Z�b�g(���W�̂���)���Z�b�g
	m_ObjEnemy[ENEMY_PARTS_HEAD].SetTranslation(Vector3(0, 0.1f, 0));
	m_ObjEnemy[ENEMY_PARTS_ARM_RIGHT].SetTranslation(Vector3(0.25f, 0.2f, 0));
	m_ObjEnemy[ENEMY_PARTS_ARM_LEFT].SetTranslation(Vector3(-0.25f, 0.2f, 0));
	m_ObjEnemy[ENEMY_PARTS_TOP].SetTranslation(Vector3(0, 0.2f, 0.3f));

	//	�傫��
	m_ObjEnemy[ENEMY_PARTS_TIRE].SetScale(Vector3(2, 2, 2));

	//	���̌���
	m_ObjEnemy[ENEMY_PARTS_ARM_RIGHT].SetRotation(Vector3(0, -30.0f, 0));
	m_ObjEnemy[ENEMY_PARTS_ARM_LEFT].SetRotation(Vector3(0, 30.0f, 0));

	//	��Ԃ̏�����(�I�t)
	//m_enemyState = false;
	m_deathFlag = false;

	//	�����ʒu��ݒ�
	Vector3 pos;
	pos.x = rand() % 10;
	pos.z = rand() % 10;

	SetTranslation(pos);

	//	������
	m_timer = 0;
	m_distAngle = 0;

	{//	�G�{�̂̓����蔻��m�[�h�̐ݒ�
		m_CollisionNodeBody.Initialize();

		//	�e�p�[�c�̂�ݒ�
		m_CollisionNodeBody.SetParent(&m_ObjEnemy[ENEMY_PARTS_HEAD]);
		m_CollisionNodeBody.SetTrans(Vector3(0, 0.1f, 0));
		m_CollisionNodeBody.SetLocalRadius(0.5f);

	}


}

void Enemy::Update()
{
	m_timer--;
	if (m_timer < 0)
	{
		m_timer = 60;

		//	�ڕW�p�������_����
		//-0.5�`0.5
		float rnd = (float)rand() / RAND_MAX - 0.5f;
		//-90�`90
		rnd *= 180.0f;
		//	���W�A���ɕϊ�
		rnd = XMConvertToRadians(rnd);

		m_distAngle += rnd;
	}

	//Vector3 rot = GetRotation();
	////	���
	//float angle = m_distAngle - rot.y;
	//rot.y *= angle*0.01f;

	Vector3 rot = m_ObjEnemy[ENEMY_PARTS_TIRE].GetRotation();
	float angle = m_distAngle - rot.y;
	rot.y += angle*0.01f;
	m_ObjEnemy[ENEMY_PARTS_TIRE].SetRotation(rot);


	//SetRotation(Vector3(0, m_distAngle, 0));

	////	���@�̑傫���̐ݒ�
	//m_cycle += 0.1f;
	//float scale = 1.0f + sinf(m_cycle);
	//m_ObjPlayer[PLAYER_PARTS_HEAD].SetScale(Vector3(scale, scale, scale));

	////	���@�̏�Ԃ��I�t�̂Ƃ�
	//if (m_enemyState == false)
	//{
	//	//	�ό`����
	//	m_ObjEnemy[ENEMY_PARTS_HEAD].SetTranslation(Vector3(0, 0.6f, 0));
	//	m_ObjEnemy[ENEMY_PARTS_HEAD].SetRotation(Vector3(1.5f, 0, 0));
	//	m_ObjEnemy[ENEMY_PARTS_ARM_RIGHT].SetRotation(Vector3(0, 1.5f, -1.8f));
	//	m_ObjEnemy[ENEMY_PARTS_ARM_LEFT].SetRotation(Vector3(0, -1.5f, 1.8f));
	//	m_ObjEnemy[ENEMY_PARTS_TOP].SetTranslation(Vector3(0, 0, -0.1f));
	//	m_ObjEnemy[ENEMY_PARTS_TOP].SetRotation(Vector3(5.0f, 0, 0));

	//	//	��Ԃ��I��
	//	m_enemyState = true;
	//}
	//else
	//{
	//	//	�q�p�[�c�̐e����̃I�t�Z�b�g(���W�̂���)���Z�b�g
	//	m_ObjEnemy[ENEMY_PARTS_HEAD].SetTranslation(Vector3(0, 0.1f, 0));
	//	m_ObjEnemy[ENEMY_PARTS_ARM_RIGHT].SetTranslation(Vector3(0.25f, 0.2f, 0));
	//	m_ObjEnemy[ENEMY_PARTS_ARM_LEFT].SetTranslation(Vector3(-0.25f, 0.2f, 0));
	//	m_ObjEnemy[ENEMY_PARTS_TOP].SetTranslation(Vector3(0, 0.2f, 0.3f));

	//	//	���̌���
	//	m_ObjEnemy[ENEMY_PARTS_ARM_RIGHT].SetRotation(Vector3(0, -30.0f, 0));
	//	m_ObjEnemy[ENEMY_PARTS_ARM_LEFT].SetRotation(Vector3(0, 30.0f, 0));

	//	//	��Ԃ��I�t
	//	m_enemyState = false;
	//}

	Vector3 trans = m_ObjEnemy[ENEMY_PARTS_TIRE].GetTranslation();

	//	�ړ��x�N�g��(Z���W�O�i)
	Vector3 move(0, 0, -0.1f);
	Vector3 rotv = m_ObjEnemy[ENEMY_PARTS_TIRE].GetRotation();

	//	��]
	//float angle = m_ObjEnemy[0].GetRotation().y;
	Matrix rotm = Matrix::CreateRotationY(rotv.y);
	//	�ړ��x�N�g�������@�̊p�x����]������
	move = Vector3::TransformNormal(move, rotm);
	//Vector3 pos = m_ObjEnemy[0].GetTranslation();
	//m_ObjEnemy[0].SetTranslation(pos + rotm);

	//	���@�̍��W���ړ�
	trans += move;

	m_ObjEnemy[ENEMY_PARTS_TIRE].SetTranslation(trans);

	//{//	�ړ��x�N�g��(Z���W���)
	//	Vector3 moveV(0, 0, 0.1f);
	//	//	��]
	//	float angle = m_ObjEnemy[0].GetRotation().y;
	//	Matrix rotmat = Matrix::CreateRotationY(angle);
	//	//	�ړ��x�N�g�������@�̊p�x����]������
	//	moveV = Vector3::TransformNormal(moveV, rotmat);
	//	Vector3 pos = m_ObjEnemy[0].GetTranslation();
	//	m_ObjEnemy[0].SetTranslation(pos + moveV);

	//	//	�ړ��x�N�g�������@�̊p�x����]������
	//	//	moveV = Vector3::TransformNormal(moveV, m_worldHead);
	//	//Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(headAngle));
	//	//moveV = Vector3::TransformNormal(moveV, rotmaty);

	//	//	���@�̍��W���ړ�
	//	m_headPos += moveV;
	//}
	//
	//	//	���ɐ��񂷂�
	//	float angle = m_ObjEnemy[0].GetRotation().y;
	//	m_ObjEnemy[0].SetRotation(Vector3(0, angle + 0.03f, 0));

	//	//headAngle += 0.1f;
	//	////	�ړ��x�N�g����(X���W���)
	//	//Vector3 moveV(-0.1f, 0, 0);
	//	////	���@�̍��W���ړ�
	//	//m_headPos += moveV;
	//}
	//	//	�E�ɐ��񂷂�
	//	float angle = m_ObjEnemy[0].GetRotation().y;
	//	m_ObjEnemy[0].SetRotation(Vector3(0, angle - 0.03f, 0));


	//	���@�I�u�W�F�N�g�̍X�V
	for (std::vector<Obj3d>::iterator it = m_ObjEnemy.begin();
		it != m_ObjEnemy.end();
		it++)
	{
		it->Update();
	}

	//	�G�{�̗p�̓����蔻��m�[�h
	m_CollisionNodeBody.Update();

}

void Enemy::Draw()
{
	//	���@�I�u�W�F�N�g�̕`��
	for (std::vector<Obj3d>::iterator it = m_ObjEnemy.begin();
		it != m_ObjEnemy.end();
		it++)
	{
		it->Draw();
	}

	//	�G�{�̗p�����蔻��m�[�h
	m_CollisionNodeBody.Draw();
}

//=============�������=======================//

bool Enemy::GetDeath()
{
	return m_deathFlag;
}

void Enemy::SetDeath()
{
	m_deathFlag = true;

	m_ObjEnemy.pop_back();
}
