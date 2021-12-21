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
#include "particleshrink_heel.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"

float CParticleHeel::m_fAngleX = 0.0f;
float CParticleHeel::m_fAngleZ = 0.0f;
float CParticleHeel::m_fSize = 0.0f;
//=====================================================================
// �}�N����`
// Author : toshiki
//=====================================================================
#define PARTICLE_POS    ((D3DXVECTOR3(m_fAngleX, 5.0f, m_fAngleZ)))
#define SIZE            (D3DXVECTOR3(m_fSize, m_fSize, m_fSize))
#define SPEED           (5.0f)
#define RANDOM          (3.14f)
#define LIFE            (40)
#define COLOR           (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define TANGENT         (7.0f)

//=====================================================================
// �R���X�g���N�^
// Author : toshiki
//=====================================================================
CParticleHeel::CParticleHeel()
{
    m_fSpeed = 0.0f;
    ShrinkPos = ZeroVector3;
}

//=====================================================================
// �f�X�g���N�^
// Author : toshiki
//=====================================================================
CParticleHeel::~CParticleHeel()
{

}

//=====================================================================
// ��������
// Author : toshiki
//=====================================================================
CParticleHeel * CParticleHeel::Create(const D3DXVECTOR3 &pos)
{
    CParticleHeel * pParticle = new CParticleHeel;

    if (pParticle != nullptr)
    {
        m_fAngleX = CLibrary::Random(600.0f);
        m_fAngleZ = CLibrary::Random(600.0f);
        m_fSize = CLibrary::Random(30.0f, 100.0f);
        pParticle->SetSceneInfo(D3DXVECTOR3(pos.x + m_fAngleX, pos.y, pos.z + m_fAngleZ), SIZE);

        pParticle->Init();
        return pParticle;
    }
    return nullptr;
}

//=====================================================================
// ����������
// Author : toshiki
//=====================================================================
HRESULT CParticleHeel::Init(void)
{
    CParticleInfo::Init();
    SetParticle();
    return S_OK;
}

//=====================================================================
// �X�V����
// Author : toshiki
//=====================================================================
void CParticleHeel::Update(void)
{
    CParticleInfo::Update();
}

//=====================================================================
// �I������
// Author : toshiki
//=====================================================================
void CParticleHeel::Uninit(void)
{
    CParticleInfo::Uninit();
}

//=====================================================================
// �`�揈��
// Author : toshiki
//=====================================================================
void CParticleHeel::Draw(void)
{
    CParticleInfo::Draw();
}

//=====================================================================
// �p�[�e�B�N�����o������
// Author : toshiki
//=====================================================================
void CParticleHeel::SetParticle(void)
{
    // �e�N�X�`���̐ݒ�
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_HEEL));
    // �X�s�[�h�̒l��ݒ�
    m_fSpeed = SPEED;
    // �ړ������邽�߂̏���
    D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 8.0f, 0.0f);
    // �ړ�����ݒ�
    SetMove(move);
    // �F�̐ݒ�
    SetColor(COLOR);
    // �p�[�e�B�N���������鎞�Ԃ̐ݒ�
    SetLife(LIFE);
}