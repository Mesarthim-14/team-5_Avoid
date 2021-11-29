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
#include "particlepop.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"

float CParticlePop::m_fSize = 0.0f;
//=====================================================================
// �}�N����`
// Author : toshiki
//=====================================================================
#define SIZE		(D3DXVECTOR3(m_fSize, m_fSize, m_fSize))
#define ANGLE		(4.0f)
#define SPEED		(100.0f)
#define RANDOM		(3.14f)
#define LIFE		(90)
#define COLOR		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

//=====================================================================
// �R���X�g���N�^
// Author : toshiki
//=====================================================================
CParticlePop::CParticlePop()
{
    m_fAngle = 0.0f;
    m_nLife = 0;
}

//=====================================================================
// �f�X�g���N�^
// Author : toshiki
//=====================================================================
CParticlePop::~CParticlePop()
{

}

//=====================================================================
// ��������
// Author : toshiki
//=====================================================================
CParticlePop * CParticlePop::Create(const D3DXVECTOR3 &pos)
{
    CParticlePop * pParticlePop = new CParticlePop;

    if (pParticlePop)
    {
        m_fSize = CLibrary::Random(200.0f, 300.0f);
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
HRESULT CParticlePop::Init()
{
    CParticleInfo::Init();
    SetParticle();
    return S_OK;
}

//=====================================================================
// �X�V����
// Author : toshiki
//=====================================================================
void CParticlePop::Update()
{
    CParticleInfo::Update();
}

//=====================================================================
// �I������
// Author : toshiki
//=====================================================================
void CParticlePop::Uninit()
{
    CParticleInfo::Uninit();
}

//=====================================================================
// �`�揈��
// Author : toshiki
//=====================================================================
void CParticlePop::Draw()
{
    CParticleInfo::Draw();
}

//=====================================================================
// �p�[�e�B�N���̐ݒ�
// Author : toshiki
//=====================================================================
void CParticlePop::SetParticle()
{
    // �e�N�X�`���̐ݒ�
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PARTICLE));
    // �X�s�[�h�̒l��ݒ�
    m_fSpeed = SPEED;
    // �p�[�e�B�N���̏o��p�x�̐ݒ�
    m_fAngle = CLibrary::Random(RANDOM);
    // �d�͂�����
    CParticleInfo::SetGravity(true);
    // �ړ������邽�߂̏���
    D3DXVECTOR3 move = D3DXVECTOR3(sinf(m_fAngle) * m_fSpeed, ANGLE, cosf(m_fAngle) * m_fSpeed);
    // �ړ�����ݒ�
    SetMove(move);
    // �F�̐ݒ�
    SetColor(COLOR);
    // �p�[�e�B�N���������鎞�Ԃ̐ݒ�
    SetLife(LIFE);
}