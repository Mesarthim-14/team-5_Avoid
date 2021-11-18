#ifndef _PARTICLEPOP_H_
#define _PARTICLEPOP_H_
//=====================================================================
//
//	�p�[�e�B�N������[particlepop.h]
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
class CParticlePop : public CParticleInfo
{
public:
	//==================
	// �����o�֐�
	//==================
	CParticlePop();
	~CParticlePop();

	static CParticlePop * Create(D3DXVECTOR3 pos);
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

	D3DXVECTOR3 PlayerPos;		// �v���C���[�̈ʒu
};

#endif