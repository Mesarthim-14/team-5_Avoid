#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//=============================================================================
//
// �L�����N�^�[�N���X�w�b�_  [character.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "main.h"
#include "scene.h"
#include "modelanime.h"

//=============================================================================
// �O���錾
//=============================================================================
class CMotion;

//=============================================================================
// �L�����N�^�[�̃N���X
//=============================================================================
class CCharacter : public CScene
{
public:
    //=============================================================================
    // �L�����N�^�[�̏��
    //=============================================================================
    enum STATE
    {
        STATE_NORMAL = 0,
        STATE_WALK,
        STATE_DEAD,
        STATE_JUMP,
        STATE_AVOID,
        STATE_LANDING,
        STATE_STAN,
        STATE_KNOCKBACK,
        STATE_MAX
    };

    //=============================================================================
    // �L�����N�^�[�̎��
    //=============================================================================
    enum CHARACTER_TYPE
    {
        CHARACTER_TYPE_NONE = -1,    // �����l
        CHARACTER_TYPE_PLAYER,        // �v���C���[
        CHARACTER_TYPE_ENEMY,        // �G
        CHARACTER_TYPE_MAX            // �ő�l
    };

    CCharacter(PRIORITY Priority = PRIORITY_CHARACTER); // �R���X�g���N�^
    virtual ~CCharacter();                              // �f�X�g���N�^

    virtual HRESULT Init();             // ����������
    virtual void Uninit();              // �I������
    virtual void Update();              // �X�V����
    virtual void Draw();                // �`�揈��
    void Landing(const float &fHeight); // ���n

    // Get�֐�
    inline D3DXVECTOR3 GetPos()const                            { return m_pos; }                       // ���݂̍��W���
    inline D3DXVECTOR3 GetOldPos()const                         { return m_posOld; }                    // �Â����W���
    inline D3DXVECTOR3 GetRot()const                            { return m_rot; }                       // �p�x���
    inline D3DXVECTOR3 GetMove()const                           { return m_move; }                      // �ړ��ʂ̏��
    inline D3DXVECTOR3 GetSize()const                           { return m_size; }                      // �T�C�Y�擾
    inline CModelAnime *GetModelAnime(const int &nCount)const   { return m_apModelAnime.at(nCount); }   // ���[�V�����̃J�E���g���
    inline CMotion *GetMotion()const                            { return m_pMotion; }                   // ���[�V�����̃|�C���^���
    inline int GetStateCounter()const                           { return m_nStateCounter; }             // ��ԃJ�E���^�[�̏��
    inline int GetPartsNum()const                               { return m_apModelAnime.size(); }       // �p�[�c���擾
    inline float &GetSpeed()                                    { return m_fSpeed; }                    // �X�s�[�h�̏��
    inline STATE GetState()const                                { return m_State; }                     // ��Ԏ擾
    inline CHARACTER_TYPE GetType() const                       { return m_type; }                      // ���
    inline vector<CModelAnime*> GetModelAnimeVec()const         { return m_apModelAnime; }              // �|�C���^�S�Ă̎擾
    inline D3DXMATRIX GetMtxWorld()const                        { return m_mtxWorld; }                  // �}�g���N�X���[���h

    inline void SetPos(const D3DXVECTOR3 &pos)      { m_pos = pos; }            // ���W�̐ݒ�
    inline void SetLanding(const bool &bLanding)    { m_bLanding = bLanding; }  // ���n
    inline bool GetLanding()                        { return m_bLanding; }      // ���n����擾

protected:
    void SetCharacterInfo(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);  // �L�����N�^�[�̊�{���
    void ModelCreate(const CXfile::HIERARCHY_XFILE_NUM &FileNum);           // ���f���̐���
    void SetShadowRotCalculation();                                         // �e����

    // Set�֐�
    inline void SetPosOld(const D3DXVECTOR3 &posOld)    { m_posOld = posOld; }      // ���W�̐ݒ�
    inline void SetMove(const D3DXVECTOR3 &move)        { m_move = move; }          // �ړ��ʂ̐ݒ�
    inline void SetRot(const D3DXVECTOR3 &rot)          { m_rot = rot; }            // �p�x�̐ݒ�
    inline void SetSize(const D3DXVECTOR3 &size)        { m_size = size; }          // �T�C�Y�ݒ�
    inline void SetSpeed(const float &fSpeed)           { m_fSpeed = fSpeed; }      // ���x�̐ݒ�
    inline void SetState(const STATE &state)            { m_State = state; }        // ��Ԑݒ�
    inline void SetGravityFlag(const bool &bFlag)       { m_bGravity = bFlag; }     // �d�͂̃t���O
    inline void SetType(const CHARACTER_TYPE &type)     { m_type = type; }          // ���
    inline void SetUseShadow()                          { m_bUseShadow = true; }    // �e�̎g�p����

private:
    // private�֐�
    void ModelAnimeUpdate();                    // ���f���A�j���[�V����
    void Gravity();                             // �d��
    void SetMotion(const int &nMotionState);    // ���[�V�����̐ݒ�

    // �������z�֐�
    virtual void UpdateState() = 0;             // �L�����N�^�[���
    virtual void CreateModel() = 0;             // ���f������

    // �����o�ϐ�
    vector<CModelAnime*> m_apModelAnime;    // ���f���p�[�c�p�|�C���^
    CMotion *m_pMotion;                     // ���[�V�����N���X�̃|�C���^
    D3DXVECTOR3 m_pos;                      // ���W
    D3DXVECTOR3 m_posOld;                   // �Â����W
    D3DXVECTOR3 m_move;                     // �ړ���
    D3DXVECTOR3 m_rot;                      // ���݂̉�]
    D3DXVECTOR3 m_size;                     // �T�C�Y
    D3DXMATRIX m_mtxWorld;                  // ���[���h�}�g���b�N�X
    STATE m_State;                          // ���
    CHARACTER_TYPE m_type;                  // ���
    int m_nStateCounter;                    // ��Ԃ̃J�E���^�[
    int m_nParts;                           // �p�[�c��
    float m_fSpeed;                         // �ړ���
    bool m_bLanding;                        // ���n�t���O
    bool m_bUseShadow;                      // �e������t���O
    bool m_bGravity;                        // �d�͂�������t���O
};
#endif
