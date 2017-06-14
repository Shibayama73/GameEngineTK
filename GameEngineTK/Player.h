//	�v���C���[�N���X
#pragma once
#include "DebugCamera.h"
#include "FollowCamera.h"

#include <SimpleMath.h>			//Vecter3
#include "Obj3d.h"

class Player
{
	//	�v���C���[�p�[�c
	enum PLAYER_PARTS
	{
		PLAYER_PARTS_TIRE,		//�y��
		PLAYER_PARTS_HEAD,		//����
		PLAYER_PARTS_ARM_RIGHT,	//�E�r
		PLAYER_PARTS_ARM_LEFT,	//���r
		PLAYER_PARTS_TOP,		//����

		PLAYER_PARTS_NUM		//���v
	};

public:
	//	������
	void Initialize(DirectX::Keyboard* keyboard, DirectX::Keyboard::KeyboardStateTracker* tracker);
	//	�X�V
	void Update();
	//	�`��
	void Draw();
	//	�e�ۂ𔭎�
	void FireBullet();
	//	�e�ۂ��ő���(���Z�b�g)
	void ResetBuller();

	//	���s�ړ�(XYZ)
	const DirectX::SimpleMath::Vector3& GetTranslation() { return m_ObjPlayer[0].GetTranslation(); }
	//	��]�p(XYZ)
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_ObjPlayer[0].GetRotation(); }

private:
	DirectX::Keyboard* m_keyboard;						//�L�[�{�[�h
	DirectX::Keyboard::KeyboardStateTracker* m_tracker;	//�g���K�[

	//	���@�̈ړ����W
	DirectX::SimpleMath::Vector3 m_headPos;
	//	���@�̃��[���h�s��
	DirectX::SimpleMath::Matrix m_worldHead;
	//	���@�I�u�W�F�N�g
	std::vector<Obj3d> m_ObjPlayer;
	//	���
	bool m_plsyerState;
	//	sin�p�̊p�x
	float m_cycle;
	//	�e�ۂ̑��x�x�N�g��
	DirectX::SimpleMath::Vector3 m_BulletVel;
	//	�e�۔��˃t���O
	bool m_bulletFlag;
	//	�e�۔��˃J�E���g
	int m_bulletCount;

};
