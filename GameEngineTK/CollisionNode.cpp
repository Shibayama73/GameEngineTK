#include "CollisionNode.h"
using namespace DirectX::SimpleMath;

//========================================================
//CollisionNodeのメンバ関数
//========================================================
void CollisionNode::SetParent(Obj3d * parent)
{
	m_Obj.SetObjParent(parent);
}

//========================================================
//SphereNodeのメンバ関数
//========================================================
SphereNode::SphereNode()
{
	//	半径の初期化(1m)
	m_LocalRadius = 1.0f;
}

void SphereNode::Initialize()
{
	//	デバッグ表示用モデル読込み
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

