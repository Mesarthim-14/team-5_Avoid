//=====================================================
//
// �r���{�[�h�N���X [billboard.cpp]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "billboard.h"
#include "manager.h"
#include "renderer.h"

//=====================================================
// �R���X�g���N�^
//=====================================================
CBillboard::CBillboard(PRIORITY Priority) : CScene3D(Priority)
{
    m_bBlend = false;
}

//=====================================================
// �`�揈��
//=====================================================
void CBillboard::Draw()
{
    // �f�o�C�X���擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    //�v�Z�p�̃}�g���N�X
    D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxWorld;

    // ���C�g����
    pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

    // �A���t�@�e�X�g��L�͉�
    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

    // ���Z����
    if (m_bBlend)
    {
        // ���Z�������s��
        pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);     // a�f�X�e�B�l�[�V�����J���[
    }

    // �A���t�@�e�X�g
    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_ALPHAREF, GetAlphaTestNum());
    pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

    // �e�N�X�`���̐ݒ�
    pDevice->SetTexture(0, GetTexture());
    
    // ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

    // ���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_3D);

    //���[���h�}�g���N�X�̏�����
    D3DXMatrixIdentity(&mtxWorld);

    // �T�C�Y�擾
    D3DXVECTOR3 size = GetSize();

    // �T�C�Y�𔽉f
    D3DXMatrixScaling(&mtxScale, size.x, size.y, 1.0f);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

    // ��]�̋t�s��̐���
    pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
    D3DXMatrixInverse(&mtxWorld, nullptr, &mtxRot);
    mtxWorld._41 = 0;
    mtxWorld._42 = 0;
    mtxWorld._43 = 0;

    // �T�C�Y���
    D3DXVECTOR3 pos = GetPos();

    // �ʒu�𔽉f�A���[���h�}�g���N�X�ݒ�A�|���S���`��
    D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

    // ���[���h�}�g���N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

    // �|���S���̕`��
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

    // ���Z�������s������
    if (m_bBlend)
    {
        pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);    // a�f�X�e�B�l�[�V�����J���[
    }

    // �A���t�@�e�X�g������
    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

    // ���C�g�L��
    pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

    // �e�N�X�`���̐ݒ�
    pDevice->SetTexture(0, nullptr);

}