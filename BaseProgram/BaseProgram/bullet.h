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
class CCollisionModelOBB;

//=========================================================================
// �N���X��`
//=========================================================================
class CBullet : public CScene
{
public:
	CBullet(PRIORITY Priority);    // �R���X�g���N�^
	~CBullet();                    // �f�X�g���N�^

	virtual HRESULT Init();     // ����������
	virtual void Uninit();      // �I������
	virtual void Update();      // �X�V����
	virtual void Draw();        // �`��

    void Hit();						// �Փ˔���
    
    // Set�֐�
    inline void SetPos(const D3DXVECTOR3 &pos)          { m_pos = pos; }            // ���W�ݒ�
    inline void SetMove(const D3DXVECTOR3 &move)        { m_move = move; }          // �ړ��ʐݒ�
    inline void SetRot(const D3DXVECTOR3 &rot)          { m_rot = rot; }            // �p�x�ݒ�
    inline void SetColRadius(const float &radius)       { m_ColRadius = radius; }   // �����蔻��̔��a�ݒ�
    inline void SetColSizeOBB(const D3DXVECTOR3 &size)  { m_colSizeOBB = size; }    // �����蔻��T�C�Y(OBB)�ݒ�
    inline void SetLife(const int &nLife)               { m_nLife = nLife; }        // �̗͐ݒ�

    // Get�֐�
    inline D3DXVECTOR3 GetPos()const    { return m_pos; }       // ���W���
    inline D3DXVECTOR3 GetMove()const   { return m_move; }      // �ړ��ʏ��
    inline D3DXVECTOR3 GetRot()const    { return m_rot; }       // �p�x���
    inline float GetColRadius()const    { return m_ColRadius; } // �����蔻��̔��a���
    inline int GetLife()const           { return m_nLife; }     // �̗͏��
    inline CCollisionModelSphere* GetColSpherePtr()const { return m_pCollisionModelSphere; }    // �����蔻�胂�f���̃|�C���^(�J�v�Z��)
    inline CCollisionModelOBB* GetColOBBPtr()const { return m_pColModelOBB; }                   // �����蔻�胂�f���̃|�C���^(�J�v�Z��)

private:
	D3DXVECTOR3 m_pos;          // ���W
	D3DXVECTOR3 m_move;         // �ړ���
	D3DXVECTOR3 m_rot;          // ���݂̉�]
	float m_ColRadius;          // �����蔻��̔��a(����)
    D3DXVECTOR3 m_colSizeOBB;   // �����蔻��T�C�Y(OBB)
	int m_nLife;                // ��������
	float m_fSpeed;             // �X�s�[�h
	int m_nDamage;              // �_���[�W��

    CCollisionModelSphere* m_pCollisionModelSphere;   // �����蔻�胂�f��(����)�̃|�C���^
    CCollisionModelOBB* m_pColModelOBB;               // �����蔻�胂�f��(OBB)�̃|�C���^
};

#endif