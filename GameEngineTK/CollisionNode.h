/// <summary>
/// �����蔻��m�[�h
/// </summary>
#pragma once

#include "Obj3d.h"
#include "Collision.h"

// �����蔻��m�[�h�N���X
class CollisionNode
{
public:
	//	�f�o�b�O�\���t���O�擾
	static bool GetDebugVisible() { return m_DebugVisible; }
	//	�f�o�b�O�\���t���O�Z�b�g
	static void SetDebugVisible(bool visible) { m_DebugVisible = visible; }

protected:
	//	�f�o�b�O�t���O�\��ON
	static bool m_DebugVisible;

public:
	//	������
	virtual void Initialize() = 0;
	//	�X�V
	virtual void Update() = 0;
	//	�`��
	virtual void Draw() = 0;

	//	�e�q�֌W�\�z
	void SetParent(Obj3d* parent);
	//	�e����̃I�t�Z�b�g
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { m_Trans = trans; }


protected:
	//	�f�o�b�O�\���p�I�u�W�F�N�g
	Obj3d m_Obj;

	//	�e����̃I�t�Z�b�g
	DirectX::SimpleMath::Vector3 m_Trans;

};

//	�������蔻��m�[�h�N���X
class SphereNode :public CollisionNode, public Sphere
{
public:
	SphereNode();
	//	������
	void Initialize();
	//	�X�V
	void Update();
	//	�`��
	void Draw();

	//	���[�J�����a�̃Z�b�g
	void SetLocalRadius(float radius) { m_LocalRadius = radius; }

protected:
	//	���[�J�����a
	float m_LocalRadius;

};
