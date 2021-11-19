#ifndef _MOTION_H_
#define _MOTION_H_
//=============================================================================
//
// ���[�V�����N���X�w�b�_�[ [motion.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "xfile.h"
#include "modelanime.h"

//=============================================================================
// ���[�V�����N���X
//=============================================================================
class CMotion
{
public:
    CMotion();        // �R���X�g���N�^
    ~CMotion();        // �f�X�g���N�^

    static CMotion *Create(const string &cFileName);

    void SetMotion(const int &nMotion, const int &nMaxParts, const vector<CModelAnime*> pModelAnime);   // ���[�V�����̐ݒ�
    void UpdateMotion(const int &nMaxParts, const vector<CModelAnime*> pModelAnime);                    // ���[�V�����̍X�V

    // Get�֐�
    inline int GetMotionState()    { return m_nMotionState; }   // ���[�V�������
    inline int GetKey()            { return m_nKey; }           // �L�[�̏��
    inline int GetCountMotion()    { return m_nCountMotion; }   // ���[�V�����̃J�E���g

private:
    // �e�v�f�̃L�[���
    struct KEY
    {
        float fPosX;
        float fPosY;
        float fPosZ;
        float fRotX;
        float fRotY;
        float fRotZ;
    };

    //    �L�[���̍\����
    struct KEY_INFO
    {
        int nFrame;         // �t���[����
        vector<KEY> aKey;   // �e�p�[�c�̃L�[���
    };

    // ���[�V�������̍\����
    struct Motion_Info
    {
        bool bLoop;                 // ���[�v���邩�ǂ���
        int nNumKey;                // �L�[��
        vector<KEY_INFO> aKeyInfo;  // �L�[���
    };

    // private�֐�
    HRESULT ReadMotionFile(const string &cFileName);    // ���[�V�����f�[�^��ǂݍ���

    // ���[�V�����p�ϐ�
    vector<Motion_Info> m_Motion;   // ���[�V�������
    KEY_INFO *m_apKeyInfo;          // �L�[���̃|�C���^
    int m_nMotionState;             // ���[�V�����̏��
    int m_nNumKey;                  // �L�[�̑���
    int m_nCountMotion;             // ���[�V�����J�E���^�[
    int m_nMotionInterval;          // ���[�V�����̃C���^�[�o��
    int m_nKey;                     // ���݃L�[��No
    bool m_bMotionPlaing;           // ���[�V�����̍Đ�
    D3DXVECTOR3 m_diffPos;          // �ύX���W
    D3DXVECTOR3 m_diffRot;          // �ύX�p�x
};

#endif 