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
	CBossBullet(PRIORITY = PRIORITY_TEST_MODEL);    // �R���X�g���N�^
	~CBossBullet();                                 // �f�X�g���N�^

	static CBossBullet *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);	// �C���X�^���X����
	HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);					// ����������
	void Uninit();					// ����������
	void Update();					// �X�V����
	void Draw();					// �`��
	void Hit();						// �Փ˔���

private:
    void FollowPlayer(); // �ړ��ʂ̐ݒ�
	void Move();

	// �����o�ϐ�
	CModel * m_pModel;					// ���f���|�C���^
};

#endif