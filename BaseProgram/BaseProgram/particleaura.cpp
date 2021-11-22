//=====================================================================
//
//    �p�[�e�B�N������[particlepop.h]
//    Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "particleaura.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"

float CParticleAura::m_fSize = 0.0f;
//=====================================================================
// �}�N����`
//=====================================================================
#define SIZE        (D3DXVECTOR3(m_fSize, m_fSize, m_fSize))
#define ANGLE        (3.0f)
#define SPEED        (10.0f)
#define RANDOM        (3.14f)
#define LIFE        (90)
#define COLOR        (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CParticleAura::CParticleAura()
{
    m_fAngle = 0.0f;
    m_nLife = 0;
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CParticleAura::~CParticleAura()
{

}

//=====================================================================
// ��������
//=====================================================================
CParticleAura * CParticleAura::Create(D3DXVECTOR3 pos)
{
    CParticleAura * pParticlePop = new CParticleAura;

    if (pParticlePop)
    {
        pParticlePop->SetSceneInfo(pos, SIZE);

        pParticlePop->Init();
        return pParticlePop;
    }
    return nullptr;
}

//=====================================================================
// ����������
//=====================================================================
HRESULT CParticleAura::Init()
{
    CParticleInfo::Init();
    SetParticle();
    return S_OK;
}

//=====================================================================
// �X�V����
//=====================================================================
void CParticleAura::Update()
{
    CParticleInfo::Update();
}

//=====================================================================
// �I������
//=====================================================================
void CParticleAura::Uninit()
{
    CParticleInfo::Uninit();
}

//=====================================================================
// �`�揈��
//=====================================================================
void CParticleAura::Draw()
{
    CParticleInfo::Draw();
}

//=====================================================================
// �p�[�e�B�N���̐ݒ�
//=====================================================================
void CParticleAura::SetParticle()
{
    // �e�N�X�`���̐ݒ�
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PARTICLE));
    // �F�̐ݒ�
    SetColor(COLOR);
}