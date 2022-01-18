//=========================================================
//
// �{�X��HP�o�[�N���X	[boss_hp_bar.cpp]
// Author : Konishi Yuuto
//
//=========================================================

//=========================================================
// �C���N���[�h
//=========================================================
#include "boss_hp_bar.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"

//=========================================================
// �}�N����`
//=========================================================
#define SIZE    (D3DXVECTOR3(635.0f, 12.0f, 0.0f))
#define POS     (D3DXVECTOR3((SCREEN_WIDTH / 2) - (598.0f * 0.5f), 90.0f, 0.0f))

//=========================================================
// �|���S������
//=========================================================
CBossHpBar * CBossHpBar::Create(const int& nLife)
{
    // �������m��
    CBossHpBar *pPtr = new CBossHpBar(PRIORITY_UI);

    if (pPtr)
    {
        pPtr->m_nGage = pPtr->m_nMaxGage = nLife;
        pPtr->Init();   // ������
    }

    return pPtr;
}

//=========================================================
// �R���X�g���N�^
//=========================================================
CBossHpBar::CBossHpBar(PRIORITY Priority) : CSceneBase(Priority)
{
    m_nMaxGage = 0;
    m_nGage = m_nMaxGage;
}

//=========================================================
// �f�X�g���N�^
//=========================================================
CBossHpBar::~CBossHpBar()
{
}

//=========================================================
// ����������
//=========================================================
HRESULT CBossHpBar::Init()
{
    // �e�N�X�`���̐ݒ�
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_BOSS_HP_BAR));

    // ����������
    CreateVertex(POS, SIZE);       // ���W�E�T�C�Y
    SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));	// �F�̐ݒ�

    return S_OK;
}

//=========================================================
// �I������
//=========================================================
void CBossHpBar::Uninit()
{
    // �I������
    CSceneBase::Uninit();
}

//=========================================================
// �X�V����
//=========================================================
void CBossHpBar::Update()
{

}

//=========================================================
// �`�揈��
//=========================================================
void CBossHpBar::Draw()
{
}

//=========================================================
// ���_�ݒ�
//=========================================================
void CBossHpBar::SetGageVertex()
{
    VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^
    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

    // ���_�o�b�t�@�����b�N
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // �o�[�̍��W�ƃT�C�Y
    D3DXVECTOR3 pos = GetPos();
    D3DXVECTOR3 size = GetSize();

    // HP���������ꍇ�A�摜�̉E������`�����߂�
    pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y - size.y, 0.0f);
    pVtx[1].pos = D3DXVECTOR3((pos.x + (size.x )*((float)m_nGage / m_nMaxGage)), pos.y - size.y, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(pos.x, pos.y + size.y, 0.0f);
    pVtx[3].pos = D3DXVECTOR3((pos.x + (size.x )*((float)m_nGage / m_nMaxGage)), pos.y + size.y, 0.0f);

    // ���_�f�[�^���A�����b�N����
    pVtxBuff->Unlock();
}

//=========================================================
// ���_�̐���
//=========================================================
void CBossHpBar::CreateVertex(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
    // �����_���[�̏����󂯎��
    LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;
    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;

    // ���_�o�b�t�@�̐���
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_2D,
        D3DPOOL_MANAGED,
        &pVtxBuff,
        nullptr);

    SetPos(pos);
    SetSize(size);

    //���_���ւ̃|�C���^
    VERTEX_2D *pVtx;

    // ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // HP���������ꍇ�A�摜�̉E������`�����߂�
    pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y - size.y, 0.0f);
    pVtx[1].pos = D3DXVECTOR3((pos.x + (size.x)*((float)m_nGage / m_nMaxGage)), pos.y - size.y, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(pos.x, pos.y + size.y, 0.0f);
    pVtx[3].pos = D3DXVECTOR3((pos.x + (size.x)*((float)m_nGage / m_nMaxGage)), pos.y + size.y, 0.0f);

    //rhw�̐ݒ�i�l��1.0�Őݒ肷��j
    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    //���_�J���[��ݒ�i0�`255�̒l�Őݒ肷��j
    pVtx[0].col = WhiteColor;
    pVtx[1].col = WhiteColor;
    pVtx[2].col = WhiteColor;
    pVtx[3].col = WhiteColor;

    //�e�N�X�`�����W�̐ݒ�
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

    //���_�f�[�^���A�����b�N����
    pVtxBuff->Unlock();

    // ���_����n��
    BindVtxBuff(pVtxBuff);
}

//=========================================================
// HP���Z
//=========================================================
void CBossHpBar::SubHp(const int& nNum)
{
    m_nGage -= nNum;
    SetGageVertex();
}


void CBossHpBar::Render()
{
    // Renderer�N���X����f�o�C�X���擾
    LPDIRECT3DDEVICE9 pD3DDevice = GET_RENDERER_DEVICE;

    //�A���t�@�e�X�g��L����
    pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

    // ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pD3DDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_2D));

    // ���_�t�H�[�}�b�g�̐ݒ�
    pD3DDevice->SetFVF(FVF_VERTEX_2D);

    // �e�N�X�`���̐ݒ�
    pD3DDevice->SetTexture(0, GetTexture());

    // �|���S���̕`��
    pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
        0,
        NUM_POLYGON);

    //�A���t�@�e�X�g�𖳌���
    pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

    // �e�N�X�`���̐ݒ�
    pD3DDevice->SetTexture(0, nullptr);

}
