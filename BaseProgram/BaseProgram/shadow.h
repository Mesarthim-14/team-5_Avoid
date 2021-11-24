#ifndef _SHADOW_H_
#define _SHADOW_H_
//=============================================================================
//
// �V���h�E�N���X�w�b�_�[ [shadow.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "scene.h"

//=========================================================================
// �O���錾
//=========================================================================
class CShadowVolume;
class CShadowPolygon;

//=========================================================================
// �N���X��`
//=========================================================================
class CShadow
{
public:
    CShadow();          // �R���X�g���N�^
    ~CShadow();         // �f�X�g���N�^

    static CShadow *Create(const LPD3DXMESH &pSrcMesh);                                                     // �C���X�^���X����
    HRESULT Init(const LPD3DXMESH &pSrcMesh);                                                               // ��������������
    void Uninit();                                                                                          // �I������
    void VolumeDraw();                                                                                      // �e�`�揈��
    void CreateShadow(const D3DXVECTOR3 &rot, const D3DXVECTOR3 &ShipRot, const D3DXMATRIX &ModelMtxWorld); // �e�̐���
    void CreateShadow(const D3DXVECTOR3 &rot, const D3DXMATRIX &ModelMtxWorld);                             // �e�̐���

    static void SetShadowStateStencil();    // �X�e���V���̐ݒ�
    static void SetShadowStencilTest();     // �X�e���V���e�X�g�ݒ�
    static void ReSetShadowStateStencil();  // �X�e���V����񃊃Z�b�g
    static void PolygonUninit();            // �`�揈��

private:
    CShadowVolume *m_pShadowVolume;     // �V���h�E�{�����[���̃|�C���^
    D3DXMATRIX m_ModelMtxWorld;         // ���f���̃��[���h���W�擾
    static CShadowPolygon *m_pPolygon;  // �|���S���̃|�C���^
    bool m_bDrawUpdate;                 // �`��̍X�V
};
#endif