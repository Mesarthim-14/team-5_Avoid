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
#include "particlecannon.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"
#include "texture_animation.h"

//=====================================================================
// �}�N����`
// Author : toshiki
//=====================================================================
#define POS         (ZeroVector3)
#define SIZE        (D3DXVECTOR3(m_fSize, m_fSize, m_fSize))
#define RANDOM      (3.14f)
#define LIFE        (70)
#define COLOR       (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

float CParticleCannon::m_fSize = 0.0f;
float CParticleCannon::m_fSpeed = 0.0f;
//=====================================================================
// �R���X�g���N�^
// Author : toshiki
//=====================================================================
CParticleCannon::CParticleCannon()
{
    m_fAngle = 0.0f;
}

//=====================================================================
// �f�X�g���N�^
// Author : toshiki
//=====================================================================
CParticleCannon::~CParticleCannon()
{

}

//=====================================================================
// ��������
// Author : toshiki
//=====================================================================
CParticleCannon * CParticleCannon::Create(const D3DXVECTOR3 &pos)
{
    CParticleCannon * pParticle = new CParticleCannon;

    if (pParticle != nullptr)
    {
        m_fSize = CLibrary::Random(1000.0f, 3000.0f);
        m_fSpeed = CLibrary::Random(10.0f, 40.0f);
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
HRESULT CParticleCannon::Init(void)
{
    CParticleInfo::Init();
    SetParticle();
    return S_OK;
}

//=====================================================================
// �X�V����
// Author : toshiki
//=====================================================================
void CParticleCannon::Update(void)
{
    CParticleInfo::Update();
    SetEffect();
}

//=====================================================================
// �I������
// Author : toshiki
//=====================================================================
void CParticleCannon::Uninit(void)
{
    CParticleInfo::Uninit();
}

//=====================================================================
// �`�揈��
// Author : toshiki
//=====================================================================
void CParticleCannon::Draw(void)
{
    CParticleInfo::Draw();
}

//=====================================================================
// �p�[�e�B�N�����o������
// Author : toshiki
//=====================================================================
void CParticleCannon::SetParticle(void)
{
    // �e�N�X�`���̐ݒ�
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_CANNON));
    CScene3D::InitAnimation(8, 10, -1);
    // �p�[�e�B�N���̏o��p�x�̐ݒ�
    m_fAngle = CLibrary::Random(RANDOM);
    // �ړ������邽�߂̏���
    D3DXVECTOR3 move = D3DXVECTOR3(sinf(m_fAngle)*m_fSpeed, CLibrary::Random(m_fSpeed), cosf(m_fAngle)*m_fSpeed);
    // �ړ�����ݒ�
    SetMove(move);
    // �F�̐ݒ�
    SetColor(COLOR);
    // �p�[�e�B�N���������鎞�Ԃ̐ݒ�
    SetLife(LIFE);
}

//=====================================================================
// �G�t�F�N�g�X�V
// Author : toshiki
//=====================================================================
void CParticleCannon::SetEffect(void)
{
    CTextureAnimation *pAnimation = GetTextureAnimationPtr();
    pAnimation->Update();
}