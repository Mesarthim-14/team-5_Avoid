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
#include "particleshrink.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"

float CParticleShrink::m_fAngleX = 0.0f;
float CParticleShrink::m_fAngleZ = 0.0f;
//=====================================================================
// �}�N����`
// Author : toshiki
//=====================================================================
#define PARTICLE_POS	((D3DXVECTOR3(m_fAngleX, 5.0f, m_fAngleZ)))
#define SIZE			(D3DXVECTOR3(60.0f, 60.0f, 60.0f))
#define SPEED			(5.0f)
#define RANDOM			(3.14f)
#define LIFE			(70)
#define COLOR			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

//=====================================================================
// �R���X�g���N�^
// Author : toshiki
//=====================================================================
CParticleShrink::CParticleShrink()
{
	m_fSpeed = 0.0f;
	ShrinkPos = ZeroVector3;
}

//=====================================================================
// �f�X�g���N�^
// Author : toshiki
//=====================================================================
CParticleShrink::~CParticleShrink()
{

}

//=====================================================================
// ��������
// Author : toshiki
//=====================================================================
CParticleShrink * CParticleShrink::Create(const D3DXVECTOR3 &pos)
{
	CParticleShrink * pParticle = new CParticleShrink;

	if (pParticle != nullptr)
	{
		m_fAngleX = CLibrary::Random(500.0f);
		m_fAngleZ = CLibrary::Random(500.0f);
		pParticle->SetSceneInfo(D3DXVECTOR3(pos.x + m_fAngleX,pos.y,pos.z + m_fAngleZ), SIZE);

		pParticle->Init();
		return pParticle;
	}
	return nullptr; 
}

//=====================================================================
// ����������
// Author : toshiki
//=====================================================================
HRESULT CParticleShrink::Init(void)
{
	CParticleInfo::Init();
	SetParticle();
	return S_OK;
}

//=====================================================================
// �X�V����
// Author : toshiki
//=====================================================================
void CParticleShrink::Update(void)
{
	CParticleInfo::Update();
}

//=====================================================================
// �I������
// Author : toshiki
//=====================================================================
void CParticleShrink::Uninit(void)
{
	CParticleInfo::Uninit();
}

//=====================================================================
// �`�揈��
// Author : toshiki
//=====================================================================
void CParticleShrink::Draw(void)
{
	CParticleInfo::Draw();
}

//=====================================================================
// �p�[�e�B�N�����o������
// Author : toshiki
//=====================================================================
void CParticleShrink::SetParticle(void)
{
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = GET_TEXTURE_PTR;
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PARTICLE));
	// �X�s�[�h�̒l��ݒ�
	m_fSpeed = SPEED;
	float fTangent = atan2f(ShrinkPos.z - m_fAngleX, ShrinkPos.x - m_fAngleZ);
	// �ړ������邽�߂̏���
	D3DXVECTOR3 move = D3DXVECTOR3(sinf(fTangent) * m_fSpeed, 1.0f, cosf(fTangent) * m_fSpeed);
	// �ړ�����ݒ�
	SetMove(move);
	// �F�̐ݒ�
	SetColor(COLOR);
	// �p�[�e�B�N���������鎞�Ԃ̐ݒ�
	SetLife(LIFE);
}
