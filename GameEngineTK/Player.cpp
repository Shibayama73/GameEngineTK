//	�v���C���[�N���X
#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

void Player::Initialize(DirectX::Keyboard* keyboard, DirectX::Keyboard::KeyboardStateTracker* tracker)
{
	//	�L�[�{�[�h�̐���
	m_keyboard = keyboard;
	//	�g���K�[�̐���
	m_tracker = tracker;
	
	//	���@�p�[�c�̓ǂݍ���
	m_ObjPlayer.resize(PLAYER_PARTS_NUM);
	m_ObjPlayer[PLAYER_PARTS_TIRE].LoadModel(L"Resources/tire.cmo");
	m_ObjPlayer[PLAYER_PARTS_HEAD].LoadModel(L"Resources/head.cmo");
	m_ObjPlayer[PLAYER_PARTS_ARM_RIGHT].LoadModel(L"Resources/arm_right.cmo");
	m_ObjPlayer[PLAYER_PARTS_ARM_LEFT].LoadModel(L"Resources/arm_right.cmo");
	m_ObjPlayer[PLAYER_PARTS_TOP].LoadModel(L"Resources/top.cmo");

	//	�e�q�֌W�̍\�z(�q�p�[�c�ɐe��ݒ�)
	m_ObjPlayer[PLAYER_PARTS_HEAD].SetObjParent(&m_ObjPlayer[PLAYER_PARTS_TIRE]);
	m_ObjPlayer[PLAYER_PARTS_ARM_RIGHT].SetObjParent(&m_ObjPlayer[PLAYER_PARTS_HEAD]);
	m_ObjPlayer[PLAYER_PARTS_ARM_LEFT].SetObjParent(&m_ObjPlayer[PLAYER_PARTS_HEAD]);
	m_ObjPlayer[PLAYER_PARTS_TOP].SetObjParent(&m_ObjPlayer[PLAYER_PARTS_HEAD]);

	//	�q�p�[�c�̐e����̃I�t�Z�b�g(���W�̂���)���Z�b�g
	m_ObjPlayer[PLAYER_PARTS_HEAD].SetTranslation(Vector3(0, 0.1f, 0));
	m_ObjPlayer[PLAYER_PARTS_ARM_RIGHT].SetTranslation(Vector3(0.25f, 0.2f, 0));
	m_ObjPlayer[PLAYER_PARTS_ARM_LEFT].SetTranslation(Vector3(-0.25f, 0.2f, 0));
	m_ObjPlayer[PLAYER_PARTS_TOP].SetTranslation(Vector3(0, 0.2f, 0.3f));

	//	�傫��
	m_ObjPlayer[PLAYER_PARTS_TIRE].SetScale(Vector3(2, 2, 2));

	//	���̌���
	m_ObjPlayer[PLAYER_PARTS_ARM_RIGHT].SetRotation(Vector3(0, -30.0f, 0));
	m_ObjPlayer[PLAYER_PARTS_ARM_LEFT].SetRotation(Vector3(0, 30.0f, 0));

	//	��Ԃ̏�����(�I�t)
	m_plsyerState = false;

	//	�e�۔��˃t���O(�I�t)
	m_bulletFlag = false;

	//	�e�۔��˃J�E���g
	m_bulletCount = 0;

	{//	�e�ۗp�����蔻��m�[�h�̐ݒ�
		m_CollisionNodeBullet.Initialize();

		//	�e�p�[�c��ݒ�
		m_CollisionNodeBullet.SetParent(&m_ObjPlayer[PLAYER_PARTS_TOP]);
		m_CollisionNodeBullet.SetTrans(Vector3(0,0.3f,0));
		m_CollisionNodeBullet.SetLocalRadius(0.3f);
	}

	{//	�{�̂̓����蔻��m�[�h�̐ݒ�
		m_CollisionNodeBody.Initialize();

		//	�e�p�[�c�̂�ݒ�
		m_CollisionNodeBody.SetParent(&m_ObjPlayer[PLAYER_PARTS_TIRE]);
		m_CollisionNodeBody.SetTrans(Vector3(0, 0.1f, 0));
		m_CollisionNodeBody.SetLocalRadius(0.1f);

	}

	//	�W�����v�t���O���I�t
	m_isJump = false;

}

