#ifndef _TOON_SHADER_H_
#define _TOON_SHADER_H_
//=============================================================================
//
// �g�D�[���V�F�[�_�N���X [toon_shader.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "main.h"
#include "xfile.h"

//=========================================================================
// �O���錾
//=========================================================================
class CEdgeFilter;
class CCanvas;

//=========================================================================
// �N���X��`
//=========================================================================
class CToonShader
{
public:
    enum TOON_PASS
    {
        TOON_PASS_NONE = -1,        // �����l
        TOON_PASS_SKINMESH_TEX,     // �X�L�����b�V��(�e�N�X�`������)
        TOON_PASS_EDGE_FILTER,      // �A�E�g���C��
        TOON_PASS_MODEL,            // ���f��
        TOON_PASS_SKINMESH_DIFFUSE, // �X�L�����b�V��(�e�N�X�`������)
    };

    CToonShader(LPDIRECT3DDEVICE9 pd3dDevice);  // �R���X�g���N�^
    ~CToonShader();                             // �f�X�g���N�^

    void Invalidate();
    void Restore();
    void Init();            // ����������
    void Uninit();          // �I������
    void Draw();            // �`�揈��
    HRESULT Load();         // �V�F�[�_���[�h
    void TextureLoad();     // �e�N�X�`�����[�h[
    void BeginSurface();    // �T�[�t�F�X�̓���ւ�
    void DrawEdgeFilter();  // �G�b�W�̕`��
    void EndSurface();      // �T�[�t�F�X�̏I��

    void Begin();
    void Begin(int nNum, D3DXMATRIX& mtxWorld, CXfile::MODEL model);      // �ʏ�V�F�[�_
    void Begin(int nNum, D3DXMATRIX& mtxWorld, D3DXVECTOR4* LightDir);    // �X�L�����b�V���V�F�[�_�J�n
    void BeginPass(int nNum);                                   // �p�X�̊J�n
    void SetMatrix(D3DXMATRIX* pMatWorld, D3DXVECTOR4* pLightDir, D3DXVECTOR4* pCameraPos);
    void SetAmbient(float Ambient);
    void SetAmbient(D3DXVECTOR4* pAmbient);
    void CommitChanges();
    void EndPass();
    void End();
    inline LPD3DXEFFECT GetEffect()const { return m_pEffect; };
    void Render(LPDIRECT3DTEXTURE9 pBackBuffer, LPDIRECT3DTEXTURE9 pZBuffer);
    void SetParameters(D3DXVECTOR2* pTexel, float pLimit);
    void SetDiffuse(D3DXVECTOR4 Diffuse);
    void SetVertexBlendInfo(D3DXMATRIX *pMtxWorld[4], D3DXMATRIX pMtxView, D3DXMATRIX pMtxProj, int nNum);

private:
    LPD3DXEFFECT m_pEffect;
    D3DXHANDLE m_pTechnique, m_pWVP, m_pLightDir, m_pTexel, m_pLimit, m_pEyePos, m_pMtxWorld, m_Diffuse;
    D3DXHANDLE matWorld[4], matView, matProj, nBlendNum;
    D3DXMATRIX m_matView, m_matProj;
    LPDIRECT3DDEVICE9 m_pd3dDevice;

    CEdgeFilter *m_pEdgeFilter;
    //�g�[���}�b�v�e�N�X�`���[
    LPDIRECT3DTEXTURE9 m_pToonMap;
    //�V�[���̃J���[�����i�[����T�[�t�F�C�X�̐錾
    LPDIRECT3DTEXTURE9 m_pColorTexture;
    LPDIRECT3DSURFACE9 m_pColorSurface;
    //�V�[���̂y�l�����i�[����T�[�t�F�C�X�̐錾
    LPDIRECT3DTEXTURE9 m_pZMapTexture;
    LPDIRECT3DSURFACE9 m_pZMapSurface;
    //�V�[���̂y�l�����i�[����T�[�t�F�C�X�̐錾
    LPDIRECT3DTEXTURE9 m_pDiffuseTexture;
    LPDIRECT3DSURFACE9 m_pDiffuseSurface;
    //����e�N�X�`���[
    LPDIRECT3DTEXTURE9 m_pCanvasTexture;

    LPDIRECT3DSURFACE9 m_OldSurface;
    float m_fLimit;
    CCanvas* m_pCanvas;
};

#endif