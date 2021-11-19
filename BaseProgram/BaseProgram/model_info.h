#ifndef _MODEL_INFO_H_
#define _MODEL_INFO_H_
//=============================================================================
//
// ���f���̏��N���X[model_info.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "xfile.h"

//=============================================================================
// �O���錾
//=============================================================================
class CShadow;

//=============================================================================
//�K�w���f���N���X
//=============================================================================
class CModelInfo
{
public:
    // ���f���̎��
    enum MODEL_TYPE
    {
        MODEL_TYPE_NONE = 0,    // �ݒ�Ȃ�
        MODEL_TYPE_CHARACTER,   // �L�����N�^�[
        MODEL_TYPE_OBJECT,      // �I�u�W�F�N�g
        MODEL_TYPE_MAX          // �ő�l
    };

    CModelInfo(const MODEL_TYPE &type); // �R���X�g���N�^
    ~CModelInfo();                      // �f�X�g���N�^

    static CModelInfo *Create(const MODEL_TYPE &type);    // �C���X�^���X����

    HRESULT Init();                             // ����������
    void Uninit();                              // �I������
    void Draw(const D3DXVECTOR3 &rot);          // �`�揈��
    void ShadowDraw(const D3DXVECTOR3 &rot);    // �e�̕`��
    void CreateShadowPtr();                     // �e�̐���

    // Set�֐�
    inline void SetPos(const D3DXVECTOR3 &pos)              { m_pos = pos; }                            // ���W
    inline void SetRot(const D3DXVECTOR3 &rot)              { m_rot = rot; }                            // �����ݒ�
    inline void SetModel(const CXfile::MODEL &model)        { m_model = model; }                        // ���f�����̐ݒ�
    inline void SetMtxWorld(const D3DXMATRIX &mtxWorld)     { m_mtxWorld = mtxWorld; }                  // �}�g���N�X���[���h�ݒ�
    void SetModelStatus(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const CXfile::MODEL &model);    // ���f�����̐ݒ�
    D3DXMATRIX SetShadowInfo(const D3DXVECTOR3 &rot, const D3DXMATRIX &pParent);                        // �e�̏��̐ݒ�

    // Get���
    inline D3DXVECTOR3 &GetPos()       { return m_pos; }                // ���W���
    inline D3DXVECTOR3 &GetRot()       { return m_rot; }                // �p�x�̏��
    inline D3DXMATRIX GetMtxWorld()    { return m_mtxWorld; }           // ���[���h�}�g���N�X���
    inline D3DXMATRIX GetOldMtxWorld() { return m_OldMtxWorld; }        // �Â����[���h�}�g���N�X�̏��
    inline LPD3DXMESH GetMesh()        { return m_model.pMesh; }        // ���f�����擾
    inline LPD3DXBUFFER GetBuffMat()   { return m_model.pBuffMat; }     // �o�b�t�@���
    inline DWORD GetNumMat()           { return m_model.dwNumMat; }     // �}�g���N�X�̐�
    inline CXfile::MODEL GetModel()    { return m_model; }              // ���f���̏��
    inline CShadow* GetShadow()        { return m_pShadow; }            // �e�̃|�C���^
    D3DXVECTOR3 GetMtxPos();                                            // �}�g���N�X���W

private:
    // private�֐�
    void HasPtrDelete();            // �ێ��|�C���^�̊J������

    // �����o�ϐ�
    D3DXVECTOR3 m_pos;          // �ʒu
    D3DXVECTOR3 m_rot;          // ����
    D3DXMATRIX m_mtxWorld;      // ���[���h�}�g���b�N�X
    D3DXMATRIX m_OldMtxWorld;   // �Â����[���h���W
    CXfile::MODEL m_model;      // ���f�����
    MODEL_TYPE m_type;          // ���

    // �e�̐����p
    CShadow *m_pShadow; // �e�̃|�C���^
    bool m_bUseShadow;  // �e�̎g�p�t���O

    // ���f���̏�񃊃X�g
    static list<CModelInfo*> m_ModelInfoList[MODEL_TYPE_MAX];
};

#endif 