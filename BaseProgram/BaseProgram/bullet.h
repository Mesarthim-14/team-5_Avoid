#ifndef _BULLET_H_
#define _BULLET_H_
//=============================================================================
//
// �e�N���X [boss_bullet.h]
// Author : Hayashikawa Sarina
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "model.h"

//=========================================================================
// �O���錾
//=========================================================================
class CCollisionModelSphere;

//=========================================================================
// �N���X��`
//=========================================================================
class CBullet : public CScene
{
public:
	CBullet(PRIORITY = PRIORITY_TEST_MODEL);	// �R���X�g���N�^
	~CBullet();								// �f�X�g���N�^

	static CBullet *Create();   // �C���X�^���X����
	virtual HRESULT Init();     // ����������
	virtual void Uninit();      // �I������
	virtual void Update();      // �X�V����
	virtual void Draw();        // �`��
    CCollisionModelSphere* GetColSpherePtr()const { return m_pCollisionModelSphere; }    // �����蔻�胂�f���̃|�C���^(�J�v�Z��)
    
    // Set�֐�
    inline void SetPos(const D3DXVECTOR3 &pos)      { m_pos = pos; }        // ���W�ݒ�
    inline void SetMove(const D3DXVECTOR3 &move)    { m_move = move; }      // �ړ��ʐݒ�
    inline void SetRot(const D3DXVECTOR3 &rot)      { m_rot = rot; }        // �p�x�ݒ�
    inline void SetSize(const D3DXVECTOR3 &size)    { m_size = size; }      // �T�C�Y�ݒ�
    inline void SetLife(const int &nLife)           { m_nLife = nLife; }    // �̗͐ݒ�

    // Get�֐�
    inline D3DXVECTOR3 GetPos()const    { return m_pos; }   // ���W���
    inline D3DXVECTOR3 GetMove()const   { return m_move; }  // �ړ��ʏ��
    inline D3DXVECTOR3 GetRot()const    { return m_rot; }   // �p�x���
    inline D3DXVECTOR3 GetSize()const   { return m_size; }  // �T�C�Y���
    inline int GetLife()const           { return m_nLife; } // �̗͏��

private:
	D3DXVECTOR3 m_pos;  // ���W
	D3DXVECTOR3 m_move; // �ړ���
	D3DXVECTOR3 m_rot;  // ���݂̉�]
	D3DXVECTOR3 m_size; // �T�C�Y
	int m_nLife;        // ��������
	float m_fSpeed;     // �X�s�[�h
	int m_nDamage;      // �_���[�W��

    CCollisionModelSphere* m_pCollisionModelSphere;   // �����蔻�胂�f���̃|�C���^
};

#endif