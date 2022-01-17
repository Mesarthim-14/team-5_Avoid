#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// �v���C���[�N���X�w�b�_�[ [player.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"
#include "skinmesh_model.h"
#include "state_object.h"

//=========================================================================
// �O���錾
//=========================================================================
class CCollisionModelOBB;
class CCollisionModelCapsule;
class CState;
class CGauge;

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer : public CCharacter, public CStateObject
{
public:
    enum ACTION_STATE
    {
        ACTION_NONE = -1,
        ACTION_IDOL,
        ACTION_JUMP,
        ACTION_LANDING,
        ACTION_WALK,
        ACTION_AVOID,
        ACTION_MAX
    };//�s�����

    enum STATE_PLAYER
    {
        STATE_PLAYER_NONE = -1,     // �����l
        STATE_PLAYER_IDOL,          // �ʏ���
        STATE_PLAYER_JUMP,          // �W�����v���
        STATE_PLAYER_AVOID,         // ������
        STATE_PLAYER_STUN,          // �C��
        STATE_PLAYER_KNOCK_BACK,    // �m�b�N�o�b�N
        STATE_PLAYER_MAX,           // �ő�l
    };

    enum SLIME_STATE
    {
        SLIME_LITTLESIZE = 0,
        SLIME_MIDDLESIZE,
        SLIME_LARGESIZE,
        SLIME_STATE_MAX
    };//�X���C���̏�ԁi�傫���j

    enum STATE
    {
        NONE = -1,
        AVOID,      // ���
        CANNON,     // ��C
        JUMP,       // �W�����v
        KNOCKBACK,  // �m�b�N�o�b�N
        NORMAL,     // �ʏ�
        NOT_MOVE,   // �s��
        RESPAWN,    // ���X�|�[��
        STUN,       // �C��
        MAX
    };// ��ԗ�

    CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);    // �R���X�g���N�^
    ~CPlayer();                                         // �f�X�g���N�^

    static CPlayer*Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);    // �N���G�C�g

    HRESULT Init();                                 // ����������
    void Uninit();                                  // �I������
    void Update();                                  // �X�V����
    void Draw();                                    // �`�揈��
    void ShowInfo();                                // ���
    HRESULT LoadInfo();                             // �f�[�^���[�h
    void SaveInfo();                                // �f�[�^�Z�[�u
    void SubLife(const int &nDamage);               // �_���[�W
    void AddLife(const int &nNum);                  // ���C�t�̉��Z
    CSkinmeshModel* GetCurrentSkinMeshPtr();        // ���݂̃X�L�����b�V���|�C���^
    void ChangeState(CState* pPlayerState);         // ��ԃ`�F���W

    // Set�֐�
    inline void SetAction(const int &nCount, const int &nMaxAction) { m_nMaxAction[nCount] = nMaxAction; }  // �A�N�V�����̐ݒ�
    inline void SetMove(const D3DXVECTOR3 &move)                    { CCharacter::SetMove(move); }          // �ړ��ʐݒ�
    inline void SetRotDest(const D3DXVECTOR3& rotDest)              { m_rotDest = rotDest; }                // �ړI�̊p�x
    inline void SetAngle(const float& fAngle)                       { m_fAngle = fAngle; }                  // �A���O��
    inline void SetCollision(const bool &bFlag)                     { m_bCollision = bFlag; }               // �����蔻��
    inline void SetState(const STATE &state)                        { m_state = state; }                    // ��Ԃ̐ݒ�
    inline void AddDeathCount()                                     { m_nDeathCount++; }                    // ���S�񐔂̃J�E���g
    inline void SetBoolJump(const bool &bJump)                      { m_bJump = bJump; }                    // �W�����v�ł��邩�̔���

    // Get�֐�
    inline int GetLife()const                               { return m_nHP; }               // HP�̏��
    inline float GetAngle()const                            { return m_fAngle; }            // �A���O��
    inline D3DXVECTOR3 GetRotDest()const                    { return m_rotDest; }           // �ړI
    inline D3DXVECTOR3 GetInertia()const                    { return m_Inertia; }           // �����̏��
    inline float GetInertiaNum()const                       { return m_fInertiaNum; }       // �����̒l
    inline SLIME_STATE GetSlimeState()const                 { return m_SlimeState; }        // �X���C���̏��
    inline CCollisionModelOBB* GetColOBBPtr()const          { return m_pColModelOBB; }      // �����蔻��|�C���^(OBB)
    inline CCollisionModelCapsule* GetColCapsulePtr()const  { return m_pColModelCapsule; }  // �����蔻��|�C���^(�J�v�Z��)
    inline bool GetCollision()const                         { return m_bCollision; }        // �����蔻��̎g�p
    inline CState* GetCurrentState()const                   { return m_pCurrentState; }     // ���݂̏�ԃ|�C���^�̎擾
    inline STATE GetState()const                            { return m_state; }             // ��ԗ񋓂̎擾
    inline int GetDeathCount()const                         { return m_nDeathCount; }       // ���S�񐔂̏��
    inline int GetTotalDamegeNum()const                     { return m_nTotalDamegeNum; }   // �_���[�W�̑���
    inline bool GetBoolJump()const                          { return m_bJump; }             // �W�����v�ł��邩�̔���̎擾

private:
    // private�֐�
    void UpdateState(); // �v���C���[�̏��
    void UpdateRot();   // �p�x�̍X�V����
    void ChangeModel(); // ���f���`�F���W
    void Respawn();     // ���X�|�[��
    void CreateModel(); // ���f������

    // �����o�ϐ�
    D3DXVECTOR3 m_rotDest;                              // ��](�ڕW�l)
    D3DXVECTOR3 m_Inertia;                              // ����
    float m_fInertiaNum;                                // �����̒l
    float m_fRotationSpeed;                             // ��]�̑��x
    bool m_bMove;                                       // �ړ��̃t���O
    int m_nHP;                                          // �X���C��HP ~100�܂Łi�p�[�Z���g�j
    SLIME_STATE m_SlimeState;                           // �X���C���̏��
    float m_fAngle;                                     // �J���������A���O��
    float m_fAngleSpeed;                                // �ڕW�����܂Ō������X�s�[�h
    ACTION_STATE m_ActionState;                         // �s�����
    CSkinmeshModel *m_pSkinmeshModel[SLIME_STATE_MAX];  // �X�L�����b�V�����f���|�C���^
    int m_nMaxAction[SLIME_STATE_MAX];                  // �A�N�V�����̍ő吔
    CState* m_pCurrentState;                            // ���݂̏�ԃ|�C���^
    CState* m_pNextState;                               // ���̏�ԃ|�C���^
    CCollisionModelOBB* m_pColModelOBB;                 // �����蔻�胂�f��(������)�̃|�C���^
    CCollisionModelCapsule* m_pColModelCapsule;         // �����蔻�胂�f��(�J�v�Z��)�̃|�C���^
    bool m_bCollision;                                  // �����蔻��̎g�p
    STATE m_state;                                      // ���
    int m_nDeathCount;                                  // ���S��
    int m_nTotalDamegeNum;                              // �_���[�W�̑���
    bool m_bJump;                                       // �W�����v�ł��邩�̃t���O
};
#endif