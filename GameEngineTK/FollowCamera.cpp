#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	�ÓI�����o�ϐ��̏�����
const float FollowCamera::CAMERA_DISTANCE = 5.0f;

//	�R���X�g���N�^
FollowCamera::FollowCamera(int width, int height)
	:Camera(width, height)
{
	//	������===============================
	//	�Ǐ]�Ώۂ̍��W
	m_targetPos = Vector3(0, 0, 0);
	//	�Ǐ]�Ώۂ̉�]�p
	m_targetAngle = 0.0f;
	//	�L�[�{�[�h
	m_keyboard = nullptr;
	//	FPS�t���O
	m_isFPS = false;
	//	�v���C���[
//	m_player = nullptr;

}

//	�X�V
void FollowCamera::Update()
{
	//	�L�[�{�[�h�̏�Ԏ擾
	Keyboard::State keystate = m_keyboard->GetState();
	//	�L�[�{�[�h�g���b�J�[�̎擾
	m_keyboardTracker.Update(keystate);

	//	C�L�[�������ꂽ��
	if (m_keyboardTracker.IsKeyPressed(Keyboard::Keyboard::C)) {
		//	�J�����̃t���O�؂�ւ�
		m_isFPS = !m_isFPS;
	}

//	if (m_player)
//	{
//		this->SetTargetPos(m_player->GetTranslation());		//���@�̍��W��ǔ�
//		this->SetTargetAngle(m_player->GetRotation().y);	//���@��y���W��]�p��ǔ�
//	}

	//	�J�����̐ݒ�i���@�ɒǏ]����J�����j
	//	���_�E�Q�Ɠ_�̍��W
	Vector3 eyepos, refpos;

	if(m_isFPS)
	//FPS�J������TPS�J�����͎Q�Ɠ_�ƃJ�����̍��W�v�Z�̏��Ԃ����ւ���̂�
	{//	FPS�J�����̏���
		Vector3 position;
		//	�J�������W�̌v�Z
		position = m_targetPos + Vector3(0, 0.2f, 0);

		//	���@����J�����܂ł̋���
		Vector3 cameraV(0, 0, -CAMERA_DISTANCE);

		//	���@������ɉ�荞�ނ��߂̉�]�s��
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		//	�J�����ւ̃x�N�g������]������
		cameraV = Vector3::TransformNormal(cameraV, rotmat);

		//	�����i�񂾐掋�_���W�̌v�Z
		eyepos = position + cameraV * 0.1f;
		//	��ɐi�񂾎Q�Ɠ_���W�̌v�Z
		refpos = position + cameraV;

	}

	else
	{//	TPS�J�����̏���
		//	�Q�Ɠ_���W�̌v�Z
		refpos = m_targetPos + Vector3(0, 2.0f, 0);
		//	���@����J�����܂ł̋���
		Vector3 cameraV(0, 0, CAMERA_DISTANCE);

		//	���@������ɉ�荞�ނ��߂̉�]�s��
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		//	�J�����ւ̃x�N�g������]������
		cameraV = Vector3::TransformNormal(cameraV, rotmat);

		//	�J�������W���v�Z
		eyepos = refpos + cameraV;


		//�S���Ђ��̋���
		//	���_�����݈ʒu�����Ԃ���
		//	�O��̎��_ + (���_�̖ڕW�_ - �O��̎��_) * 0.05f
		eyepos = m_eyepos + (eyepos - m_eyepos)*0.03f;

		//	�J�����̎Q�Ɠ_�����݈ʒu�����Ԃ���
		//	�O��̎Q�Ɠ_ + (�Q�Ɠ_�̖ڕW�_ - �O��̎Q�Ɠ_) * 0.05f
		refpos = m_refpos + (refpos - m_refpos)*0.3f;

	}


	//	�J�����ɏ���n��
	this->SetRefPos(refpos);
	this->SetEyePos(eyepos);

	//	�J����(���N���X)�̍X�V
	Camera::Update();

}

//	�Ǐ]�Ώۂ̍��W���Z�b�g
void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetPos)
{
	m_targetPos = targetPos;
}

//	�Ǐ]�Ώۂ̉�]�p���Z�b�g
void FollowCamera::SetTargetAngle(float targetAngle)
{
	m_targetAngle = targetAngle;
}

//	�L�[�{�[�h���Z�b�g
void FollowCamera::SetKeyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}
//
////	�v���C���[���Z�b�g
//void FollowCamera::SetPlayer(Player * player)
//{
//	m_player = player;
//}

