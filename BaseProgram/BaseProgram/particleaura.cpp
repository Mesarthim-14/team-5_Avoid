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

//=====================================================================
// �}�N����`
// Author : toshiki
//=====================================================================
#define SIZE         (D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f))
#define ANGLE        (3.0f)
#define SPEED        (10.0f)
#define RANDOM       (3.14f)
#define LIFE         (90)
#define COLOR        (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

//=====================================================================
// �R���X�g���N�^
// Author : toshiki
//=====================================================================
CParticleAura::CParticleAura()
{
    m_fAngle = 0.0f;
    m_nLife = 0;
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
CParticleAura * CParticleAura::Create(const D3DXVECTOR3 &pos)
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