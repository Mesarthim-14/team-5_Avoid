//=============================================================================
//
// 3D�|���S���N���X [plane.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "plane.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"

//=============================================================================
// �`�揈��
//=============================================================================
void CPlane::Draw()
{
    // �f�o�C�X���擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);         // ���C�g����
    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);   // �A���t�@�e�X�g��L�͉�

    // �}�g���N�X�v�Z
    D3DXMATRIX mtxWorld;
    CLibrary::ConfigMatrix(&mtxWorld, GetPos(), GetRot());

    // ���[���h�}�g���N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
    SetMtxWorld(mtxWorld);

    // �e�N�X�`���̐ݒ�
    pDevice->SetTexture(0, GetTexture());

    // ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

    // ���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_3D);

    // �|���S���̕`��
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

    // �A���t�@�e�X�g������
    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

    // ���C�g�L��
    pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}