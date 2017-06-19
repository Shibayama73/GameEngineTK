#include "CollisionNode.h"
using namespace DirectX::SimpleMath;

//========================================================
//CollisionNode�̃����o�֐�
//========================================================
void CollisionNode::SetParent(Obj3d * parent)
{
	m_Obj.SetObjParent(parent);
}

//========================================================
//SphereNode�̃����o�֐�
//========================================================
SphereNode::SphereNode()
{
	//	���a�̏�����(1m)
	m_LocalRadius = 1.0f;
}

void SphereNode::Initialize()
{
	//	�f�o�b�O�\���p���f���Ǎ���
	m_Obj.LoadModel(L"Resources/sphereNode.cmo");
}

void SphereNode::Update()
{
	m_Obj.SetTranslation(m_Trans);
	m_Obj.SetScale(Vector3(m_LocalRadius));

	m_Obj.Update();
}

void SphereNode::Draw()
{
	m_Obj.Draw();
}

