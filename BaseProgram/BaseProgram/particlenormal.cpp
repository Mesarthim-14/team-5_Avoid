//=====================================================================
//
//	�p�[�e�B�N������[particle.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "particlenormal.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define POS         (ZeroVector3)
#define SIZE        (D3DXVECTOR3(50.0f, 50.0f, 50.0f))
#define SPEED       (5.0f)
#define RANDOM      (3.14f)
#define LIFE        (60)
#define COLOR       (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CParticleNormal::CParticleNormal()
{
    m_fAngle = 0.0f;
    m_fSpeed = 0.0f;
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CParticleNormal::~CParticleNormal()
{

}

//=====================================================================
// ��������
//=====================================================================
CParticleNormal * CParticleNormal::Create(void)
{
    CParticleNormal * pParticle = new CParticleNormal;

    if (pParticle != nullptr)
    {
        pParticle->SetSceneInfo(POS, SIZE);

        pParticle->Init();
        return pParticle;
    }
    return nullptr;
}

//=====================================================================
// ����������
//=====================================================================
HRESULT CParticleNormal::Init(void)
{
    CParticleInfo::Init();
    SetParticle();
    return S_OK;
}

//=====================================================================
// �X�V����
//=====================================================================
void CParticleNormal::Update(void)
{
    CParticleInfo::Update();
}

//=====================================================================
// �I������
//=====================================================================
void CParticleNormal::Uninit(void)
{
    CParticleInfo::Uninit();
}

//=====================================================================
// �`�揈��
//=====================================================================
void CParticleNormal::Draw(void)
{
    CParticleInfo::Draw();
}

//=====================================================================
// �p�[�e�B�N�����o������
//=====================================================================
void CParticleNormal::SetParticle(void)
{
    // �e�N�X�`���̐ݒ�
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PARTICLE));
    // �X�s�[�h�̒l��ݒ�
    m_fSpeed = SPEED;
    // �p�[�e�B�N���̏o��p�x�̐ݒ�
    m_fAngle = CLibrary::Random(RANDOM);
    // �ړ������邽�߂̏���
    D3DXVECTOR3 move = D3DXVECTOR3(sinf(m_fAngle)*m_fSpeed, CLibrary::Random(4.0f, m_fSpeed), cosf(m_fAngle)*m_fSpeed);
    // �ړ�����ݒ�
    SetMove(move);
    // �F�̐ݒ�
    SetColor(COLOR);
    // �p�[�e�B�N���������鎞�Ԃ̐ݒ�
    SetLife(LIFE);
}
