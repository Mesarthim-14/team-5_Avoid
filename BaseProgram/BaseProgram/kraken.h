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
#include "state_object.h"

//=============================================================================
// �O���錾
//=============================================================================
class CSkinmeshModel;
class CCollisionModelOBB;
class CState;

//=============================================================================
// �N���X��`
//=============================================================================
class CKraken : public CEnemy, public CStateObject
{
public:
    CKraken(PRIORITY Priority = PRIORITY_CHARACTER);    // �R���X�g���N�^
    ~CKraken();                                         // �f�X�g���N�^

    static CKraken *Create();           // �C���X�^���X����
    HRESULT Init();                     // ����������
    void Uninit();                      // �I������
    void Update();                      // �X�V����
    void ChangeState(CState* pState);   // ��Ԃ̕ύX

    inline void SubLife()                       { m_nLife--; }
    CCollisionModelOBB* GetCollosion()const     { return m_pCollision; }
    inline bool GetDead()const                  { return m_bDead; }
    inline CSkinmeshModel* GetSkinMesh()const   { return m_pSkinmeshModel; }

private:
    // private�֐�
    void CreateModel(); // ���f���̐���
    void UpdateState(); // �v���C���[�̏��
    void Attack();      // �U������

    // �����o�ϐ�
    CSkinmeshModel *m_pSkinmeshModel;   // �X�L�����b�V�����f���|�C���^
    CCollisionModelOBB* m_pCollision;   // �����蔻��
    int m_nBulletCount;                 // ���˃J�E���g
    int m_nLife;                        // ���C�t
    bool m_bDead;                       // ���񂾃t���O

    // ��Ԃ̃|�C���^
    CState* m_pCurrentState;  // ���݂̏�ԃ|�C���^
    CState* m_pNextState;     // ���̏�ԃ|�C���^
};
#endif