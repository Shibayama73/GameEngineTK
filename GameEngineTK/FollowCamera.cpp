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

}

//	�X�V
void FollowCamera::Update()
{
	//	�J�����̐ݒ�i���@�ɒǏ]����J�����j
	//	���_�E�Q�Ɠ_�̍��W
	Vector3 eyepos, refpos;

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

