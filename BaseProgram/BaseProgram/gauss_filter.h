#ifndef _GAUSS_FILTER_H_
#define _GAUSS_FILTER_H_
//=============================================================================
//
// ���U�C�N���� [gauss_filter.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "shader_square.h"
#include "xfile.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CGaussFilter
{
public:
    enum
    {
        WEIGHT_MUN = 8, // �d�݂��v�Z�����
    };
    //-------------------------------------------------------------
    // ���_�̍\����
    //-------------------------------------------------------------
    struct TVERTEX
    {
        FLOAT p[4];
        FLOAT tu, tv;
    };

    CGaussFilter(LPDIRECT3DDEVICE9 pd3dDevice);
    ~CGaussFilter();
    void Uninit();
    void Restore();
    HRESULT Load();
    inline LPD3DXEFFECT GetEffect()const { return m_pEffect; };

    void UpdateWeight();                                // �����̌v�Z
    void BeginSurface();                                // �T�[�t�F�X�̊J�n
    void DrawPolygon();                                 // �|���S���̕`��
    void FadeOut();                                     // ���U�C�N������
    inline void SetFade(const bool& bFlag)  { m_bFade = bFlag; }
    inline bool GetUse()const               { return m_bUse; }

private:
    void ShowInfo();    // imgui���
    void SetAlphaNum(); // �����x�ݒ�
    void GaussShader(); // �K�E�X�V�F�[�_�ݒ�
    void EndSurface();  // �T�[�t�F�X��߂�

    LPD3DXEFFECT m_pEffect;
    D3DXHANDLE m_hTechnique, m_hafWeight, m_htSrcMap, m_AlphaNum;
    LPDIRECT3DDEVICE9 m_pd3dDevice;

    // �ʏ�̍��W�ϊ��s��
    D3DXMATRIX m_mWorld;
    D3DXMATRIX m_mView;
    D3DXMATRIX m_mProj;

    LPDIRECT3DSURFACE9 m_pMapZ;             // �[�x�o�b�t�@
    LPDIRECT3DTEXTURE9 m_pOriginalMap;      // �e�N�X�`��
    LPDIRECT3DSURFACE9 m_pOriginalMapSurf;  // �T�[�t�F�X
    LPDIRECT3DTEXTURE9 m_pXMap;             // �e�N�X�`��
    LPDIRECT3DSURFACE9 m_pXMapSurf;	        // �T�[�t�F�X
    LPDIRECT3DTEXTURE9 m_pXYMap;            // �e�N�X�`��
    LPDIRECT3DSURFACE9 m_pXYMapSurf;        // �T�[�t�F�X
    LPDIRECT3DTEXTURE9 m_pAllMap;           // �e�N�X�`��
    LPDIRECT3DSURFACE9 m_pAllMapSurf;       // �T�[�t�F�X
    LPDIRECT3DTEXTURE9 m_pScreenMap;        // �e�N�X�`��
    LPDIRECT3DSURFACE9 m_pOldBackBuffer, m_pOldZBuffer;
    D3DVIEWPORT9 m_oldViewport;
    float m_dispersion_sq;                  // ���U�̕�����
    float m_tbl[WEIGHT_MUN];                // �d�݂̔z��
    float m_fAlphaNum;                      // �����x
    bool m_bFade;                           // �t�F�[�h�̃t���O
    bool m_bUse;                           // �g�p����Ă��邩�ǂ���
};
#endif