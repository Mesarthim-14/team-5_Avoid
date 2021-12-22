//=============================================================================
//
// �~�����b�V���N���X [mesh_tube.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "mesh_tube.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMeshTube::CMeshTube(PRIORITY Priority) :CMesh3d(Priority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshTube::~CMeshTube()
{
}

//=============================================================================
// �|���S������
//=============================================================================
CMeshTube * CMeshTube::Create(const D3DXVECTOR3 &pos, const MESH_TYPE &MeshNum)
{
    // �������m��
    CMeshTube *pMeshCylinder = new CMeshTube;

    // ����������
    if (pMeshCylinder != nullptr)
    {
        pMeshCylinder->SetMeshNum(MeshNum);         // ���p�`��
        pMeshCylinder->Init();                      // ���W�E�T�C�Y
    }

    return pMeshCylinder;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshTube::Init(void)
{
    // Renderer�N���X����f�o�C�X���擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
    VERTEX_3D *pVtx = nullptr;

    D3DXVECTOR3 pos = GetPos();
    // ���[�J���ϐ�
    int nCount = 0;         // for���p
    int nCntIndex = 0;      // ���_�̐����ԍ�
    int nCntH = 0;          // �c�̒��_�J�E���^
    int nCntV = 0;          // ���̒��_�J�E���^

                            // ���_�̐�
    int nWidth = GetMesh3D(GetMeshNum()).CylinderNum.nNumX;
    int nHeight = GetMesh3D(GetMeshNum()).CylinderNum.nNumY;

    // ���b�V���̃T�C�Y�ݒ�
    D3DXVECTOR2 MeshSize = D3DXVECTOR2(GetMesh3D(GetMeshNum()).size.x, GetMesh3D(GetMeshNum()).size.y);

    // �l�̏�����
    SetNumVertex((nWidth + 1) * (nHeight + 1));
    SetNumIndex((nWidth + 1) * nHeight * 2 + (nHeight - 1) * 2);            // 5*(4*2)+3*2	46
    SetNumPolygon(nWidth * nHeight * 2 + (nWidth - 1) * 4);                 // 4*8+3*4	44	36
    D3DXVECTOR2 OneSize = D3DXVECTOR2(MeshSize.x * 2 / nWidth, MeshSize.y * 2 / nHeight);
    SetOneSize(OneSize);		// 24000/4

                                // �o�b�t�@�̐錾
    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;
    LPDIRECT3DINDEXBUFFER9 pIdxBuff = nullptr;

    // �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * GetNumVertex(),
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_3D,
        D3DPOOL_MANAGED,
        &pVtxBuff,
        nullptr);

    // �C���f�b�N�X�o�b�t�@����
    pDevice->CreateIndexBuffer(sizeof(WORD) * GetNumIndex(),
        D3DUSAGE_WRITEONLY,
        D3DFMT_INDEX16,
        D3DPOOL_MANAGED,
        &pIdxBuff,
        nullptr);

    // ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    for (nCntV = 0; nCntV < nHeight + 1; nCntV++)
    {
        for (nCntH = 0; nCntH < nWidth + 1; nCntH++)
        {
            // ���_�̐ݒ�
            pVtx[(nCntV * (nWidth + 1)) + nCntH].pos = D3DXVECTOR3(
                pos.x + MeshSize.x*cosf(D3DXToRadian((360 / (nWidth))*nCntH)),
                pos.y + (nCntV * MeshSize.y),
                pos.z + MeshSize.x*sinf(D3DXToRadian((360 / (nWidth))*nCntH)));

            // �@���x�N�g���̐ݒ�
            pVtx[(nCntV * (nWidth + 1)) + nCntH].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

            // �F�̐ݒ�
            pVtx[(nCntV * (nWidth + 1)) + nCntH].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

            // �e�N�X�`�����W�̐ݒ�
            pVtx[(nCntV * (nWidth + 1)) + nCntH].tex = D3DXVECTOR2(float(nCntH), float(nCntV));
        }
    }

    // ���_�f�[�^���A�����b�N����
    pVtxBuff->Unlock();

    // �o�b�t�@����n��
    BindVtxBuff(pVtxBuff);

    // �C���f�b�N�X�o�b�t�@�̐ݒ�
    WORD *pIdx = nullptr;

    // �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
    pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

    // �C���f�b�N�X��
    int nNumIndex = GetNumIndex();
    for (nCount = 0, nCntIndex = 0; nCount < nNumIndex; nCount += 2)
    {
        if (((nCount + 2) % (((nWidth + 1) * 2) + 2)) == 0 && nCount != 0)
        {
            // �C���f�b�N�X�̐ݒ�
            pIdx[nCount] = nCntIndex - 1;

            // �C���f�b�N�X�̐ݒ�
            pIdx[nCount + 1] = nWidth + nCntIndex + 1;
        }
        else
        {
            // �C���f�b�N�X�̐ݒ�
            pIdx[nCount] = nWidth + nCntIndex + 1;

            // �C���f�b�N�X�̐ݒ�
            pIdx[nCount + 1] = nCntIndex;

            nCntIndex++;
        }

    }

    // ���_�f�[�^���A�����b�N����
    pIdxBuff->Unlock();

    // �C���f�b�N�X�o�b�t�@��n��
    BindIdxBuff(pIdxBuff);

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshTube::Uninit(void)
{
    // �폜�t���O
    Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshTube::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshTube::Draw(void)
{
    // �e�N���X�`�揈��
    CMesh3d::Draw();
}