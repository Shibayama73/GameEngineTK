//	プレイヤークラス
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

void Enemy::Initialize()
{
	//	自機パーツの読み込み
	m_ObjEnemy.resize(ENEMY_PARTS_NUM);
	m_ObjEnemy[ENEMY_PARTS_TIRE].LoadModel(L"Resources/tire.cmo");
	m_ObjEnemy[ENEMY_PARTS_HEAD].LoadModel(L"Resources/head.cmo");
	m_ObjEnemy[ENEMY_PARTS_ARM_RIGHT].LoadModel(L"Resources/arm_right.cmo");
	m_ObjEnemy[ENEMY_PARTS_ARM_LEFT].LoadModel(L"Resources/arm_right.cmo");
	m_ObjEnemy[ENEMY_PARTS_TOP].LoadModel(L"Resources/top.cmo");

	//	親子関係の構築(子パーツに親を設定)
	m_ObjEnemy[ENEMY_PARTS_HEAD].SetObjParent(&m_ObjEnemy[ENEMY_PARTS_TIRE]);
	m_ObjEnemy[ENEMY_PARTS_ARM_RIGHT].SetObjParent(&m_ObjEnemy[ENEMY_PARTS_HEAD]);
	m_ObjEnemy[ENEMY_PARTS_ARM_LEFT].SetObjParent(&m_ObjEnemy[ENEMY_PARTS_HEAD]);
	m_ObjEnemy[ENEMY_PARTS_TOP].SetObjParent(&m_ObjEnemy[ENEMY_PARTS_HEAD]);

	//	子パーツの親からのオフセット(座標のずれ)をセット
	m_ObjEnemy[ENEMY_PARTS_HEAD].SetTranslation(Vector3(0, 0.1f, 0));
	m_ObjEnemy[ENEMY_PARTS_ARM_RIGHT].SetTranslation(Vector3(0.25f, 0.2f, 0));
	m_ObjEnemy[ENEMY_PARTS_ARM_LEFT].SetTranslation(Vector3(-0.25f, 0.2f, 0));
	m_ObjEnemy[ENEMY_PARTS_TOP].SetTranslation(Vector3(0, 0.2f, 0.3f));

	//	大きさ
	m_ObjEnemy[ENEMY_PARTS_TIRE].SetScale(Vector3(2, 2, 2));

	//	翼の向き
	m_ObjEnemy[ENEMY_PARTS_ARM_RIGHT].SetRotation(Vector3(0, -30.0f, 0));
	m_ObjEnemy[ENEMY_PARTS_ARM_LEFT].SetRotation(Vector3(0, 30.0f, 0));

	//	状態の初期化(オフ)
	//m_enemyState = false;
	m_deathFlag = false;

	//	初期位置を設定
	Vector3 pos;
	pos.x = rand() % 10;
	pos.z = rand() % 10;

	SetTranslation(pos);

	//	初期化
	m_timer = 0;
	m_distAngle = 0;

	{//	敵本体の当たり判定ノードの設定
		m_CollisionNodeBody.Initialize();

		//	親パーツのを設定
		m_CollisionNodeBody.SetParent(&m_ObjEnemy[ENEMY_PARTS_HEAD]);
		m_CollisionNodeBody.SetTrans(Vector3(0, 0.1f, 0));
		m_CollisionNodeBody.SetLocalRadius(0.5f);

	}


}

