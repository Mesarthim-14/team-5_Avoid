//=============================================================================
//
// �V�[��3D�N���X [scene3D.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"
#include "texture_animation.h"
#include "library.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene3D::CScene3D(PRIORITY Priority) : CSceneBase(Priority)
{
    m_fScaleNum = 0.0f;
    m_nAlphaTestNum = 0;
    m_bAlpha = false;
    m_fAlphaNum = 0.0f;
    m_move = ZeroVector3;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene3D::~CScene3D()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene3D::Init()
{
    // ���_�̐���
    CreateVertex();

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene3D::Uninit()
{
    CSceneBase::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene3D::Update()
{
    // �ړ��ʉ��Z
    GetPos() += m_move;
}

//=============================================================================
// ���_�̐���
//=============================================================================
void CScene3D::CreateVertex()
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();    // �f�o�C�X�̎擾
    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;                                         // ���_�o�b�t�@�ϐ��̐錾

    //���_�o�b�t�@�̐���
    pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX,
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_3D,
        D3DPOOL_MANAGED,
        &pVtxBuff,
        nullptr);

    D3DXVECTOR3 pos = GetPos();
    D3DXVECTOR3 size = GetSize();
    VERTEX_3D*pVtx = nullptr;

    //���_�o�b�t�@�����b�N
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //���_���W�ݒ�̐ݒ�
    pVtx[0].pos = D3DXVECTOR3(-(size.x / 2), (size.y / 2), (size.z / 2));
    pVtx[1].pos = D3DXVECTOR3((size.x / 2), (size.y / 2), (size.z / 2));
    pVtx[2].pos = D3DXVECTOR3(-(size.x / 2), -(size.y / 2), -(size.z / 2));
    pVtx[3].pos = D3DXVECTOR3((size.x / 2), -(size.y / 2),    -(size.z / 2));

    //�e���_�̖@���̐ݒ�
    pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    //���_�J���[�̐ݒ�
    pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

    //�e���_�̖@���̐ݒ�
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

    //���_�o�b�t�@�̃A�����b�N
    pVtxBuff->Unlock();

    // �o�b�t�@�̐ݒ�
    BindVtxBuff(pVtxBuff);
}

//=============================================================================
// ���W�ݒ�(���W�X�V�p)
//=============================================================================
void CScene3D::SetVertexPos()
{
    // ���_����ݒ�
    VERTEX_3D *pVtx = nullptr;
    D3DXVECTOR3 size = GetSize();

    // �o�b�t�@�擾
    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

    // ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //���_���W�ݒ�̐ݒ�
    pVtx[0].pos = D3DXVECTOR3(-(size.x / 2), +(size.y / 2),(size.z / 2));
    pVtx[1].pos = D3DXVECTOR3(+(size.x / 2), +(size.y / 2),(size.z / 2));
    pVtx[2].pos = D3DXVECTOR3(-(size.x / 2), -(size.y / 2),-(size.z / 2));
    pVtx[3].pos = D3DXVECTOR3(+(size.x / 2), -(size.y / 2),-(size.z / 2));

    // ���_�o�b�t�@���A�����b�N����
    pVtxBuff->Unlock();
}

//=============================================================================
// �F�̐ݒ�
//=============================================================================
void CScene3D::SetColor(const D3DXCOLOR &col)
{
    // �F��ς���
    CSceneBase::SetColor(col);

    // �o�b�t�@�擾
    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
    VERTEX_3D*pVtx = nullptr;

    //���_�o�b�t�@�����b�N
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j
    pVtx[0].col = col;
    pVtx[1].col = col;
    pVtx[2].col = col;
    pVtx[3].col = col;

    //���_�o�b�t�@�̃A�����b�N
    pVtxBuff->Unlock();
}

//=============================================
// �A�j���[�V�������擾
//=============================================
void CScene3D::InitAnimation(const int &nCounterAnim, const int &nPatternAnim, const int &nLoop)
{
    // �o�b�t�@�擾
    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
    VERTEX_3D *pVtx = nullptr;

    // ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //�e�N�X�`�����W���X�V
    pVtx[0].tex = D3DXVECTOR2((float)(1.0f / nPatternAnim)*(float)nPatternAnim, 0.0f);
    pVtx[1].tex = D3DXVECTOR2((float)(1.0f / nPatternAnim)*(float)nPatternAnim + (float)(1.0f / nPatternAnim), 0.0f);
    pVtx[2].tex = D3DXVECTOR2((float)(1.0f / nPatternAnim)*(float)nPatternAnim, 1.0f);
    pVtx[3].tex = D3DXVECTOR2((float)(1.0f / nPatternAnim)*(float)nPatternAnim + (float)(1.0f / nPatternAnim), 1.0f);

    // �e�N�X�`�����W��n��
    D3DXVECTOR2 tex[NUM_VERTEX] = {};
    for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        tex[nCount] = pVtx[nCount].tex;
    }

    // �e�N�X�`���A�j���[�V��������
    CTextureAnimation *pTextureAnimation = CTextureAnimation::Create(tex);
    pTextureAnimation->InitAnimationInfo(nCounterAnim, nPatternAnim, nLoop);
    SetTextureAnimationPtr(pTextureAnimation);

    // ���_�o�b�t�@���A�����b�N����
    pVtxBuff->Unlock();
}

