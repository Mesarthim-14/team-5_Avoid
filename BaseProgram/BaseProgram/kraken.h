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
class CKrakenTentacles;
class CBossHp;

//=============================================================================
// �N���X��`
//=============================================================================
class CKraken : public CEnemy, public CStateObject
{
public:
    enum MOTION
    {
        MOTION_NONE = -1,   // �����l
        MOTION_IDOL,        // �ʏ�
		MOTION_ATTACK,      // �U��
		MOTION_ANGRY,       // �{�����Ƃ�
		MOTION_DAMAGE,      // �_���[�W
        MOTION_DEATH,       // ���񂾂Ƃ�
        MOTION_MAX
    };

    CKraken(PRIORITY Priority = PRIORITY_CHARACTER);    // �R���X�g���N�^
    ~CKraken();                                         // �f�X�g���N�^

    static CKraken *Create();           // �C���X�^���X����
    HRESULT Init();                     // ����������
    void Uninit();                      // �I������
    void Update();                      // �X�V����
    void ChangeState(CState* pState);   // ��Ԃ̕ύX
    void SubLife();                     // �̗͂̌��Z

    inline CCollisionModelOBB* GetCollosion()const  { return m_pCollision; }        // �����蔻��̏��
    inline bool GetDead()const                      { return m_bDead; }             // ���񂾔���
    inline CSkinmeshModel* GetSkinMesh()const       { return m_pSkinmeshModel; }    // �X�L�����b�V���̏��
    inline CBossHp* GetHpUi()const                  { return m_pHpUi; }

private:
    // private�֐�
    void CreateModel();     // ���f���̐���
    void UpdateState();     // �v���C���[�̏��
    void Attack();          // �U������
    void CreateTentacles(); // �G��̐���

    // �����o�ϐ�
    CSkinmeshModel *m_pSkinmeshModel;           // �X�L�����b�V�����f���|�C���^
    CCollisionModelOBB* m_pCollision;           // �����蔻��
    CState* m_pCurrentState;                    // ���݂̏�ԃ|�C���^
    CState* m_pNextState;                       // ���̏�ԃ|�C���^
    vector<CKrakenTentacles*> m_apTentacles;    // �G��
    int m_nBulletCount;                         // ���˃J�E���g
    int m_nLife;                                // ���C�t
    bool m_bDead;                               // ���񂾃t���O
    CBossHp* m_pHpUi;                           // HP��Ui
};
#endif