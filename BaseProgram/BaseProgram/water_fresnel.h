#ifndef _WATER_FRESNELH_
#define _WATER_FRESNELH_
//=============================================================================
//
// �t���l�����ː��N���X [water_fresnel.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "model.h"

//=========================================================================
// �O���錾
//=========================================================================
class CWave;
class CParallaxMapping2;
class CBlurFilter;
class CFrenelLambert;
class CShaderSquare;
class CReflect;
class CMask;

//=========================================================================
// �N���X��`
//=========================================================================
class CWaterFresnel : public CModel
{
public:
	CWaterFresnel(PRIORITY = PRIORITY_0);	// �R���X�g���N�^
	~CWaterFresnel();						// �f�X�g���N�^

	static CWaterFresnel *Create();	// �C���X�^���X����
	HRESULT Init();					// ����������
	void Uninit();					// ����������
	void Update();					// �X�V����
	void Draw();					// �`��
	void ShowInfo();				// ImgUi

private:
	CWave *m_pWave;					// �C
	CParallaxMapping2 *m_pParallax;	// �����}�b�v
	LPD3DXMESH m_WaterMesh;			// �����ڂ����b�V��
	CBlurFilter *m_pBlurFilter;		// �u���[
	CFrenelLambert *m_pLambert;			// �����o�[�g
	CShaderSquare *m_pSquObj;		// ���ʃI�u�W�F�N�g
	CMask *m_pMask;					// �}�X�N
	CReflect *m_pReflect;			// ����

	//�V�[���̃����_�����O
	LPDIRECT3DTEXTURE9    m_pColorTexture;
	LPDIRECT3DSURFACE9    m_pColorSurface;
	//���˃}�b�v
	LPDIRECT3DTEXTURE9    m_pReflectTexture;
	LPDIRECT3DSURFACE9    m_pReflectSurface;
	//���ʂ̃}�X�N�}�b�v
	LPDIRECT3DTEXTURE9    m_pWaterTexture;
	LPDIRECT3DSURFACE9    m_pWaterSurface;
	//�u���[����
	LPDIRECT3DTEXTURE9    m_pBlurFilterTexture;
	LPDIRECT3DSURFACE9    m_pBlurFilterSurface;

	float m_fWaveSpeed;					// �g�̑��x
	D3DXVECTOR4 m_ReflectPlayerAmbiend;	// ���˂̐F
	D3DXVECTOR4 m_ReflectSkyAmbiend;	// ���˂̐F
	float m_fReflectHeight;				// ���˂̍���
	D3DXVECTOR4 m_LambertPlayerAmbiend;	// ���ˌ��̐F
	D3DXVECTOR4 m_LambertSkyAmbiend;	// ���ˌ��̐F
	D3DXVECTOR4 m_ParallaxAmbiend;		// �����}�b�v�̐F
	float m_fParallaxSpecular;			// �L��
	float m_fParallaxSpecularPower;		// ����
	float m_fParallaxHeight;			// ����
	float m_fParallaxRefraction;		// �K���x
	float m_fZdistance;					// �ŉ��ߋ���
};

#endif