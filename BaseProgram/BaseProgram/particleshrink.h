#ifndef _PARTICLESHRINK_H_
#define _PARTICLESHRINK_H_
//=====================================================================
//
//	�p�[�e�B�N������[particlenormal.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "particle_info.h"

//=====================================================================
// �N���X��`
//=====================================================================
class CParticleShrink : public CParticleInfo
{
public:
	//==================
	// �����o�֐�
	//==================
	CParticleShrink();
	~CParticleShrink();

	static CParticleShrink * Create(const D3DXVECTOR3 &pos);
	HRESULT Init(void);
	void Update(void);
	void Uninit(void);
	void Draw(void);

private:
	void SetParticle(void);		// �p�[�e�B�N�����o������
	//==================
	// �����o�ϐ�
	//==================
	static float m_fAngleX;		// �p�x
	static float m_fAngleZ;		// �p�x
	float m_fSpeed;				// ���x
	int m_nLife;				// �̗�

	D3DXVECTOR3 ShrinkPos;
};

#endif