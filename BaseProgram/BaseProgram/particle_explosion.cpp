//=====================================================================
//
//	�p�[�e�B�N������[particle.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
// Author : toshiki
//=====================================================================
#include "particle_explosion.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"
#include "texture_animation.h"

D3DXVECTOR3 CParticleExplosion::m_Rot = ZeroVector3;
//=====================================================================
// �}�N����`
// Author : toshiki
//=====================================================================
#define POS         (ZeroVector3)
#define SIZE        (D3DXVECTOR3(1600.0f, 1600.0f, 0.0f))
#define SPEED       (7.0f)
#define RANDOM      (3.14f)
#define LIFE        (200)
#define COLOR       (D3DXCOLOR(1.0f,1.0f,1.0f,m_fColor))

//=====================================================================
// �R���X�g���N�^
// Author : toshiki
//=====================================================================
CParticleExplosion::CParticleExplosion()
{
    m_fAngle = 0.0f;
    m_fSpeed = 0.0f;
    m_fColor = 1.0f;
    m_nCnt = 0;
}

//=====================================================================
// �f�X�g���N�^
// Author : toshiki
//=====================================================================
CParticleExplosion::~CParticleExplosion()
{

}

//=====================================================================
// ��������
// Author : toshiki
//=====================================================================
CParticleExplosion * CParticleExplosion::Create(const D3DXVECTOR3 &pos)
{
    CParticleExplosion * pParticle = new CParticleExplosion;

    if (pParticle != nullptr)
    {
        pParticle->SetSceneInfo(pos, SIZE);
        pParticle->Init();
        return pParticle;
    }
    return nullptr;
}

//=====================================================================
// ����������
// Author : toshiki
//=====================================================================
HRESULT CParticleExplosion::Init(void)
{
    CParticleInfo::Init();
    SetParticle();
    return S_OK;
}

//=====================================================================
// �X�V����
// Author : toshiki
//=====================================================================
void CParticleExplosion::Update(void)
{
    CParticleInfo::Update();
    SetParticleColor();
    SetEffect();
}

//=====================================================================
// �I������
// Author : toshiki
//=====================================================================
void CParticleExplosion::Uninit(void)
{
    CParticleInfo::Uninit();
}

//=====================================================================
// �`�揈��
// Author : toshiki
//=====================================================================
void CParticleExplosion::Draw(void)
{
    CParticleInfo::Draw();
}

//=====================================================================
// �p�[�e�B�N�����o������
// Author : toshiki
//=====================================================================
void CParticleExplosion::SetParticle(void)
{
    // �e�N�X�`���̐ݒ�
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_SMOKE));
    CScene3D::InitAnimation(8, 10, 0);
    // �p�[�e�B�N���������鎞�Ԃ̐ݒ�
    SetLife(LIFE);
}

//=====================================================================
// �p�[�e�B�N�������X�ɏ�������
// Author : toshiki
//=====================================================================
void CParticleExplosion::SetParticleColor(void)
{
    m_nCnt++;
    // ���X�ɏ����Ă�������
    if (m_nCnt >= 10)
    {
        m_fColor -= 0.1f;
        m_nCnt = 0;
    }
    SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColor));
}

//=====================================================================
// �G�t�F�N�g�X�V
// Author : toshiki
//=====================================================================
void CParticleExplosion::SetEffect(void)
{
    CTextureAnimation *pAnimation = GetTextureAnimationPtr();
    pAnimation->Update();
}