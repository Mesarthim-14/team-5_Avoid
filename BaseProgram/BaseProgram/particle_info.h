#ifndef _PARTICLE_INFO_H_
#define _PARTICLE_INFO_H_
//=====================================================================
//
//	�p�[�e�B�N����b����[particle_info.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "billboard.h"

//=====================================================================
// �N���X��`
//=====================================================================
class CParticleInfo : public CBillboard
{
public:
	//==================
	// �����o�֐�
	//==================
	CParticleInfo();
	virtual ~CParticleInfo();

	virtual HRESULT Init(void) = 0;
	virtual void Update(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Draw(void) = 0;

	// get�֐�
	D3DXVECTOR3 GetMove(void) { return m_move; }
	int GetLife(void) { return m_nLife; }
	// set�֐�
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetLife(int life) { m_nLife = life; }
	void SetGravity(bool set) { m_bGravitySet = set; }

private:
	void Gravity(void);
	//==================
	// �����o�ϐ�
	//==================
	D3DXVECTOR3 m_move;		// �p�[�e�B�N���̈ړ���
	int m_nLife;			// �p�[�e�B�N���̃��C�t
	bool m_bGravitySet;
};

#endif