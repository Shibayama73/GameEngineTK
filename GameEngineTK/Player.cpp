//	プレイヤークラス
#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

void Player::Initialize(DirectX::Keyboard* keyboard, DirectX::Keyboard::KeyboardStateTracker* tracker)
{
	//	キーボードの生成
	m_keyboard = keyboard;
	//	トリガーの生成
	m_tracker = tracker;
	
	//	自機パーツの読み込み
	m_ObjPlayer.resize(PLAYER_PARTS_NUM);
	m_ObjPlayer[PLAYER_PARTS_TIRE].LoadModel(L"Resources/tire.cmo");
	m_ObjPlayer[PLAYER_PARTS_HEAD].LoadModel(L"Resources/head.cmo");
	m_ObjPlayer[PLAYER_PARTS_ARM_RIGHT].LoadModel(L"Resources/arm_right.cmo");
	m_ObjPlayer[PLAYER_PARTS_ARM_LEFT].LoadModel(L"Resources/arm_right.cmo");
	m_ObjPlayer[PLAYER_PARTS_TOP].LoadModel(L"Resources/top.cmo");

	//	親子関係の構築(子パーツに親を設定)
	m_ObjPlayer[PLAYER_PARTS_HEAD].SetObjParent(&m_ObjPlayer[PLAYER_PARTS_TIRE]);
	m_ObjPlayer[PLAYER_PARTS_ARM_RIGHT].SetObjParent(&m_ObjPlayer[PLAYER_PARTS_HEAD]);
	m_ObjPlayer[PLAYER_PARTS_ARM_LEFT].SetObjParent(&m_ObjPlayer[PLAYER_PARTS_HEAD]);
	m_ObjPlayer[PLAYER_PARTS_TOP].SetObjParent(&m_ObjPlayer[PLAYER_PARTS_HEAD]);

	//	子パーツの親からのオフセット(座標のずれ)をセット
	m_ObjPlayer[PLAYER_PARTS_HEAD].SetTranslation(Vector3(0, 0.1f, 0));
	m_ObjPlayer[PLAYER_PARTS_ARM_RIGHT].SetTranslation(Vector3(0.25f, 0.2f, 0));
	m_ObjPlayer[PLAYER_PARTS_ARM_LEFT].SetTranslation(Vector3(-0.25f, 0.2f, 0));
	m_ObjPlayer[PLAYER_PARTS_TOP].SetTranslation(Vector3(0, 0.2f, 0.3f));

	//	大きさ
	m_ObjPlayer[PLAYER_PARTS_TIRE].SetScale(Vector3(2, 2, 2));

	//	翼の向き
	m_ObjPlayer[PLAYER_PARTS_ARM_RIGHT].SetRotation(Vector3(0, -30.0f, 0));
	m_ObjPlayer[PLAYER_PARTS_ARM_LEFT].SetRotation(Vector3(0, 30.0f, 0));

	//	状態の初期化(オフ)
	m_plsyerState = false;

	//	弾丸発射フラグ(オフ)
	m_bulletFlag = false;

	//	弾丸発射カウント
	m_bulletCount = 0;

	{//	弾丸用当たり判定ノードの設定
		m_CollisionNodeBullet.Initialize();

		//	親パーツを設定
		m_CollisionNodeBullet.SetParent(&m_ObjPlayer[PLAYER_PARTS_TOP]);
		m_CollisionNodeBullet.SetTrans(Vector3(0,0.3f,0));
		m_CollisionNodeBullet.SetLocalRadius(0.3f);
	}

	{//	本体の当たり判定ノードの設定
		m_CollisionNodeBody.Initialize();

		//	親パーツのを設定
		m_CollisionNodeBody.SetParent(&m_ObjPlayer[PLAYER_PARTS_TIRE]);
		m_CollisionNodeBody.SetTrans(Vector3(0, 0.1f, 0));
		m_CollisionNodeBody.SetLocalRadius(0.1f);

	}

	//	ジャンプフラグをオフ
	m_isJump = false;

}

