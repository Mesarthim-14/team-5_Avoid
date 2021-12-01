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

//=====================================================================
// �}�N����`
// Author : toshiki
//=====================================================================
#define POS         (ZeroVector3)
#define SIZE        (D3DXVECTOR3(200.0f, 200.0f, 200.0f))
#define SPEED       (30.0f)
#define RANDOM      (3.14f)
#define LIFE        (40)
#define COLOR       (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

//=====================================================================
// �R���X�g���N�^
// Author : toshiki
//=====================================================================
CParticleCannon::CParticleCannon()
{
    m_fAngle = 0.0f;
    m_fSpeed = 0.0f;
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
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PARTICLE));
    // �X�s�[�h�̒l��ݒ�
    m_fSpeed = SPEED;
    // �p�[�e�B�N���̏o��p�x�̐ݒ�
    m_fAngle = CLibrary::Random(RANDOM);
    // �d�͂�����
    SetGravity(true);
    // �ړ������邽�߂̏���
    D3DXVECTOR3 move = D3DXVECTOR3(sinf(m_fAngle)*m_fSpeed, CLibrary::Random(4.0f, m_fSpeed), cosf(m_fAngle)*m_fSpeed);
    // �ړ�����ݒ�
    SetMove(move);
    // �F�̐ݒ�
    SetColor(COLOR);
    // �p�[�e�B�N���������鎞�Ԃ̐ݒ�
    SetLife(LIFE);
}