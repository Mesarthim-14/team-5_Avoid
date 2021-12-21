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
class CCautionBossBulletUi;

//=========================================================================
// �N���X��`
//=========================================================================
class CBossBullet : public CBullet
{
public:
	CBossBullet(PRIORITY Priority);    // �R���X�g���N�^
	~CBossBullet();                    // �f�X�g���N�^

	static CBossBullet *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);	// �C���X�^���X����
	HRESULT Init();					// ����������
	void Uninit();					// ����������
	void Update();					// �X�V����
	void Draw();					// �`��

    void SetDeath() { m_bDeath = true; }    // ���̍X�V�Ŕj�����邩�̔���X�V

    bool GetDeath()const { return m_bDeath; }   // // ���̍X�V�Ŕj�����邩�̔���擾

private:
    void FollowPlayer();                    // �ړ��ʂ̐ݒ�
    void FixPos(const D3DXVECTOR3& pos);    // ���W�̏C��

	// �����o�ϐ�
	CModel * m_pModel;					// ���f���|�C���^
    CCautionBossBulletUi* m_pCaution;   // �x��

    bool m_bDeath;  // ���̍X�V�Ŕj�����邩�̔���
};

#endif