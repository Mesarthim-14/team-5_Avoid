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
#include "plane_jump.h"
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
CPlaneJump::CPlaneJump()
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
CPlaneJump::~CPlaneJump()
{
}

//=====================================================================
// ��������
// Author : toshiki
//=====================================================================
CPlaneJump * CPlaneJump::Create(const D3DXVECTOR3 & pos)
{
    CPlaneJump * pPlaneJump = new CPlaneJump;
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
HRESULT CPlaneJump::Init()
{
    CPlane::Init();
    return S_OK;
}

//=====================================================================
// �X�V����
// Author : toshiki
//=====================================================================
void CPlaneJump::Update()
{
    CPlane::Update();
    CPlayer * pPlayer = CManager::GetInstance()->GetPlayer();
    // �e�N�X�`���̐ݒ�
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_JUMP));
    m_nCnt++;
    // �\��������p�x��ݒ�
    SetRot(D3DXVECTOR3(0.8f, m_fRot, 0.0f));

    m_fSize = 0.08f;
    ScaleUp(m_fSize);
    if (m_nCnt >= 30)
    {
        // ���X�ɓ����ɂ��Ă���
        m_fColor -= 0.05f;
        SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColor));
        // ���S�ɓ����ɂȂ��������
        if (m_fColor <= 0.0f)
        {
            m_nCnt = 0;
            Uninit();
        }
    }
}

//=====================================================================
// �I������
// Author : toshiki
//=====================================================================
void CPlaneJump::Uninit()
{
    CPlane::Uninit();
}

//=====================================================================
// �`�揈��
// Author : toshiki
//=====================================================================
void CPlaneJump::Draw()
{
    CPlane::Draw();
}