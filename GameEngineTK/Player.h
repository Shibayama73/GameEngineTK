//	プレイヤークラス
#pragma once
#include "DebugCamera.h"
#include "FollowCamera.h"

#include <SimpleMath.h>			//Vecter3
#include "Obj3d.h"
#include "CollisionNode.h"

class Player
{
public:
	//	重力加速度
	const float GRAVITY_ACC = 0.03f;
	//	ジャンプ初速度
	const float JUMP_SPEED_FIRST = 0.5f;
	//	ジャンプ速度制限
	const float JUMP_SPEED_MAX = 0.3f;


	//	プレイヤーパーツ
	enum PLAYER_PARTS
	{
		PLAYER_PARTS_TIRE,		//土台
		PLAYER_PARTS_HEAD,		//頭体
		PLAYER_PARTS_ARM_RIGHT,	//右腕
		PLAYER_PARTS_ARM_LEFT,	//左腕
		PLAYER_PARTS_TOP,		//頭先

		PLAYER_PARTS_NUM		//合計
	};

public:
	//	初期化
	void Initialize(DirectX::Keyboard* keyboard, DirectX::Keyboard::KeyboardStateTracker* tracker);
	//	更新
	void Update();
	//	描画
	void Draw();
	//	弾丸を発射
	void FireBullet();
	//	弾丸を最装着(リセット)
	void ResetBuller();

	void Calc();

	//	ジャンプを開始する
	void StartJump();
	//	落下を開始する
	void StartFall();
	//	落下を終了する
	void StopJump();

	void SetTranslation(DirectX::SimpleMath::Vector3 trans) { m_ObjPlayer[0].SetTranslation(trans); }
	void SetRotation(DirectX::SimpleMath::Vector3 angle) { m_ObjPlayer[0].SetRotation(angle); }

	//	平行移動(XYZ)
	const DirectX::SimpleMath::Vector3& GetTranslation() { return m_ObjPlayer[0].GetTranslation(); }
	//	回転角(XYZ)
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_ObjPlayer[0].GetRotation(); }
	//	弾丸用の当たり判定取得
	const SphereNode& GetCollisionNodeBullet() { return m_CollisionNodeBullet; }
	//	本体の当たり判定取得
	const SphereNode& GetCollisionNodeBody() { return m_CollisionNodeBody; }
	//	速度を取得
	const DirectX::SimpleMath::Vector3& GetVelocity() { return m_Velocity; }


private:
	DirectX::Keyboard* m_keyboard;						//キーボード
	DirectX::Keyboard::KeyboardStateTracker* m_tracker;	//トリガー

	//	自機の移動座標
	DirectX::SimpleMath::Vector3 m_headPos;
	//	自機のワールド行列
	DirectX::SimpleMath::Matrix m_worldHead;
	//	自機オブジェクト
	std::vector<Obj3d> m_ObjPlayer;
	//	状態
	bool m_plsyerState;
	//	sin用の角度
	float m_cycle;

	//	弾丸の速度ベクトル
	DirectX::SimpleMath::Vector3 m_BulletVel;
	//	弾丸発射フラグ
	bool m_bulletFlag;
	//	弾丸発射カウント
	int m_bulletCount;
	//	弾丸用の当たり判定
	SphereNode m_CollisionNodeBullet;
	//	本体の当たり判定
	SphereNode m_CollisionNodeBody;

	//	速度
	DirectX::SimpleMath::Vector3 m_Velocity;

	//	ジャンプフラグ
	bool m_isJump;

};
