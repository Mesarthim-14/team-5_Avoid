#ifndef _TEXTURE_ANIMATION_H_
#define _TEXTURE_ANIMATION_H_
//=============================================================================
//
// �e�N�X�`���̃A�j���[�V�����N���X [texture_animation.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CTextureAnimation
{
public:
    CTextureAnimation();    // �R���X�g���N�^
    ~CTextureAnimation();    // �f�X�g���N�^

    static CTextureAnimation *Create(const D3DXVECTOR2 m_tex[NUM_VERTEX]);  // �C���X�^���X����
    void Update();                                                          // �X�V����

    void InitAnimationInfo(const int &nPatternNum, const int &nSpeed, const int &nLoop);    // �A�j���[�V�����̏��ݒ�
    void InitScroll(const int &nSpeed, const float &fDivision);                             // �X�N���[�����̐ݒ�
    void UpdateAnimation();                                                                 // �A�j���[�V�����̍X�V
    void UpdateScroll();                                                                    // �X�N���[���̍X�V
    
    // Set�֐�
    inline void SetCountAnim(const int &nCountAnim)         { m_nCountAnim = nCountAnim; }              // �A�j���[�V�����̃J�E���^�ݒ�
    inline void SetCountPattern(const int &nCountPattern)   { m_nCountAnimPattern = nCountPattern; }    // �A�j���[�V�����p�^�[���̃J�E���g
    inline void SetScrollCounter(const int &nScrollCounter) { m_nScrollCounter = nScrollCounter; }      // �X�N���[���̏��
    inline void SetUpdateFlag(const bool &bFlag)            { m_bUpdate = bFlag; }                      // �X�V�̃t���O�ݒ�

    // Get�֐�
    D3DXVECTOR2 GetTex(const int &nCount)   { return m_tex[nCount]; }   // �e�N�X�`�����W�̏��
    bool GetEnd()const                      { return m_bEnd; }          // �I���t���O
    bool GetUpdate()const                   { return m_bUpdate; }       // �X�V���ꂽ���̃t���O

private:
    D3DXVECTOR2 m_tex[NUM_VERTEX];  // ���_�����̃e�N�X�`�����
    int m_nCountAnim;               // �A�j���[�V�����̃J�E���^
    int m_nCountAnimPattern;        // �A�j���[�V�����̃p�^�[��
    int m_nPatternNum;              // �A�j���[�V�����̃J�E���^�[
    int m_nAnimSpeed;               // �A�j���[�V�����̃p�^�[����
    int m_nLoop;                    // ���[�v���邩�ǂ���
    int m_nSpeedTexture;            // �e�N�X�`���̈ړ����x
    int m_nScrollCounter;           // �X�N���[���̃J�E���^
    float m_fDivisionCounter;       // �X�N���[���̃J�E���^�[
    float m_fDivisionBaseNum;       // �X�N���[���̊Ԋu
    bool m_bEnd;                    // �I���t���O
    bool m_bUpdate;                 // �e�N�X�`�����X�V���ꂽ���̃t���O
};

#endif