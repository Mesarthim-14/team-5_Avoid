#ifndef _PARTICLENORMAL_H_
#define _PARTICLENORMAL_H_
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
class CParticleNormal : public CParticleInfo
{
public:
    //==================
    // �����o�֐�
    //==================
    CParticleNormal();
    ~CParticleNormal();

    static CParticleNormal * Create(const D3DXVECTOR3 &pos);
    HRESULT Init(void);
    void Update(void);
    void Uninit(void);
    void Draw(void);

private:
    void SetParticle(void);     // �p�[�e�B�N�����o������
    //==================
    // �����o�ϐ�
    //==================
    float m_fAngle;             // �p�x
    float m_fSpeed;             // ���x
    int m_nLife;                // �̗�
};

#endif