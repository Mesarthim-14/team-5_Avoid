//=====================================================================
//
//	�W�����v�G�t�F�N�g����[plane_jump.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
// Author : toshiki
//=====================================================================
#include "plane_jumpreservoir.h"
#include "manager.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"
#include "player.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define SIZE    (D3DXVECTOR3(1000.0f, 800.0f, 800.0f))
#define COLOR   (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

//=====================================================================
// �R���X�g���N�^
// Author : toshiki
//=====================================================================
CPlaneJumpReservoir::CPlaneJumpReservoir()
{
    m_pos = ZeroVector3;
    m_move = ZeroVector3;
    m_fSize = 0.0f;
    m_fColor = 1.0f;
    m_fRot = 0.0f;
    m_nCnt = 0;
}

//=====================================================================
// �f�X�g���N�^
// Author : toshiki
//=====================================================================
CPlaneJumpReservoir::~CPlaneJumpReservoir()
{
}

//=====================================================================
// ��������
// Author : toshiki
//=====================================================================
CPlaneJumpReservoir * CPlaneJumpReservoir::Create(const D3DXVECTOR3 & pos)
{
    CPlaneJumpReservoir * pPlaneJump = new CPlaneJumpReservoir;
    if (pPlaneJump != nullptr)
    {
        pPlaneJump->SetSceneInfo(pos, SIZE);
        pPlaneJump->Init();
        return pPlaneJump;
    }

    return nullptr;
}

//=====================================================================
// ����������
// Author : toshiki
//=====================================================================
HRESULT CPlaneJumpReservoir::Init()
{
    CPlane::Init();
    SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
    return S_OK;
}

//=====================================================================
// �X�V����
// Author : toshiki
//=====================================================================
void CPlaneJumpReservoir::Update()
{
    CPlane::Update();
    CPlayer * pPlayer = CManager::GetInstance()->GetPlayer();
    // �e�N�X�`���̐ݒ�
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_JUMP));
    // �\��������p�x��ݒ�
    SetRot(D3DXVECTOR3(0.8f, m_fRot, 0.0f));

    // �v���C���[�̈ʒu���������Ă���
    m_pos = pPlayer->GetPos();
    // �v���C���[�̈ʒu�ɒǏ]
    m_pos += m_move;
    m_nCnt++;
    m_fSize = 0.07f;
    ScaleDown(m_fSize);
    if (m_nCnt >= 10)
    {
        // ���X�ɓ����ɂ��Ă���
        m_fColor -= 0.1f;
        SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColor));
        // ���S�ɓ����ɂȂ��������
        if (m_fColor <= 0.0f)
        {
            m_nCnt = 0;
            Uninit();
        }
    }
    // �ʒu����ݒ�
    SetPos(D3DXVECTOR3(m_pos.x, m_pos.y - 200.0f, m_pos.z));
}

//=====================================================================
// �I������
// Author : toshiki
//=====================================================================
void CPlaneJumpReservoir::Uninit()
{
    CPlane::Uninit();
}

//=====================================================================
// �`�揈��
// Author : toshiki
//=====================================================================
void CPlaneJumpReservoir::Draw()
{
    CPlane::Draw();
}
