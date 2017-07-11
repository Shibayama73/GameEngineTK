/// <summary>
/// 当たり判定ノード
/// </summary>
#pragma once

#include "Obj3d.h"
#include "Collision.h"

// 当たり判定ノードクラス
class CollisionNode
{
public:
	//	デバッグ表示フラグ取得
	static bool GetDebugVisible() { return m_DebugVisible; }
	//	デバッグ表示フラグセット
	static void SetDebugVisible(bool visible) { m_DebugVisible = visible; }

protected:
	//	デバッグフラグ表示ON
	static bool m_DebugVisible;

public:
	//	初期化
	virtual void Initialize() = 0;
	//	更新
	virtual void Update() = 0;
	//	描画
	virtual void Draw() = 0;

	//	親子関係構築
	void SetParent(Obj3d* parent);
	//	親からのオフセット
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { m_Trans = trans; }


protected:
	//	デバッグ表示用オブジェクト
	Obj3d m_Obj;

	//	親からのオフセット
	DirectX::SimpleMath::Vector3 m_Trans;

};

//	球当たり判定ノードクラス
class SphereNode :public CollisionNode, public Sphere
{
public:
	SphereNode();
	//	初期化
	void Initialize();
	//	更新
	void Update();
	//	描画
	void Draw();

	//	ローカル半径のセット
	void SetLocalRadius(float radius) { m_LocalRadius = radius; }

protected:
	//	ローカル半径
	float m_LocalRadius;

};
