#ifndef _MODEL_H_
#define _MODEL_H_
//=============================================================================
//
// ���f���N���X [model.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "xfile.h"

//=============================================================================
// �O���錾
//=============================================================================
class CModelInfo;

//=============================================================================
// ���f���N���X
//=============================================================================
class CModel : public CScene
{
public:
    CModel(PRIORITY Priority);  // �R���X�g���N�^
    virtual ~CModel();          // �f�X�g���N�^

    virtual HRESULT Init();                                                 // ����������
    virtual void Uninit();                                                  // �I������
    virtual void Update();                                                  // �X�V����
    virtual void Draw();                                                    // �`�揈��
    static CModel *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);  // �C���X�^���X����

    // Get�֐�
    D3DXVECTOR3 GetPos()const;
    D3DXVECTOR3 GetRot()const;
    inline CModelInfo* GetModelInfo()const { return m_pModelInfo; } // ���f���̏��

protected:
    bool PlayerDisCollision(const float &fDistanse);    // �v���C���[�Ƃ̋����̓����蔻��

    // Set�֐�
    inline void SetMove(const D3DXVECTOR3 &move)        { m_move = move; }              // �ړ��ʂ̐ݒ�
    inline void SetSize(const D3DXVECTOR3 &size)        { m_size = size; }              // �T�C�Y�̐ݒ�
    inline void SetTexPattern(const int &TexPattern)    { m_nTexPattern = TexPattern; } // �e�N�X�`���̃p�^�[��
    inline void SetLife(const int &nLife)               { m_nLife = nLife; }            // ���C�t�̐ݒ�
    inline void SetScale(const D3DXVECTOR3 &scale)      { m_scale = scale; }            // �g�嗦

    inline D3DXVECTOR3 &GetMove()       { return m_move; }          // �ړ��ʂ̏��
    inline D3DXVECTOR3 GetSize()const   { return m_size; }          // �T�C�Y�̐ݒ�
    inline int GetTexPattern()const     { return m_nTexPattern; }   // �e�N�X�`��
    inline int GetLife()const           { return m_nLife; }         // ���C�t�̐ݒ�

private:
    // private�֐�
    void HasPtrDelete();    // �ێ��|�C���^�̊J������
    void CreateInfoPtr();   // ���̃|�C���^����

    // �����o�ϐ�
    CModelInfo* m_pModelInfo;   // ���f���̏��
    D3DXVECTOR3 m_move;         // �ړ���
    D3DXVECTOR3 m_size;         // �T�C�Y
    D3DXVECTOR3 m_scale;        // �g�嗦
    int m_nTexPattern;          // �e�N�X�`���̃p�^�[����
    int m_nLife;                // ���C�t
};
#endif 