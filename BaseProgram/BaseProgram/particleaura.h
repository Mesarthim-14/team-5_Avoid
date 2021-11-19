#ifndef _PARTICLEAURA_H_
#define _PARTICLEAURA_H_
//=====================================================================
//
//	�p�[�e�B�N������[particleaura.h]
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
class CParticleAura : public CParticleInfo
{
public:
	//==================
	// �����o�֐�
	//==================
	CParticleAura();
	~CParticleAura();

	static CParticleAura * Create(D3DXVECTOR3 pos);
	HRESULT Init(void);
	void Update(void);
	void Uninit(void);
	void Draw(void);

private:
	void SetParticle(void);		// �p�[�e�B�N�����o������
	//==================
	// �����o�ϐ�
	//==================
	float m_fAngle;				// �p�x
	float m_fSpeed;				// ���x
	int m_nLife;				// �̗�
	static float m_fSize;
};

#endif
