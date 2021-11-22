#ifndef _SHADOW_VOLUME_H_
#define _SHADOW_VOLUME_H_
//=============================================================================
//
// �V���h�E�{�����[���N���X�w�b�_�[ [shadow_volume.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "main.h"

//=========================================================================
// �N���X��`
//=========================================================================
class CShadowVolume
{
public:
    CShadowVolume();    // �R���X�g���N�^
    ~CShadowVolume();   // �f�X�g���N�^

    static CShadowVolume *Create(const LPD3DXMESH &pSrcMesh);                   // �C���X�^���X����
    HRESULT Init(const LPD3DXMESH &pSrcMesh);                                   // ��������������
    void Uninit();                                                              // �I������
    void Draw();                                                                // �`�揈��
    HRESULT CreateShadow(const D3DXVECTOR3 &rot, const D3DXVECTOR3 &Rot);       // �e�̐���
    HRESULT CreateShadow(const D3DXVECTOR3 &Rot);                               // �e�̐���

private:
    // ���b�V�����̍\����
    struct MESHVERTEX
    {
        D3DXVECTOR3 pos, nor;
        FLOAT tu, tv;
    };
    // private�֐�
    void AddEdge(WORD* pEdges, DWORD& dwNumEdges, const WORD &v0, const WORD &v1);    // �G�b�W�̐ݒ�
    void CreateVolume(const vector<D3DXVECTOR3> &pos, const D3DXVECTOR3 &Lpos);       // �V���h�E�{�����[��

    // �����o�ϐ�
    D3DXVECTOR3 m_LightPos;         // ���C�g�̍��W
    DWORD m_dwNumVertices;          // ���_��
    D3DXVECTOR3 m_pVertice[32000];  // ���_�̔z��
    LPD3DXMESH m_pSrcMesh;          // ���b�V�����
    MESHVERTEX *m_MeshVertices;     // ���b�V���̏��
    WORD *m_pIndices;               // �C���f�b�N�X��
    DWORD m_dwNumFaces;             // ���b�V���̖ʂ̐�
    WORD *m_pEdges;                 // �G�b�W�̐�
};
#endif