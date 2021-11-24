//=====================================================================
//
//	�p�[�e�B�N������[particlecollective.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
// Author : toshiki
//=====================================================================
#include "particlecollective.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"

//=====================================================================
// �}�N����`
// Author : toshiki
//=====================================================================
#define POS			(ZeroVector3)
#define SIZE		(D3DXVECTOR3(50.0f, 50.0f, 50.0f))
#define SPEED		(5.0f)
#define RANDOM		(3.14f)
#define LIFE		(20)
#define COLOR		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

#define COLLECTIVE	(D3DXVECTOR3(0.0f,0.0f,400.0f))

//=====================================================================
// �R���X�g���N�^
// Author : toshiki
//=====================================================================
CParticleCollective::CParticleCollective()
{
    m_fAngle = 0.0f;
    m_fSpeed = 0.0f;
}

//=====================================================================
// �f�X�g���N�^
// Author : toshiki
//=====================================================================
CParticleCollective::~CParticleCollective()
{

}

//=====================================================================
// ��������
// Author : toshiki
//=====================================================================
CParticleCollective * CParticleCollective::Create(const D3DXVECTOR3 &pos)
{
    CParticleCollective * pParticle = new CParticleCollective;

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
HRESULT CParticleCollective::Init(void)
{
    CParticleInfo::Init();
    SetParticle();
    return S_OK;
}

//=====================================================================
// �X�V����
// Author : toshiki
//=====================================================================
void CParticleCollective::Update(void)
{
    CParticleInfo::Update();
}

//=====================================================================
// �I������
// Author : toshiki
//=====================================================================
void CParticleCollective::Uninit(void)
{
    CParticleInfo::Uninit();
}

//=====================================================================
// �`�揈��
// Author : toshiki
//=====================================================================
void CParticleCollective::Draw(void)
{
    CParticleInfo::Draw();
}

//=====================================================================
// �p�[�e�B�N�����o������
// Author : toshiki
//=====================================================================
void CParticleCollective::SetParticle(void)
{
    //	����������ꏊ�̍��W��ݒ�
    D3DXVECTOR3 CollectivePos = COLLECTIVE;

    // �e�N�X�`���̐ݒ�
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PARTICLE));
    // �X�s�[�h�̒l��ݒ�
    m_fSpeed = SPEED;
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