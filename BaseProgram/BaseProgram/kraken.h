#ifndef _KRAKEN_H_
#define _KRAKEN_H_
//=============================================================================
//
//�N���[�P��(�G) [kraken.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy.h"

//=============================================================================
// �O���錾
//=============================================================================
class CSkinmeshModel;
class CCollisionModelOBB;

//=============================================================================
// �N���X��`
//=============================================================================
class CKraken : public CEnemy
{
public:
    CKraken(PRIORITY Priority = PRIORITY_CHARACTER);    // �R���X�g���N�^
    ~CKraken();                                         // �f�X�g���N�^

    static CKraken *Create();   // �C���X�^���X����
    HRESULT Init();             // ����������
    void Uninit();              // �I������
    void Update();              // �X�V����

    inline void SubLife()           { m_nLife--; }
    CCollisionModelOBB* GetCollosion() { return m_pCollision; }
    inline bool GetDead()const      { return m_bDead; }

private:
    // private�֐�
    void Attack();      // �U��
    void ShotBullet();  // �e����
    void CreateModel(); // ���f���̐���

    CSkinmeshModel *m_pSkinmeshModel;   // �X�L�����b�V�����f���|�C���^
    int m_nBulletCount;                 // ���˃J�E���g
    CCollisionModelOBB* m_pCollision;   // �����蔻��
    int m_nLife;                        // ���C�t
    bool m_bDead;                       // ���񂾃t���O
};
#endif