void Enemy::Update()
{
	m_timer--;
	if (m_timer < 0)
	{
		m_timer = 60;

		//	目標角をランダムに
		//-0.5～0.5
		float rnd = (float)rand() / RAND_MAX - 0.5f;
		//-90～90
		rnd *= 180.0f;
		//	ラジアンに変換
		rnd = XMConvertToRadians(rnd);

		m_distAngle += rnd;
	}

	//Vector3 rot = GetRotation();
	////	補間
	//float angle = m_distAngle - rot.y;
	//rot.y *= angle*0.01f;

	Vector3 rot = m_ObjEnemy[ENEMY_PARTS_TIRE].GetRotation();
	float angle = m_distAngle - rot.y;
	rot.y += angle*0.01f;
	m_ObjEnemy[ENEMY_PARTS_TIRE].SetRotation(rot);


	//SetRotation(Vector3(0, m_distAngle, 0));

	////	自機の大きさの設定
	//m_cycle += 0.1f;
	//float scale = 1.0f + sinf(m_cycle);
	//m_ObjPlayer[PLAYER_PARTS_HEAD].SetScale(Vector3(scale, scale, scale));

	////	自機の状態がオフのとき
	//if (m_enemyState == false)
	//{
	//	//	変形する
	//	m_ObjEnemy[ENEMY_PARTS_HEAD].SetTranslation(Vector3(0, 0.6f, 0));
	//	m_ObjEnemy[ENEMY_PARTS_HEAD].SetRotation(Vector3(1.5f, 0, 0));
	//	m_ObjEnemy[ENEMY_PARTS_ARM_RIGHT].SetRotation(Vector3(0, 1.5f, -1.8f));
	//	m_ObjEnemy[ENEMY_PARTS_ARM_LEFT].SetRotation(Vector3(0, -1.5f, 1.8f));
	//	m_ObjEnemy[ENEMY_PARTS_TOP].SetTranslation(Vector3(0, 0, -0.1f));
	//	m_ObjEnemy[ENEMY_PARTS_TOP].SetRotation(Vector3(5.0f, 0, 0));

	//	//	状態をオン
	//	m_enemyState = true;
	//}
	//else
	//{
	//	//	子パーツの親からのオフセット(座標のずれ)をセット
	//	m_ObjEnemy[ENEMY_PARTS_HEAD].SetTranslation(Vector3(0, 0.1f, 0));
	//	m_ObjEnemy[ENEMY_PARTS_ARM_RIGHT].SetTranslation(Vector3(0.25f, 0.2f, 0));
	//	m_ObjEnemy[ENEMY_PARTS_ARM_LEFT].SetTranslation(Vector3(-0.25f, 0.2f, 0));
	//	m_ObjEnemy[ENEMY_PARTS_TOP].SetTranslation(Vector3(0, 0.2f, 0.3f));

	//	//	翼の向き
	//	m_ObjEnemy[ENEMY_PARTS_ARM_RIGHT].SetRotation(Vector3(0, -30.0f, 0));
	//	m_ObjEnemy[ENEMY_PARTS_ARM_LEFT].SetRotation(Vector3(0, 30.0f, 0));

	//	//	状態をオフ
	//	m_enemyState = false;
	//}

	Vector3 trans = m_ObjEnemy[ENEMY_PARTS_TIRE].GetTranslation();

	//	移動ベクトル(Z座標前進)
	Vector3 move(0, 0, -0.1f);
	Vector3 rotv = m_ObjEnemy[ENEMY_PARTS_TIRE].GetRotation();

	//	回転
	//float angle = m_ObjEnemy[0].GetRotation().y;
	Matrix rotm = Matrix::CreateRotationY(rotv.y);
	//	移動ベクトルを自機の角度分回転させる
	move = Vector3::TransformNormal(move, rotm);
	//Vector3 pos = m_ObjEnemy[0].GetTranslation();
	//m_ObjEnemy[0].SetTranslation(pos + rotm);

	//	自機の座標を移動
	trans += move;

	m_ObjEnemy[ENEMY_PARTS_TIRE].SetTranslation(trans);

	//{//	移動ベクトル(Z座標後退)
	//	Vector3 moveV(0, 0, 0.1f);
	//	//	回転
	//	float angle = m_ObjEnemy[0].GetRotation().y;
	//	Matrix rotmat = Matrix::CreateRotationY(angle);
	//	//	移動ベクトルを自機の角度分回転させる
	//	moveV = Vector3::TransformNormal(moveV, rotmat);
	//	Vector3 pos = m_ObjEnemy[0].GetTranslation();
	//	m_ObjEnemy[0].SetTranslation(pos + moveV);

	//	//	移動ベクトルを自機の角度分回転させる
	//	//	moveV = Vector3::TransformNormal(moveV, m_worldHead);
	//	//Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(headAngle));
	//	//moveV = Vector3::TransformNormal(moveV, rotmaty);

	//	//	自機の座標を移動
	//	m_headPos += moveV;
	//}
	//
	//	//	左に旋回する
	//	float angle = m_ObjEnemy[0].GetRotation().y;
	//	m_ObjEnemy[0].SetRotation(Vector3(0, angle + 0.03f, 0));

	//	//headAngle += 0.1f;
	//	////	移動ベクトル左(X座標後退)
	//	//Vector3 moveV(-0.1f, 0, 0);
	//	////	自機の座標を移動
	//	//m_headPos += moveV;
	//}
	//	//	右に旋回する
	//	float angle = m_ObjEnemy[0].GetRotation().y;
	//	m_ObjEnemy[0].SetRotation(Vector3(0, angle - 0.03f, 0));


	//	自機オブジェクトの更新
	for (std::vector<Obj3d>::iterator it = m_ObjEnemy.begin();
		it != m_ObjEnemy.end();
		it++)
	{
		it->Update();
	}

	//	敵本体用の当たり判定ノード
	m_CollisionNodeBody.Update();

}

void Enemy::Draw()
{
	//	自機オブジェクトの描画
	for (std::vector<Obj3d>::iterator it = m_ObjEnemy.begin();
		it != m_ObjEnemy.end();
		it++)
	{
		it->Draw();
	}

	//	敵本体用当たり判定ノード
	m_CollisionNodeBody.Draw();
}

//=============消す候補=======================//

bool Enemy::GetDeath()
{
	return m_deathFlag;
}

void Enemy::SetDeath()
{
	m_deathFlag = true;

	m_ObjEnemy.pop_back();
}
