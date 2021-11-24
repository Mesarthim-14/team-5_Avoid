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

	static CBullet *Create(void);	// �C���X�^���X����
	virtual HRESULT Init(void);					// ����������
	virtual void Uninit(void);					// ����������
	virtual void Update(void);					// �X�V����
	virtual void Draw(void);					// �`��

protected:
	D3DXVECTOR3 m_pos;						// ���W
	D3DXVECTOR3 m_move;						// �ړ���
	D3DXVECTOR3 m_rot;						// ���݂̉�]
	D3DXVECTOR3 m_size;						// �T�C�Y
	int m_nLife;							// ��������
	float m_fSpeed;							// �X�s�[�h
	int m_nDamage;							// �_���[�W��

    CCollisionModelSphere* m_pCollisionModelSphere;   // �����蔻�胂�f���̃|�C���^
};

#endif