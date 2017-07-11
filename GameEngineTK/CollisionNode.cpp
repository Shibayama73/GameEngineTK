#include "CollisionNode.h"
using namespace DirectX::SimpleMath;

//	メンバ変数実態
bool CollisionNode::m_DebugVisible = true;

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

	{//	判定球の要素を計算
		const Matrix worldm = m_Obj.GetWorld();

		//	モデル座標系での中心点
		Vector3 center(0, 0, 0);
		//	モデル座標系での右端の点
		Vector3 right(1, 0, 0);

		//	ワールド座標系に変換
		center = Vector3::Transform(center, worldm);
		right = Vector3::Transform(right, worldm);

		//	判定球の要素を代入
		Sphere::Center = center;
		Sphere::Radius = Vector3::Distance(center, right);

	}
}

void SphereNode::Draw()
{
	m_Obj.Draw();
}