void Player::Update()
{
	////	自機の大きさの設定
	//m_cycle += 0.1f;
	//float scale = 1.0f + sinf(m_cycle);
	//m_ObjPlayer[PLAYER_PARTS_HEAD].SetScale(Vector3(scale, scale, scale));

	//	キーボードの状態取得
	Keyboard::State key = m_keyboard->GetState();
	m_tracker->Update(key);

	if (m_tracker->IsKeyPressed(Keyboard::Keys::Z))
	{
		//	ジャンプする
		StartJump();
	}
	//	ジャンプ中のとき
	if (m_isJump)
	{
		//	重力による加速
		m_Velocity.y -= GRAVITY_ACC;

		if (m_Velocity.y < -JUMP_SPEED_MAX)
		{
			m_Velocity.y = -JUMP_SPEED_MAX;
		}
	}

	{//	速度による移動
		Vector3 trans = GetTranslation();
		trans += m_Velocity;
		SetTranslation(trans);
	}

	//	Xキーが押されたとき
	if (m_tracker->pressed.X)
	{
		//	自機の状態がオフのとき
		if (m_plsyerState == false)
		{
			//	変形する
			m_ObjPlayer[PLAYER_PARTS_HEAD].SetTranslation(Vector3(0, 0.6f, 0));
			m_ObjPlayer[PLAYER_PARTS_HEAD].SetRotation(Vector3(1.5f, 0, 0));
			m_ObjPlayer[PLAYER_PARTS_ARM_RIGHT].SetRotation(Vector3(0, 1.5f, -1.8f));
			m_ObjPlayer[PLAYER_PARTS_ARM_LEFT].SetRotation(Vector3(0, -1.5f, 1.8f));
			m_ObjPlayer[PLAYER_PARTS_TOP].SetTranslation(Vector3(0, 0, -0.1f));
			m_ObjPlayer[PLAYER_PARTS_TOP].SetRotation(Vector3(5.0f, 0, 0));

			//	状態をオン
			m_plsyerState = true;
		}
		else
		{
			//	子パーツの親からのオフセット(座標のずれ)をセット
			m_ObjPlayer[PLAYER_PARTS_HEAD].SetTranslation(Vector3(0, 0.1f, 0));
			m_ObjPlayer[PLAYER_PARTS_ARM_RIGHT].SetTranslation(Vector3(0.25f, 0.2f, 0));
			m_ObjPlayer[PLAYER_PARTS_ARM_LEFT].SetTranslation(Vector3(-0.25f, 0.2f, 0));
			m_ObjPlayer[PLAYER_PARTS_TOP].SetTranslation(Vector3(0, 0.2f, 0.3f));

			//	翼の向き
			m_ObjPlayer[PLAYER_PARTS_ARM_RIGHT].SetRotation(Vector3(0, -30.0f, 0));
			m_ObjPlayer[PLAYER_PARTS_ARM_LEFT].SetRotation(Vector3(0, 30.0f, 0));

			//	状態をオフ
			m_plsyerState = false;
		}
	}

	//	Wキーが押されてるとき前進
	if (key.W)
	{
		//	移動ベクトル(Z座標前進)
		Vector3 moveV(0, 0, -0.15f);
		//	回転
		float angle = m_ObjPlayer[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		//	移動ベクトルを自機の角度分回転させる
		moveV = Vector3::TransformNormal(moveV, rotmat);
		//moveV = Vector3::TransformNormal(moveV, m_worldHead);
		//Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(headAngle));
		//moveV = Vector3::TransformNormal(moveV, rotmaty);
		Vector3 pos = m_ObjPlayer[0].GetTranslation();
		m_ObjPlayer[0].SetTranslation(pos + moveV);

		//	自機の座標を移動
		m_headPos += moveV;

	}
	//	Sキーが押されてるとき後退
	if (key.S)
	{
		//	移動ベクトル(Z座標後退)
		Vector3 moveV(0, 0, 0.1f);
		//	回転
		float angle = m_ObjPlayer[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		//	移動ベクトルを自機の角度分回転させる
		moveV = Vector3::TransformNormal(moveV, rotmat);
		Vector3 pos = m_ObjPlayer[0].GetTranslation();
		m_ObjPlayer[0].SetTranslation(pos + moveV);

		//	移動ベクトルを自機の角度分回転させる
		//	moveV = Vector3::TransformNormal(moveV, m_worldHead);
		//Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(headAngle));
		//moveV = Vector3::TransformNormal(moveV, rotmaty);

		//	自機の座標を移動
		m_headPos += moveV;

	}
	//	Aキーが押されてるとき左旋回
	if (key.A)
	{
		//	左に旋回する
		float angle = m_ObjPlayer[0].GetRotation().y;
		m_ObjPlayer[0].SetRotation(Vector3(0, angle + 0.03f, 0));

		//headAngle += 0.1f;
		////	移動ベクトル左(X座標後退)
		//Vector3 moveV(-0.1f, 0, 0);
		////	自機の座標を移動
		//m_headPos += moveV;
	}
	//	Dキーが押されてるとき右旋回
	if (key.D)
	{
		//	右に旋回する
		float angle = m_ObjPlayer[0].GetRotation().y;
		m_ObjPlayer[0].SetRotation(Vector3(0, angle - 0.03f, 0));

		//headAngle -= 0.1f;
		////	移動ベクトル左(X座標前進)
		//Vector3 moveV(0.1f, 0, 0);
		////	自機の座標を移動
		//m_headPos += moveV;
	}

	//	Spaceキーが押されたら
	if(key.Space)
	{	
		//	弾丸発射フラグをオン
		m_bulletFlag = true;
	}

	//	弾丸発射フラグがオンのとき
	if (m_bulletFlag)
	{
		m_bulletCount++;
		//	3秒経ったら
		if (m_bulletCount  >= 180) {
			m_bulletCount = 0;
			//	弾丸発射フラグをオフ
			m_bulletFlag = false;
		}

		//	弾丸パーツを発射
		FireBullet();

		//	弾丸パーツの座標の移動
		Vector3 pos = m_ObjPlayer[PLAYER_PARTS_TOP].GetTranslation();
		//	弾丸パーツの前進
		m_ObjPlayer[PLAYER_PARTS_TOP].SetTranslation(pos + m_BulletVel);
	}
	//	弾丸発射フラグがオフのとき
	else {
		//	弾丸パーツをもとに戻す
		ResetBuller();
	}


	this->Calc();

	//	デバッグ用
	//FireBullet();
	
	

}

void Player::Draw()
{
	//	自機オブジェクトの描画
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin();
		it != m_ObjPlayer.end();
		it++)
	{
		it->Draw();
	}
	//	弾丸用当たり判定ノード
	m_CollisionNodeBullet.Draw();
	//	本体用当たり判定ノード
	m_CollisionNodeBody.Draw();

}

void Player::FireBullet()
{
	//	発射するパーツのワールド行列を取得
	Matrix worldm = m_ObjPlayer[PLAYER_PARTS_TOP].GetWorld();

	//	抽出した情報をしまっておく変数
	Vector3 scale;			//ワールドスケーリング
	Quaternion rotation;	//ワールド回転
	Vector3 translation;	//ワールド座標

	//	ワールド行列から各要素を抽出
	worldm.Decompose(scale, rotation, translation);

	//	親パーツから分離、独立させる
	m_ObjPlayer[PLAYER_PARTS_TOP].SetObjParent(nullptr);
	m_ObjPlayer[PLAYER_PARTS_TOP].SetScale(scale);
	m_ObjPlayer[PLAYER_PARTS_TOP].SetRotationQ(rotation);
	m_ObjPlayer[PLAYER_PARTS_TOP].SetTranslation(translation);

	//	弾丸パーツの速度を設定
	m_BulletVel = Vector3(0, 0, -0.3f);
	//	パーツの向きに合わせて速度ベクトルを回転
	m_BulletVel = Vector3::Transform(m_BulletVel, rotation);

}

//	弾丸を最装着(リセット)
void Player::ResetBuller()
{
	//	親子関係の再構築(子パーツに親を設定)
	m_ObjPlayer[PLAYER_PARTS_TOP].SetObjParent(&m_ObjPlayer[PLAYER_PARTS_HEAD]);

	//	子パーツの親からのオフセット(座標のずれ)をリセット
	m_ObjPlayer[PLAYER_PARTS_TOP].SetTranslation(Vector3(0, 0.2f, 0.3f));

	//	回転角のリセット
	m_ObjPlayer[PLAYER_PARTS_TOP].SetRotation(Vector3(0, 0, 0));
	//	大きさのリセット
	m_ObjPlayer[PLAYER_PARTS_TOP].SetScale(Vector3(1, 1, 1));

}

void Player::Calc()
{
	//	自機オブジェクトの更新
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin();
		it != m_ObjPlayer.end();
		it++)
	{
		it->Update();
	}

	//	弾丸用当たり判定ノード
	m_CollisionNodeBullet.Update();
	//	本体用の当たり判定ノード
	m_CollisionNodeBody.Update();

}

/// <summary>
/// ジャンプを開始
/// </summary>
void Player::StartJump()
{
	if (!m_isJump)
	{
		m_Velocity.y = JUMP_SPEED_FIRST;
		m_isJump = true;
	}
}

/// <summary>
/// 落下を開始
/// </summary>
void Player::StartFall()
{
	if (!m_isJump)
	{
		m_Velocity.y = 0;
		m_isJump = true;
	}
}

/// <summary>
/// 落下を終了
/// </summary>
void Player::StopJump()
{
	m_isJump = false;
	m_Velocity = Vector3::Zero;
}
