//=====================================================================
//
//    �p�[�e�B�N������[particlepop.h]
//    Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
// Author : toshiki
//=====================================================================
#include "particleaura.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"
#include "ghost.h"
#include "player.h"

//=====================================================================
// �}�N����`
// Author : toshiki
//=====================================================================
#define SIZE         (D3DXVECTOR3(1500.0f, 1500.0f, 1500.0f))
#define ANGLE        (3.0f)
#define SPEED        (5.0f)
#define RANDOM       (3.14f)
#define LIFE         (90)
#define COLOR        (D3DXCOLOR(1.0f,1.0f,1.0f,0.4f))

#define FOLLOW_END_DISTANCE (800.0f)                                // �Ǐ]��؂�
#define RISE_SPEED          (30.0f)                                 // �㏸���x
#define RISE_TIME           (120)                                   // �I���܂ł̎���
#define END_TIME            (250)                                   // �I���܂ł̎���
#define PLAYER_ADD_HEIGHT   (500.0f)                                // �v���C���[��K���ɗʑ���

//=====================================================================
// �R���X�g���N�^
// Author : toshiki
//=====================================================================
CParticleAura::CParticleAura()
{
    m_fAngle = 0.0f;
    m_nLife = 0;
    m_bFollow = false;
    m_bEnd = false;
    m_bCaution = false;
    m_nEndCount = 0;
}

//=====================================================================
// �f�X�g���N�^
// Author : toshiki
//=====================================================================
CParticleAura::~CParticleAura()
{

}

//=====================================================================
// ��������
// Author : toshiki
//=====================================================================
CParticleAura * CParticleAura::Create()
{
    CParticleAura * pParticle = new CParticleAura;

    if (pParticle)
    {
        pParticle->SetSceneInfo(D3DXVECTOR3(0.0f, 5000.0f, 0.0f), SIZE);
        pParticle->Init();
        return pParticle;
    }
    return nullptr;
}

//=====================================================================
// ����������
// Author : toshiki
//=====================================================================
HRESULT CParticleAura::Init()
{
    CParticleInfo::Init();
    SetParticle();
    return S_OK;
}

//=====================================================================
// �X�V����
// Author : toshiki
//=====================================================================
void CParticleAura::Update()
{
    CParticleInfo::Update();
    //// �v���C���[��T������
    //Tracking();
    //// �ړ�����
    //Move();
}

//=====================================================================
// �I������
// Author : toshiki
//=====================================================================
void CParticleAura::Uninit()
{
    CParticleInfo::Uninit();
}

//=====================================================================
// �`�揈��
// Author : toshiki
//=====================================================================
void CParticleAura::Draw()
{
    CParticleInfo::Draw();
}

//=====================================================================
// �p�[�e�B�N���̐ݒ�
// Author : toshiki
//=====================================================================
void CParticleAura::SetParticle()
{
    // �e�N�X�`���̐ݒ�
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PARTICLE));
    SetLife(false);
    // �F�̐ݒ�
    SetColor(COLOR);
}

//=====================================================================
// �p�[�e�B�N���̈ړ�
// Author : toshiki
//=====================================================================
void CParticleAura::Move()
{
    // �Ǐ]�t���O
    if (m_bFollow)
    {
        // �Ǐ]
        if (Follow())
        {
            // ���̋����ɋ߂Â�����
            if (CLibrary::CalDistance(
                CManager::GetInstance()->GetPlayer()->GetPos(), GetPos()) <= FOLLOW_END_DISTANCE)
            {
                m_bFollow = false;
                m_bEnd = true;
            }
        }
    }

    if (m_bEnd)
    {
        m_nEndCount++;
        if (m_nEndCount >= RISE_TIME)
        {
            // �㏸
            Rise();
            if (m_nEndCount >= END_TIME)
            {
                // ������
                Uninit();
                return;
            }
        }
    }

}

//=====================================================================
// �p�[�e�B�N���̏㏸
// Author : toshiki
//=====================================================================
void CParticleAura::Rise()
{
    D3DXVECTOR3 move = ZeroVector3;
    move.y = RISE_SPEED;
    SetMove(move);
}

//=====================================================================
// �p�[�e�B�N���̒Ǐ]�ݒ�
// Author : toshiki
//=====================================================================
void CParticleAura::Attack()
{
    if (!m_bFollow && !m_bEnd)
    {
        m_bFollow = true;
    }
}

//=====================================================================
// �p�[�e�B�N���̒Ǐ]�ݒ�
// Author : toshiki
//=====================================================================
void CParticleAura::Tracking()
{
    if (Search())
    {
        if (!m_bCaution)
        {
            m_bCaution = true;
            m_nCautionCounter = 0;
        }
    }
    // �x�����o�Ă�Ƃ�
    if (m_bCaution)
    {
        m_nCautionCounter++;
        if (m_nCautionCounter == 60)
        {
            m_bCaution = false;
            Attack();
        }
    }
}