//=============================================
// �A�j���[�V�����X�V�֐�
//=============================================
void CScene3D::UpdateAnimation()
{
    // �e�N�X�`���|�C���^�擾
    CTextureAnimation *pTextureAnimation = GetTextureAnimationPtr();
    if (pTextureAnimation)
    {
        // �e�N�X�`�����X�V����Ă�����
        if (pTextureAnimation->GetUpdate())
        {
            // �o�b�t�@�擾
            LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
            VERTEX_3D *pVtx = nullptr;

            // ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
            pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

            // �e�N�X�`�����W�̐ݒ�
            for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
            {
                pVtx[nCount].tex = pTextureAnimation->GetTex(nCount);
            }

            // ���_�o�b�t�@���A�����b�N����
            pVtxBuff->Unlock();
        }
    }
}

//======================================================
// �g��֐�
//======================================================
void CScene3D::ScaleUp(const float &fScaleUp)
{
    // �T�C�Y�擾
    D3DXVECTOR3 size = GetSize();

    m_fScaleNum += fScaleUp;

    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();    // �o�b�t�@�擾
    VERTEX_3D *pVtx = nullptr;                            //���_���ւ̃|�C���^

    //���_�f�[�^�͈͂����b�N���A���_�o�b�t�@�ւ̃|�C���^������
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // ���_���W�̐ݒ�
    pVtx[0].pos = D3DXVECTOR3(-(size.x * m_fScaleNum), +(size.y * m_fScaleNum), (size.z * m_fScaleNum));
    pVtx[1].pos = D3DXVECTOR3(+(size.x * m_fScaleNum), +(size.y * m_fScaleNum), (size.z * m_fScaleNum));
    pVtx[2].pos = D3DXVECTOR3(-(size.x * m_fScaleNum), -(size.y * m_fScaleNum), -(size.z * m_fScaleNum));
    pVtx[3].pos = D3DXVECTOR3(+(size.x * m_fScaleNum), -(size.y * m_fScaleNum), -(size.z * m_fScaleNum));

    //���_�f�[�^���A�����b�N
    pVtxBuff->Unlock();
}

//=============================================================================
// �����x�̌��Z
//=============================================================================
void CScene3D::SubAlpha(const float &fAlphaNum)
{
    // �F�̏��
    D3DXCOLOR col = GetColor();

    m_fAlphaNum = fAlphaNum;

    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();    // �o�b�t�@�擾
    VERTEX_3D*pVtx;    //���_���ւ̃|�C���^

    //���_�f�[�^�͈͂����b�N���A���_�o�b�t�@�ւ̃|�C���^������
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        //���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j
        pVtx[nCount].col = D3DXCOLOR(col.r, col.g, col.b, col.a - m_fAlphaNum);
    }

    //���_�f�[�^���A�����b�N
    pVtxBuff->Unlock();
}