/// <summary>
/// �J�����𐧌䂷��N���X
/// </summary>
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>

class Camera
{
public:
	Camera(int Width,int Height);
	virtual ~Camera();
	//	�X�V
	void Update();
	//	�r���[�s��̎擾
	DirectX::SimpleMath::Matrix GetViewMatrix();
	//	�ˉe�s��̎擾
	DirectX::SimpleMath::Matrix GetProjectionMatrix();
	//	���_���W�̃Z�b�g
	void SetEyePos(DirectX::SimpleMath::Vector3 eyepos);
	//	�����_�E�Q�Ɠ_�Z�b�g
	void SetRefPos(DirectX::SimpleMath::Vector3 refpos);
	//	�J�����̌����̃Z�b�g
	void SetUpvec(DirectX::SimpleMath::Vector3 upvec);
	//	����p�̃Z�b�g
	void SetFovY(float fovY);
	//	�A�X�y�N�g��̃Z�b�g
	void SetAspect(float aspect);
	//	�j�A�N���b�v�̃Z�b�g
	void SetNearclip(float nearclip);
	//	�t�@�[�N���b�v�̃Z�b�g
	void SetFarclip(float farclip);


protected:
	//	�J�����̈ʒu�i���_���W�j
	DirectX::SimpleMath::Vector3 m_eyepos;
	//	�J�����̌��Ă����i�����_�E�Q�Ɠ_�j
	DirectX::SimpleMath::Vector3 m_refpos;
	//	�J�����̏�����x�N�g��
	DirectX::SimpleMath::Vector3 m_upvec;
	//	������������p
	float m_fovY;
	//	�A�X�y�N�g��i��ʔ䗦�j
	float m_aspect;
	//	�j�A�N���b�v�i��O�̕\�����E�����j
	float m_nearclip;
	//	�t�@�[�N���b�v�i���̕\�����E�����j
	float m_farclip;
	//	�r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	//	�ˉe�s��
	DirectX::SimpleMath::Matrix m_proj;

};

