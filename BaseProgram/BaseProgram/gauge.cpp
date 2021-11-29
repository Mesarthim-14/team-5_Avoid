//=====================================================================
//
//    �Q�[�W����[gauge.h]
//    Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "gauge.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "keyboard.h"

float CGauge::m_fHP = 0.0f;
float CGauge::m_fSave = 0.0f;
bool CGauge::m_bHitDown = false;
bool CGauge::m_bHitUp = false;
//=====================================================================
// �}�N����`
//=====================================================================
#define POS         (D3DXVECTOR3(80.0f,575.0f,0.0f))
#define SIZE        (D3DXVECTOR3(150.0f,450.0f,0.0f))
#define MAX_GAUGE   (100.0f)

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CGauge::CGauge()
{
    m_fHP = 60.0f;
    m_fDown = 0.0f;
    m_fUp = 0.0f;
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CGauge::~CGauge()
{

}

//=====================================================================
// ��������
//=====================================================================
CGauge * CGauge::Create()
{
    CGauge * pGauge = new CGauge;

    if (pGauge)
    {
        pGauge->SetSceneInfo(POS, SIZE);
        pGauge->Init();
        return pGauge;
    }
    return nullptr;
}

//=====================================================================
// ����������
//=====================================================================
HRESULT CGauge::Init()
{
    // �e�N�X�`���̐ݒ�
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_GAUGE));
    // �Q�[�W�̐ݒ菈��
    SetVertexGauge();
    return S_OK;
}

//=====================================================================
// �I������
//=====================================================================
void CGauge::Uninit()
{
    CScene2D::Uninit();
}

//=====================================================================
// �X�V����
//=====================================================================
void CGauge::Update()
{
    CScene2D::Update();
    // �e�X�g�E�Q�[�W�̑��������ۏ���
    SetDownUp();
}

//=====================================================================
// �`�揈��
//=====================================================================
void CGauge::Draw()
{
    CScene2D::Draw();
}

//=====================================================================
// �e�N�X�`�����
//=====================================================================
void CGauge::SetVertexGauge()
{
    // Renderer�N���X����f�o�C�X���擾
    LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;        // �o�b�t�@

                                                    // ���_�o�b�t�@�̐���
    pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_2D,
        D3DPOOL_MANAGED,
        &pVtxBuff,
        nullptr);

    // ���_����ݒ�
    VERTEX_2D *pVtx = nullptr;
    D3DXVECTOR3 pos = GetPos();
    D3DXVECTOR3 size = GetSize();
    D3DXCOLOR color = GetColor();
    // �Q�[�W�̗ʂ̌v�Z
    float fDown = MAX_GAUGE / m_fHP;

    // ���_�f�[�^�����b�N����
    pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // �e�N�X�`�����W�̐ݒ�
    pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f - (1.0f / fDown));
    pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f - (1.0f / fDown));
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

    size.y *= (1.0f / fDown);

    // ���_���W�̐ݒ�
    pVtx[0].pos = D3DXVECTOR3(pos.x - (size.x / 2.0f), pos.y - size.y, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(pos.x + (size.x / 2.0f), pos.y - size.y, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(pos.x - (size.x / 2.0f), pos.y, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(pos.x + (size.x / 2.0f), pos.y, 0.0f);

    // rhw�̐ݒ�
    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    // ���_�J���[�̐ݒ�
    pVtx[0].col = color;
    pVtx[1].col = color;
    pVtx[2].col = color;
    pVtx[3].col = color;

    // ���_�f�[�^���A�����b�N����
    pVtxBuff->Unlock();

    // ���_�o�b�t�@�̐ݒ�
    BindVtxBuff(pVtxBuff);
}

//=====================================================================
// �������ۏ���
//=====================================================================
void CGauge::SetDownUp()
{
    // ���炷����
    if (m_fHP >= 0.0f)
    {
        if (m_bHitDown)
        {
            // ���炵�����l
            m_fDown = GetHP();
            m_bHitDown = false;
        }
        if (m_fDown >= 0.0f)
        {
            m_fHP -= 1.0f;
            SetVertexGauge();
            m_fDown -= 1.0f;
            // 0�ȉ��ɍs���Ȃ��悤�ɂ���@
            if (m_fHP < 0.0f)
            {
                m_fHP = 0.0f;
            }
        }
    }
    // �����鏈��
    if (m_fHP <= MAX_GAUGE)
    {
        if (m_bHitUp)
        {
            // ���₵�����l
            m_fUp = GetHP();
            m_bHitUp = false;
        }
        // �w��̐��l���グ��
        if (m_fUp >= 0.0f)
        {
            m_fHP += 1.0f;
            SetVertexGauge();
            m_fUp -= 1.0f;
            // 100�ȏ�ɍs���Ȃ��悤�ɂ���
            if (m_fHP > 100.0f)
            {
                m_fHP = 100.0f;
            }
        }
    }
}