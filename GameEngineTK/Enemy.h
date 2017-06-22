//	敵クラス
#pragma once
#include "DebugCamera.h"
#include "FollowCamera.h"

#include <SimpleMath.h>			//Vecter3
#include "Obj3d.h"
#include "CollisionNode.h"

class Enemy
{
	//	敵パーツ
	enum PLAYER_PARTS
	{
		ENEMY_PARTS_TIRE,		//土台
		ENEMY_PARTS_HEAD,		//頭体
		ENEMY_PARTS_ARM_RIGHT,	//右腕
		ENEMY_PARTS_ARM_LEFT,	//左腕
		ENEMY_PARTS_TOP,		//頭先

		ENEMY_PARTS_NUM		//合計
	};

public:
	//	初期化
	void Initialize();
	//	更新
	void Update();
	//	描画
	void Draw();


	void SetTranslation(DirectX::SimpleMath::Vector3 trans) { m_headPos = trans; }
	void SetRotation(DirectX::SimpleMath::Vector3 angle) { m_headPos = angle; }


	//	平行移動(XYZ)
	const DirectX::SimpleMath::Vector3& GetTranslation() { return m_ObjEnemy[0].GetTranslation(); }
	//	回転角(XYZ)
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_ObjEnemy[0].GetRotation(); }

	//	敵本体の当たり判定取得
	const SphereNode& GetCollisionNodeBody() { return m_CollisionNodeBody; }

private:
	//	自機の移動座標
	DirectX::SimpleMath::Vector3 m_headPos;
	//	自機のワールド行列
	DirectX::SimpleMath::Matrix m_worldHead;
	//	自機オブジェクト
	std::vector<Obj3d> m_ObjEnemy;
	//	状態
	bool m_enemyState;
	//	sin用の角度
	float m_cycle;

	//	タイマー
	int m_timer;
	//	目標角度
	float m_distAngle;
	//	敵本体の当たり判定
	SphereNode m_CollisionNodeBody;

};

