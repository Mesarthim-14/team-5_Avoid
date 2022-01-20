#ifndef _PARTICLE_EXPLOSION_H_
#define _PARTICLE_EXPLOSION_H_
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
class CParticleExplosion : public CParticleInfo
{
public:
    //==================
    // �����o�֐�
    //==================
    CParticleExplosion();
    ~CParticleExplosion();

    static CParticleExplosion * Create(const D3DXVECTOR3 &pos);
    HRESULT Init(void);
    void Update(void);
    void Uninit(void);
    void Draw(void);

private:
    void SetParticle(void);     // �p�[�e�B�N�����o������
    void SetParticleColor(void);        // �p�[�e�B�N�������X�ɏ�������
    void SetEffect(void);
    //==================
    // �����o�ϐ�
    //==================
    static D3DXVECTOR3 m_Rot;   // ����
    float m_fColor;             // �����x
    float m_fAngle;             // �p�x
    float m_fSpeed;             // ���x
    int m_nLife;                // �̗�
    int m_nCnt;
};

#endif