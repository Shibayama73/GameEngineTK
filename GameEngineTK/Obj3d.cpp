#include "Obj3d.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	�ÓI�����o�ϐ��̒�`(����)
//	�f�o�C�X
Microsoft::WRL::ComPtr<ID3D11Device> Obj3d::m_d3dDevice;
//	�f�o�C�X�R���e�L�X�g
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Obj3d::m_d3dContext;
//	�J����
Camera* Obj3d::m_Camera;
//	�ėp�X�e�[�g�ݒ�
std::unique_ptr<DirectX::CommonStates> Obj3d::m_states;
//	�G�t�F�N�g�t�@�N�g��
std::unique_ptr<DirectX::EffectFactory> Obj3d::m_factory;

void Obj3d::InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, Camera * camera)
{
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
	m_Camera = camera;

	//	�ėp�X�e�[�g�ݒ萶��
	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());
	//	�G�t�F�N�g�t�@�N�g���쐬
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	//	�e�N�X�`���t�@�C���w��
	m_factory->SetDirectory(L"Resources");


}

Obj3d::Obj3d()
{
	//	�����o�ϐ��̏�����
//	m_translation = Vector3(0, 0, 30);
	m_scale = Vector3(1, 1, 1);
	m_ObjParent = nullptr;

}

void Obj3d::LoadModel(const wchar_t * fileName)
{
	//	CMO���烂�f���̓ǂݍ���
	//	���f������
//	m_modelSkydome = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/Skydome.cmo", *m_factory);
	//m_modelGround = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/Ground.cmo", *m_factory);
//	m_modelGround = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/Ground200.cmo", *m_factory);
//	m_modelSky = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/sky.cmo", *m_factory);
	//	�e�B�[�|�b�g�̐���
	//m_modelTespot = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/Teapot.cmo", *m_factory);
	//	�@��
	//m_modelHead = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources/head.cmo", *m_factory);
	m_modelHead = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);

}

void Obj3d::Update()
{
	//	���[���h�s��̌v�Z
	//{//	���@�̃��[���h�s����v�Z
	// //	���[��
	//	Matrix rotmatz = Matrix::CreateRotationZ(XMConvertToRadians(0.0f));
	//	//	�s�b�`�i�p�j
	//	Matrix rotmatx = Matrix::CreateRotationX(XMConvertToRadians(0.0f));
	//	//	���[�i���ʊp�j
	//	Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(0.0f) + headAngle);

	//	//	��]�s��̍���(zxy)
	//	Matrix rotmat = rotmatx * rotmatz * rotmaty;

	//	//	���s�ړ�
	//	Matrix transmat = Matrix::CreateTranslation(m_translation);
	//	m_worldHead = rotmat * transmat;

	//}
	{//	���@2�̃��[���h�s����v�Z

	 //	���[���h�s��̌v�Z
		Matrix scalemat = Matrix::CreateScale(m_scale);
		Matrix rotmatZ = Matrix::CreateRotationZ(m_rotation.z);
		Matrix rotmatX = Matrix::CreateRotationX(m_rotation.x);
		Matrix rotmatY = Matrix::CreateRotationY(m_rotation.y);
		Matrix rotmat = rotmatZ * rotmatX * rotmatY;
		Matrix transmat = Matrix::CreateTranslation(m_translation);

		//	���[���h���W�̍���
		m_world = scalemat * rotmat * transmat;
		//	�e�̍s����|����(�q���̍s�񁖐e�̍s��)
		if (m_ObjParent)
		{
			m_world *= m_ObjParent->GetWorld();
		}

	}
}

void Obj3d::Draw()
{
	//	�`��
	//	�ݒ�
	m_d3dContext->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
	m_d3dContext->OMSetDepthStencilState(m_states->DepthNone(), 0);	//	���s
	m_d3dContext->RSSetState(m_states->CullClockwise());

	
	//	���f���̕`��
//	m_modelSkydome->Draw(m_d3dContext.Get(), *m_states, m_world, m_view, m_proj);
	//m_modelGround->Draw(m_d3dContext.Get(), *m_states, m_world, m_view, m_proj);
//	m_modelGround->Draw(m_d3dContext.Get(), *m_states, Matrix::Identity, m_view, m_proj);
	/*for (int i = 0; i < 20; i++)
	{
		m_modelSky->Draw(m_d3dContext.Get(), *m_states, m_worldSky[i], m_view, m_proj);
	}*/


	//for (int i = 0; i < 20; i++)
	//{
	//	//	�e�B�[�|�b�g�̕`��
	//	m_modelTespot->Draw(m_d3dContext.Get(), *m_states, m_worldTeaPot[i], m_view, m_proj);
	//}
	if (m_modelHead)
	{
		//	�@��
		m_modelHead->Draw(m_d3dContext.Get(), *m_states, m_world, m_Camera->GetViewMatrix(), m_Camera->GetProjectionMatrix());
		//m_modelHead->Draw(m_d3dContext.Get(), *m_states, m_worldHead2, m_view, m_proj);
	}

}
