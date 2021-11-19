#ifndef _SCENE3D_H_
#define _SCENE3D_H_
//=============================================================================
//
// 3D�|���S���N���X�w�b�_�[ [scene3D.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "scene_base.h"

//=========================================================================
// 3D�|���S���N���X
//=========================================================================
class CScene3D :public CSceneBase
{
public:
    CScene3D(PRIORITY Priority = PRIORITY_EFFECT);  // �R���X�g���N�^
    virtual ~CScene3D();                            // �f�X�g���N�^
    
    virtual HRESULT Init();                        // ����������
    virtual void Uninit();                         // �I������
    virtual void Update();                         // �X�V����
    virtual void Draw() = 0;                       // �`�揈��

protected:
    void SetVertexPos();    // ���W�̍X�V

    // Set�֐�
    void SubAlpha(const float &fAlphaNum);                                                  // �����x�̌��Z
    void InitAnimation(const int &nCounterAnim, const int &nPatternAnim, const int &nLoop); // �A�j���[�V������񏉊���
    void SetColor(const D3DXCOLOR &color);                                                  // �J���[�̐ݒ�
    void ScaleUp(const float &fScale);                                                      // �g�又��
    inline void SetMove(const D3DXVECTOR3 &move)        { m_move = move; }                  // �ړ���
    inline void SetAlpha(const bool &bAlpha)            { m_bAlpha = bAlpha; }              // �A���t�@�e�X�g
    inline void SetAlphaNum(const int &nAlphaNum)       { m_nAlphaTestNum = nAlphaNum; }    // �A���t�@�e�X�g�̒l
    inline void SetBlend(const bool &bBlend)            { m_bBlend = bBlend; }              // ���Z����
    inline void SetMtxWorld(const D3DXMATRIX mtxWorld)  { m_mtxWorld = mtxWorld; }          // ���[���h�}�g���N�X�̐ݒ�

    // Get�֐�
    inline D3DXMATRIX GetMtxWorld()const    { return m_mtxWorld; }      // ���[���h�}�g���N�X
    inline int GetAlphaTestNum()const       { return m_nAlphaTestNum; } // �A���t�@�e�X�g�̒l

private:
    // private�֐�
    void CreateVertex();    // ���_�̐ݒ�
    void UpdateAnimation(); // �A�j���[�V�����̍X�V

    // �����o�ϐ�
    D3DXMATRIX m_mtxWorld;  // ���[���h�}�g���N�X
    D3DXVECTOR3 m_move;     // �ړ���
    int m_nLife;            // ���C�t
    int m_nAlphaTestNum;    // �����̒l
    float m_fScaleNum;      // �g��l
    float m_fAlphaNum;      // �����x
    bool m_bAlpha;          // �������g���t���O
    bool m_bBlend;          // ���Z����
};
#endif