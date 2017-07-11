/// <summary>
/// �RD�I�u�W�F�N�g�̃N���X
/// </summary>
#pragma once

#include <windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>
#include <Effects.h>			//BasicEffect
#include <CommonStates.h>		//CommonStates
#include <SimpleMath.h>			//Vecter3
#include <Model.h>

#include "Camera.h"

class Obj3d
{
public:
	//	�ÓI�����o�֐�
	static void InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext,
		Camera* camera);

private:
	//	�ÓI�����o�ϐ�
	//	�f�o�C�X
	static Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	//	�f�o�C�X�R���e�L�X�g
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext;
	//	�J����
	static Camera* m_Camera;
	//	�ėp�X�e�[�g�ݒ�
	static std::unique_ptr<DirectX::CommonStates> m_states;
	//	�G�t�F�N�g�t�@�N�g��
	static std::unique_ptr<DirectX::EffectFactory> m_factory;



public:
	//	�R���X�g���N�^
	Obj3d();
	//	�R�s�[�R���X�g���N�^
	//Obj3d(const Obj3d& obj);

	//	CMO���f����ǂݍ���
	void LoadModel(const wchar_t* fileName);
	//	�X�V
	void Update();
	//	�`��
	void Draw();

	//	�����o�֐�
	//setter
	//	�X�P�[�����O(XYZ)
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	//	��]�p(XYZ)���t���O���I�t
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation) { m_rotation = rotation; m_UseQuaternion = false; }
	//	��]�p(�N�H�[�^�j�I��)���t���O���I��
	void SetRotationQ(const DirectX::SimpleMath::Quaternion& rotationQ) { m_rotationQ = rotationQ; m_UseQuaternion = true; }
	//	���s�ړ�(XYZ)
	void SetTranslation(const DirectX::SimpleMath::Vector3& translation) { m_translation = translation; }
	//	���[���h�s��
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { m_world = world; }
	//	�e��3D�I�u�W�F�N�g
	void SetObjParent(Obj3d* objParentle) { m_ObjParent = objParentle; }

	//getter
	//	�X�P�[�����O(XYZ)
	const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; }
	//	��]�p(XYZ)
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_rotation; }
	//	���s�ړ�(XYZ)
	const DirectX::SimpleMath::Vector3& GetTranslation() { return m_translation; }
	//	���[���h�s��
	const DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }

private:
	//	�����o�ϐ�
	//	���f��
	//std::unique_ptr<DirectX::Model> m_modelSkydome;	//�V��
	//std::unique_ptr<DirectX::Model> m_modelGround;	//�n��
	//std::unique_ptr<DirectX::Model> m_modelSky;		//��
	//std::unique_ptr<DirectX::Model> m_modelTespot;	//�e�B�[�|�b�g
	std::unique_ptr<DirectX::Model> m_modelHead;	//�@��
	//	�X�P�[�����O(XYZ)
	DirectX::SimpleMath::Vector3 m_scale;
	//	��]�p(XYZ)
	DirectX::SimpleMath::Vector3 m_rotation;
	//	��]�p(�N�H�[�^�j�I��)
	DirectX::SimpleMath::Quaternion m_rotationQ;
	//	���s�ړ�(XYZ)
	//DirectX::SimpleMath::Vector3 m_headPos;		//	���@�̈ړ����W
	DirectX::SimpleMath::Vector3 m_translation;		//	���@�̈ړ����W
	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_world;			//	���@�̃��[���h�s��
	//DirectX::SimpleMath::Matrix m_worldHead2;	//	���@�̃��[���h�s��2
	//	�e��Obj3d�ւ̃|�C���^
	Obj3d* m_ObjParent;
	//	��]���N�H�[�^�j�I���ň����t���O
	bool m_UseQuaternion;

};
