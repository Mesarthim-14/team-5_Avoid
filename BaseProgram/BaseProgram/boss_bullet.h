#ifndef _BOSS_BULLET_H_
#define _BOSS_BULLET_H_
//=============================================================================
//
// �{�X�̒e�N���X [boss_bullet.h]
// Author : Hayashikawa Sarina
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "model.h"
#include "bullet.h"
//=========================================================================
// �N���X��`
//=========================================================================
class CBossBullet : public CBullet
{
public:
	CBossBullet(PRIORITY = PRIORITY_TEST_MODEL);	// �R���X�g���N�^
	~CBossBullet();								// �f�X�g���N�^

	static CBossBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move);	// �C���X�^���X����
	HRESULT Init(void);					// ����������
	void Uninit(void);					// ����������
	void Update(void);					// �X�V����
	void Draw(void);					// �`��
	void Hit(void);						// �Փ˔���

private:
	void Move();
	// �����o�ϐ�
	CModel * m_pModel;					// ���f���|�C���^
};

#endif