void Player::Update()
{
	////	���@�̑傫���̐ݒ�
	//m_cycle += 0.1f;
	//float scale = 1.0f + sinf(m_cycle);
	//m_ObjPlayer[PLAYER_PARTS_HEAD].SetScale(Vector3(scale, scale, scale));

	//	�L�[�{�[�h�̏�Ԏ擾
	Keyboard::State key = m_keyboard->GetState();
	m_tracker->Update(key);

	if (m_tracker->IsKeyPressed(Keyboard::Keys::Z))
	{
		//	�W�����v����
		StartJump();
	}
	//	�W�����v���̂Ƃ�
	if (m_isJump)
	{
		//	�d�͂ɂ�����
		m_Velocity.y -= GRAVITY_ACC;

		if (m_Velocity.y < -JUMP_SPEED_MAX)
		{
			m_Velocity.y = -JUMP_SPEED_MAX;
		}
	}

	{//	���x�ɂ��ړ�
		Vector3 trans = GetTranslation();
		trans += m_Velocity;
		SetTranslation(trans);
	}

	//	X�L�[�������ꂽ�Ƃ�
	if (m_tracker->pressed.X)
	{
		//	���@�̏�Ԃ��I�t�̂Ƃ�
		if (m_plsyerState == false)
		{
			//	�ό`����
			m_ObjPlayer[PLAYER_PARTS_HEAD].SetTranslation(Vector3(0, 0.6f, 0));
			m_ObjPlayer[PLAYER_PARTS_HEAD].SetRotation(Vector3(1.5f, 0, 0));
			m_ObjPlayer[PLAYER_PARTS_ARM_RIGHT].SetRotation(Vector3(0, 1.5f, -1.8f));
			m_ObjPlayer[PLAYER_PARTS_ARM_LEFT].SetRotation(Vector3(0, -1.5f, 1.8f));
			m_ObjPlayer[PLAYER_PARTS_TOP].SetTranslation(Vector3(0, 0, -0.1f));
			m_ObjPlayer[PLAYER_PARTS_TOP].SetRotation(Vector3(5.0f, 0, 0));

			//	��Ԃ��I��
			m_plsyerState = true;
		}
		else
		{
			//	�q�p�[�c�̐e����̃I�t�Z�b�g(���W�̂���)���Z�b�g
			m_ObjPlayer[PLAYER_PARTS_HEAD].SetTranslation(Vector3(0, 0.1f, 0));
			m_ObjPlayer[PLAYER_PARTS_ARM_RIGHT].SetTranslation(Vector3(0.25f, 0.2f, 0));
			m_ObjPlayer[PLAYER_PARTS_ARM_LEFT].SetTranslation(Vector3(-0.25f, 0.2f, 0));
			m_ObjPlayer[PLAYER_PARTS_TOP].SetTranslation(Vector3(0, 0.2f, 0.3f));

			//	���̌���
			m_ObjPlayer[PLAYER_PARTS_ARM_RIGHT].SetRotation(Vector3(0, -30.0f, 0));
			m_ObjPlayer[PLAYER_PARTS_ARM_LEFT].SetRotation(Vector3(0, 30.0f, 0));

			//	��Ԃ��I�t
			m_plsyerState = false;
		}
	}

	//	W�L�[��������Ă�Ƃ��O�i
	if (key.W)
	{
		//	�ړ��x�N�g��(Z���W�O�i)
		Vector3 moveV(0, 0, -0.15f);
		//	��]
		float angle = m_ObjPlayer[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		//	�ړ��x�N�g�������@�̊p�x����]������
		moveV = Vector3::TransformNormal(moveV, rotmat);
		//moveV = Vector3::TransformNormal(moveV, m_worldHead);
		//Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(headAngle));
		//moveV = Vector3::TransformNormal(moveV, rotmaty);
		Vector3 pos = m_ObjPlayer[0].GetTranslation();
		m_ObjPlayer[0].SetTranslation(pos + moveV);

		//	���@�̍��W���ړ�
		m_headPos += moveV;

	}
	//	S�L�[��������Ă�Ƃ����
	if (key.S)
	{
		//	�ړ��x�N�g��(Z���W���)
		Vector3 moveV(0, 0, 0.1f);
		//	��]
		float angle = m_ObjPlayer[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		//	�ړ��x�N�g�������@�̊p�x����]������
		moveV = Vector3::TransformNormal(moveV, rotmat);
		Vector3 pos = m_ObjPlayer[0].GetTranslation();
		m_ObjPlayer[0].SetTranslation(pos + moveV);

		//	�ړ��x�N�g�������@�̊p�x����]������
		//	moveV = Vector3::TransformNormal(moveV, m_worldHead);
		//Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(headAngle));
		//moveV = Vector3::TransformNormal(moveV, rotmaty);

		//	���@�̍��W���ړ�
		m_headPos += moveV;

	}
	//	A�L�[��������Ă�Ƃ�������
	if (key.A)
	{
		//	���ɐ��񂷂�
		float angle = m_ObjPlayer[0].GetRotation().y;
		m_ObjPlayer[0].SetRotation(Vector3(0, angle + 0.03f, 0));

		//headAngle += 0.1f;
		////	�ړ��x�N�g����(X���W���)
		//Vector3 moveV(-0.1f, 0, 0);
		////	���@�̍��W���ړ�
		//m_headPos += moveV;
	}
	//	D�L�[��������Ă�Ƃ��E����
	if (key.D)
	{
		//	�E�ɐ��񂷂�
		float angle = m_ObjPlayer[0].GetRotation().y;
		m_ObjPlayer[0].SetRotation(Vector3(0, angle - 0.03f, 0));

		//headAngle -= 0.1f;
		////	�ړ��x�N�g����(X���W�O�i)
		//Vector3 moveV(0.1f, 0, 0);
		////	���@�̍��W���ړ�
		//m_headPos += moveV;
	}

	//	Space�L�[�������ꂽ��
	if(key.Space)
	{	
		//	�e�۔��˃t���O���I��
		m_bulletFlag = true;
	}

	//	�e�۔��˃t���O���I���̂Ƃ�
	if (m_bulletFlag)
	{
		m_bulletCount++;
		//	3�b�o������
		if (m_bulletCount  >= 180) {
			m_bulletCount = 0;
			//	�e�۔��˃t���O���I�t
			m_bulletFlag = false;
		}

		//	�e�ۃp�[�c�𔭎�
		FireBullet();

		//	�e�ۃp�[�c�̍��W�̈ړ�
		Vector3 pos = m_ObjPlayer[PLAYER_PARTS_TOP].GetTranslation();
		//	�e�ۃp�[�c�̑O�i
		m_ObjPlayer[PLAYER_PARTS_TOP].SetTranslation(pos + m_BulletVel);
	}
	//	�e�۔��˃t���O���I�t�̂Ƃ�
	else {
		//	�e�ۃp�[�c�����Ƃɖ߂�
		ResetBuller();
	}


	this->Calc();

	//	�f�o�b�O�p
	//FireBullet();
	
	

}

void Player::Draw()
{
	//	���@�I�u�W�F�N�g�̕`��
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin();
		it != m_ObjPlayer.end();
		it++)
	{
		it->Draw();
	}
	//	�e�ۗp�����蔻��m�[�h
	m_CollisionNodeBullet.Draw();
	//	�{�̗p�����蔻��m�[�h
	m_CollisionNodeBody.Draw();

}

void Player::FireBullet()
{
	//	���˂���p�[�c�̃��[���h�s����擾
	Matrix worldm = m_ObjPlayer[PLAYER_PARTS_TOP].GetWorld();

	//	���o�����������܂��Ă����ϐ�
	Vector3 scale;			//���[���h�X�P�[�����O
	Quaternion rotation;	//���[���h��]
	Vector3 translation;	//���[���h���W

	//	���[���h�s�񂩂�e�v�f�𒊏o
	worldm.Decompose(scale, rotation, translation);

	//	�e�p�[�c���番���A�Ɨ�������
	m_ObjPlayer[PLAYER_PARTS_TOP].SetObjParent(nullptr);
	m_ObjPlayer[PLAYER_PARTS_TOP].SetScale(scale);
	m_ObjPlayer[PLAYER_PARTS_TOP].SetRotationQ(rotation);
	m_ObjPlayer[PLAYER_PARTS_TOP].SetTranslation(translation);

	//	�e�ۃp�[�c�̑��x��ݒ�
	m_BulletVel = Vector3(0, 0, -0.3f);
	//	�p�[�c�̌����ɍ��킹�đ��x�x�N�g������]
	m_BulletVel = Vector3::Transform(m_BulletVel, rotation);

}

//	�e�ۂ��ő���(���Z�b�g)
void Player::ResetBuller()
{
	//	�e�q�֌W�̍č\�z(�q�p�[�c�ɐe��ݒ�)
	m_ObjPlayer[PLAYER_PARTS_TOP].SetObjParent(&m_ObjPlayer[PLAYER_PARTS_HEAD]);

	//	�q�p�[�c�̐e����̃I�t�Z�b�g(���W�̂���)�����Z�b�g
	m_ObjPlayer[PLAYER_PARTS_TOP].SetTranslation(Vector3(0, 0.2f, 0.3f));

	//	��]�p�̃��Z�b�g
	m_ObjPlayer[PLAYER_PARTS_TOP].SetRotation(Vector3(0, 0, 0));
	//	�傫���̃��Z�b�g
	m_ObjPlayer[PLAYER_PARTS_TOP].SetScale(Vector3(1, 1, 1));

}

void Player::Calc()
{
	//	���@�I�u�W�F�N�g�̍X�V
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin();
		it != m_ObjPlayer.end();
		it++)
	{
		it->Update();
	}

	//	�e�ۗp�����蔻��m�[�h
	m_CollisionNodeBullet.Update();
	//	�{�̗p�̓����蔻��m�[�h
	m_CollisionNodeBody.Update();

}

/// <summary>
/// �W�����v���J�n
/// </summary>
void Player::StartJump()
{
	if (!m_isJump)
	{
		m_Velocity.y = JUMP_SPEED_FIRST;
		m_isJump = true;
	}
}

/// <summary>
/// �������J�n
/// </summary>
void Player::StartFall()
{
	if (!m_isJump)
	{
		m_Velocity.y = 0;
		m_isJump = true;
	}
}

/// <summary>
/// �������I��
/// </summary>
void Player::StopJump()
{
	m_isJump = false;
	m_Velocity = Vector3::Zero;
}
