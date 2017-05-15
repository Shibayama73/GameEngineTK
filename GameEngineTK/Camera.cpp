#include "pch.h"
#include "Camera.h"


using namespace DirectX;
using Microsoft::WRL::ComPtr;
using namespace DirectX::SimpleMath;


Camera::Camera(int Width, int Height)
{
	//	������==========================================
	//	�J�����̈ʒu�i���_���W�j
	m_eyepos = Vector3(0, 0, 5.0f);
	//	�J�����̌��Ă����i�����_�E�Q�Ɠ_�j
	m_refpos = Vector3(0, 0, 10);
	//	�J�����̏�����x�N�g��
	m_upvec = Vector3(0, 1.0f, 0);
	//	������������p
	m_fovY = XMConvertToRadians(60.0f);
	//	�A�X�y�N�g��i��ʔ䗦�j
	m_aspect = (float)Width / Height;
	//	�j�A�N���b�v�i��O�̕\�����E�����j
	m_nearclip = 0.1f;
	//	�t�@�[�N���b�v�i���̕\�����E�����j
	m_farclip = 1000.0f;

	//=======================================================
	//	�r���[�s��̐���
	m_upvec.Normalize();	//������1�ɒ�������
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	//	�ˉe�s��̐���
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);

}

Camera::~Camera()
{
}

//	�X�V
void Camera::Update()
{
	//	�r���[�s��̐���
	m_upvec.Normalize();	//������1�ɒ�������
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	//	�ˉe�s��̐���
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);

}

//	�r���[�s��̎擾
DirectX::SimpleMath::Matrix Camera::GetViewMatrix()
{
	//	�r���[�s��̐���
	m_upvec.Normalize();	//������1�ɒ�������
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	return m_view;
}

//	�ˉe�s��̎擾
DirectX::SimpleMath::Matrix Camera::GetProjectionMatrix()
{
	//	�ˉe�s��̐���
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);

	return m_proj;
}

//	���_���W�̃Z�b�g
void Camera::SetEyePos(DirectX::SimpleMath::Vector3 eyepos)
{
	//	���_���W��eyepos
	m_eyepos = eyepos;
}

void Camera::SetRefPos(DirectX::SimpleMath::Vector3 refpos)
{
	m_refpos = refpos;
}

void Camera::SetUpvec(DirectX::SimpleMath::Vector3 upvec)
{
	m_upvec = upvec;
}

void Camera::SetFovY(float fovY)
{
	m_fovY = fovY;
}

void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}

void Camera::SetNearclip(float nearclip)
{
	m_nearclip = nearclip;
}

void Camera::SetFarclip(float farclip)
{
	m_farclip = farclip;
}

