//=============================================================================
//
// ���N���X [test_model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "water_fresnel.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "wave.h"
#include "shader_square.h"
#include "parallax_mapping2.h"
#include "camera.h"
#include "light.h"
#include "library.h"
#include "blur_filter.h"
#include "fresnel_lambert.h"
#include "mask.h"
#include "reflect.h"
#include "player.h"
#include "modelanime.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define WATER_POS               (ZeroVector3)
#define WATER_ROT               (ZeroVector3)

// �g�̐ݒ�
// �}�e���A����ݒ肷��
#define HEIGHT                  (0.2f)          // �g�̍���     
#define ADD_WAVE_TEX_POS        (0.0f, 1.0f)    // �g�̏o�����W
#define Z_DISTANCE              (2286.0f)       // �ŉ��ߋ���

// Reflect
#define REFLECT_HEIGHT          (30.0f)                                 // ���˂̍���
#define REFLECT_PLAYER_AMBIENT  (0.1f)                                  // ���˂̐F
#define REFLECT_SKY_AMBIENT     (D3DXVECTOR4(0.3f, 0.0f, 1.0f, 1.0f))   // ���˂̐F

// Wave 
#define WAVE_SPEED              (0.2f)                                  // �g�̑��x

// Lambert
#define LAMBERT_PLAYER_AMBIENT  (0.1f)                                  // ���ˌ��̐F
#define LAMBERT_SKY_AMBIENT     (D3DXVECTOR4(0.5f, 0.0f, 1.0f, 1.0f))   // ���ˌ��̐F

// Parallax
#define PARALLAX_AMBIENT        (D3DXVECTOR4(1.0f, 1.0f, 0.6f, 0.1f))
#define PARALLAX_SPECULAR       (0.8f)              // �L��
#define PARALLAX_SPECULARPOWER  (0.2f)              // ����
#define PARALLAX_HEIGHT         (0.5f)              // ����
#define PARALLAX_REFRACTION     (256.2f)            // �K���x

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWaterFresnel::CWaterFresnel(PRIORITY Priority) : CModel(Priority)
{
    m_pWave = nullptr;
    m_pParallax = nullptr;
    m_WaterMesh = nullptr;
    m_pBlurFilter = nullptr;
    m_pLambert = nullptr;
    m_pSquObj = nullptr;
    m_pMask = nullptr;
    m_pReflect = nullptr;
    m_pColorTexture = nullptr;
    m_pColorSurface = nullptr;
    m_pReflectTexture = nullptr;
    m_pReflectSurface = nullptr;
    m_pWaterTexture = nullptr;
    m_pWaterSurface = nullptr;
    m_pBlurFilterTexture = nullptr;
    m_pBlurFilterSurface = nullptr;

    m_fWaveSpeed = WAVE_SPEED;
    m_ReflectPlayerAmbiend = { REFLECT_PLAYER_AMBIENT, REFLECT_PLAYER_AMBIENT, REFLECT_PLAYER_AMBIENT, 1.0f };
    m_ReflectSkyAmbiend = REFLECT_SKY_AMBIENT;
    m_fReflectHeight = REFLECT_HEIGHT;
    m_LambertPlayerAmbiend = { LAMBERT_PLAYER_AMBIENT, LAMBERT_PLAYER_AMBIENT, LAMBERT_PLAYER_AMBIENT, 1.0f };
    m_LambertSkyAmbiend = LAMBERT_SKY_AMBIENT;
    m_ParallaxAmbiend = PARALLAX_AMBIENT;
    m_fParallaxSpecular = PARALLAX_SPECULAR;            // �L��
    m_fParallaxSpecularPower = PARALLAX_SPECULARPOWER;  // ����
    m_fParallaxHeight = PARALLAX_HEIGHT;                // ����
    m_fParallaxRefraction = PARALLAX_REFRACTION;        // �K���x
    m_fZdistance = Z_DISTANCE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWaterFresnel::~CWaterFresnel()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CWaterFresnel * CWaterFresnel::Create()
{
    // �������m��
    CWaterFresnel *pWater = new CWaterFresnel(PRIORITY_0);

    // nullcheck
    if (pWater)
    {
        // ����������
        pWater->Init();
        return pWater;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CWaterFresnel::Init()
{
    // ����������
    CModel::Init();
    LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;
    CXfile *pXfile = GET_XFILE_PTR;
    //BindModel(pXfile->GetXfile(CXfile::XFILE_NUM_TEST_BLOCK));
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_PLANE);
    GetModelInfo()->SetModelStatus(WATER_POS, WATER_ROT, model);

    // �g
    if (!m_pWave)
    {
        //�g�}�b�v�̃T�C�Y
        D3DXVECTOR2 WaveMapSize = D3DXVECTOR2(512.0f, 512.0f);    // 512
        m_pWave = new CWave(pDevice, (UINT)WaveMapSize.x, (UINT)WaveMapSize.y);
        m_pWave->Load();
    }
    // ���ˌ�
    if (!m_pLambert)
    {
        m_pLambert = new CFrenelLambert(pDevice);
        m_pLambert->Load();
    }
    // ����
    if (!m_pReflect)
    {
        m_pReflect = new CReflect(pDevice);
        m_pReflect->Load();
    }
    // �u���[
    if (!m_pBlurFilter)
    {
        m_pBlurFilter = new CBlurFilter(pDevice, (UINT)(SCREEN_WIDTH), (UINT)(SCREEN_HEIGHT));
        m_pBlurFilter->Load();
    }
    // ���ʃ}�X�N
    if (!m_pMask)
    {
        m_pMask = new CMask(pDevice);
        m_pMask->Load();
    }
    // �����}�b�v
    if (!m_pParallax)
    {
        m_pParallax = new CParallaxMapping2(pDevice);
        m_pParallax->Load();
    }
    if (!m_pSquObj)
    {
        //2�c�I�u�W�F�N�g�̃��[�h
        m_pSquObj = new CShaderSquare(pDevice, (UINT)(SCREEN_WIDTH), (UINT)(SCREEN_HEIGHT));
        m_pSquObj->Load();
    }

    D3DVERTEXELEMENT9 decl[] =
    {
        { 0,  0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
        { 0, 12, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0 },
        { 0, 24, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },
        { 0, 36, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
        { 0, 48, D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
        D3DDECL_END()
    };
    m_pWave->SetVertexDecl(pDevice, decl, m_WaterMesh, model.pMesh);
    m_pWave->Restore();
    m_pParallax->Restore();
    m_pBlurFilter->Restore();
    m_pLambert->Restore();
    m_pMask->Restore();
    m_pReflect->Restore();
    //�V�[���̃����_�����O�C���[�W
    pDevice->CreateTexture(SCREEN_WIDTH,
        SCREEN_HEIGHT,
        1,
        D3DUSAGE_RENDERTARGET,
        D3DFMT_A8R8G8B8,
        D3DPOOL_DEFAULT,
        &m_pColorTexture,
        NULL);
    m_pColorTexture->GetSurfaceLevel(0, &m_pColorSurface);

    //���˃}�b�v(�k���T�[�t�F�C�X)
    pDevice->CreateTexture(m_pBlurFilter->GetWidth(),
        m_pBlurFilter->GetHeight(),
        1,
        D3DUSAGE_RENDERTARGET,
        D3DFMT_A8R8G8B8,
        D3DPOOL_DEFAULT,
        &m_pReflectTexture,
        NULL);
    m_pReflectTexture->GetSurfaceLevel(0, &m_pReflectSurface);

    //�u���[�t�B���^�[�K����T�[�t�F�C�X(������k���T�[�t�F�C�X)
    pDevice->CreateTexture(m_pBlurFilter->GetWidth(),
        m_pBlurFilter->GetHeight(),
        1,
        D3DUSAGE_RENDERTARGET,
        D3DFMT_A8R8G8B8,
        D3DPOOL_DEFAULT,
        &m_pBlurFilterTexture,
        NULL);
    m_pBlurFilterTexture->GetSurfaceLevel(0, &m_pBlurFilterSurface);

    //���ʂ̃}�X�N�}�b�v
    pDevice->CreateTexture(SCREEN_WIDTH,
        SCREEN_HEIGHT,
        1,
        D3DUSAGE_RENDERTARGET,
        D3DFMT_A8R8G8B8,
        D3DPOOL_DEFAULT,
        &m_pWaterTexture,
        NULL);
    m_pWaterTexture->GetSurfaceLevel(0, &m_pWaterSurface);
    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CWaterFresnel::Uninit()
{
    if (m_pWave)
    {
        m_pWave->Uninit();
        delete m_pWave;
        m_pWave = nullptr;
    }
    if (m_pParallax)
    {
        m_pParallax->Invalidate();
        delete m_pParallax;
        m_pParallax = nullptr;
    }
    if (m_pBlurFilter)
    {
        m_pBlurFilter->Uninit();
        delete m_pBlurFilter;
        m_pBlurFilter = nullptr;
    }
    if (m_pLambert)
    {
        m_pLambert->Invalidate();
        delete m_pLambert;
        m_pLambert = nullptr;
    }
    if (m_pSquObj)
    {
        m_pSquObj->Uninit();
        delete m_pSquObj;
        m_pSquObj = nullptr;
    }
    if (m_pMask)
    {
        m_pMask->Invalidate();
        delete m_pMask;
        m_pMask = nullptr;
    }
    if (m_pReflect)
    {
        m_pReflect->Invalidate();
        delete m_pReflect;
        m_pReflect = nullptr;
    }
    if (m_pColorTexture)
    {
        m_pColorTexture->Release();
        m_pColorTexture = nullptr;
    }
    if (m_pColorSurface)
    {
        m_pColorSurface->Release();
        m_pColorSurface = nullptr;
    }

    if (m_pReflectTexture)
    {
        m_pReflectTexture->Release();
        m_pReflectTexture = nullptr;
    }    
    if (m_pReflectSurface)
    {
        m_pReflectSurface->Release();
        m_pReflectSurface = nullptr;
    }    
    if (m_pWaterTexture)
    {
        m_pWaterTexture->Release();
        m_pWaterTexture = nullptr;
    }    
    if (m_pWaterSurface)
    {
        m_pWaterSurface->Release();
        m_pWaterSurface = nullptr;
    }    
    if (m_pBlurFilterTexture)
    {
        m_pBlurFilterTexture->Release();
        m_pBlurFilterTexture = nullptr;
    }    
    if (m_pBlurFilterSurface)
    {
        m_pBlurFilterSurface->Release();
        m_pBlurFilterSurface = nullptr;
    }    

    // �I������
    CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CWaterFresnel::Update()
{
    // �X�V����
    CModel::Update();

    ShowInfo();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CWaterFresnel::Draw()
{
    if (m_pWave)
    {
        LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;
        CTexture *pTexture = GET_TEXTURE_PTR;
        D3DXMATRIX matView, mtxRot, mtxTrans, mtxScale, matWorld, matReflect;
        D3DXMATRIX matProj = CManager::GetInstance()->GetCamera()->GetMtxProj();
        D3DXVECTOR3 CameraPos = CManager::GetInstance()->GetCamera()->GetposV();
        D3DXVECTOR4 EyePos = D3DXVECTOR4(CameraPos, 1.0f);
        D3DXVECTOR4 LightDir = D3DXVECTOR4(CManager::GetInstance()->GetLight()->GetLightDir(), 0.0f);
        CModelInfo *pModelInfo = GetModelInfo();
        CXfile::MODEL map = GET_XFILE_PTR->GetXfile(CXfile::XFILE_NUM_MAP);
        CXfile::MODEL sky = GET_XFILE_PTR->GetXfile(CXfile::XFILE_NUM_SKY);
        D3DXVECTOR3 ObjPos = { 0.0f, -0.0f, 0.0f };
        D3DXVECTOR3 PlayerPos = { 0.0f, -150.0f, 0.0f };
        D3DXVECTOR3 ObjSize = { 1.0f, 1.0f, 1.0f };
        CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();

        //���z�̈ʒu�x�N�g��
        D3DXVECTOR4 LightPos = D3DXVECTOR4(-72.0f, -100.0f, -620.0f, 0.0f);
        D3DXVec3Normalize((D3DXVECTOR3*)&LightPos, (D3DXVECTOR3*)&LightPos);

        //�}�e���A���f�[�^�ւ̃|�C���^���擾
        D3DMATERIAL9 matDef;
        CXfile::MODEL model = pModelInfo->GetModel();
        D3DXMATERIAL* pMat = (D3DXMATERIAL*)pModelInfo->GetBuffMat()->GetBufferPointer();

        //���݂̃}�e���A�����擾����
        pDevice->GetMaterial(&matDef);

        // �e�N�X�`�����H
        pDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        pDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
        pDevice->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
        pDevice->SetSamplerState(2, D3DSAMP_MINFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(2, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(2, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
        pDevice->SetSamplerState(3, D3DSAMP_MINFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(3, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(3, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
        pDevice->SetSamplerState(4, D3DSAMP_MINFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(4, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(4, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

        //****************************************************************
        //�X�e�b�v�P�F�g�}�b�v�̍X�V
        //****************************************************************
        //WAVE�N���X���ŕ��������_�t�H�[�}�b�g���g�p���Ă���
        //���������_�t�H�[�}�b�g�̓r�f�I�J�[�h�ɂ���ẮuLINEAR�v�������Ȃ��̂ł����ł́uPOINT�v�ɐݒ肵�Ă���
        pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
        //2D�X�v���C�g�I�u�W�F�N�g���g�p���ă����_�����O����̂ły�o�b�t�@�ւ̏������݂𖳌��ɂ���
        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
        //�΂ˌW����ݒ�
        m_pWave->SetWaveSpeed(m_fWaveSpeed);

        int nNum = CLibrary::Random(0, 1);
        D3DXVECTOR2 texpos = ZeroVector2;
        switch (nNum)
        {
        case 0:// ��
            texpos.x = CLibrary::Random(-0.0f, 1.0f);
            texpos.y = 0.0f;
            break;
         case 1:// ��
            texpos.x = 0.0f;
            texpos.y = CLibrary::Random(-0.0f, 1.0f);
            break;
        default:
            break;
        }
        //m_pWave->AddWave(texpos.x, texpos.y, CLibrary::Random(HEIGHT));

        //�K���ɔg��V�K�쐬����
        //�ǉ�����g�̍�����ݒ�ł���悤�ɏC��. �ڍׂ͔g�V�F�[�_�[�y�[�W���Q��
        m_pWave->AddWave(CLibrary::Random(ADD_WAVE_TEX_POS), CLibrary::Random(ADD_WAVE_TEX_POS), CLibrary::Random(HEIGHT));

        //�X�V�����g�}�b�v���擾
        LPDIRECT3DTEXTURE9 BumpMap = m_pWave->Draw();
        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

        //****************************************************************
        // �X�e�b�v�Q : ���˃}�b�v�̍쐬
        //****************************************************************
        pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
        pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

        D3DVIEWPORT9 OldViewport, NewViewport;
        //�k���T�[�t�F�C�X���g�p���邽�߁A�r���[�|�[�g�𔽎˃}�b�v�̃T�C�Y�ɍ��킹��
        pDevice->GetViewport(&OldViewport);
        CopyMemory(&NewViewport, &OldViewport, sizeof(D3DVIEWPORT9));
        NewViewport.Width = m_pBlurFilter->GetWidth();
        NewViewport.Height = m_pBlurFilter->GetHeight();
        NewViewport.MinZ = 0.0f;
        NewViewport.MaxZ = 1.0f;
        pDevice->SetViewport(&NewViewport);

        // �T�[�t�F�X�擾
        LPDIRECT3DSURFACE9 OldSurface = nullptr;
        pDevice->GetRenderTarget(0, &OldSurface);

        // �T�[�t�F�X�ݒ�
        pDevice->SetRenderTarget(0, m_pReflectSurface);
        // �T�[�t�F�X�N���A
        pDevice->Clear(0L,
            nullptr,
            D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
            BlackColor,
            1.0f,
            0L);

        //Y �����ɔ��]���ă����_�����O����̂Ń����_�����O�ʂ����]������
        pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

        // �������琅�ʂ� Y �����ɔ��]������s����쐬����
        D3DXPLANE Plane;
        D3DXVECTOR3 Point, Normal;
        D3DXVECTOR4 LightDirReflect = LightDir;
        LightDirReflect.y *= -1.0f;

        //���ʂ̔C�ӈ�_�̍��W
        Point = D3DXVECTOR3(0.0f, m_fReflectHeight, 0.0f);
        //���ʂ̖@���x�N�g��
        Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
        //���ʂ̕��ʂ��`
        D3DXPlaneFromPointNormal(&Plane, &Point, &Normal);
        //��`���甽�ˍs����擾
        D3DXMatrixReflect(&matReflect, &Plane);

        // ��������w�i�����_�����O�J�n
        // ���ʂ̍������Z�b�g
        m_pReflect->SetHeight(Point.y);
        m_pReflect->Begin();

        D3DXMatrixIdentity(&matWorld);
        // �g�嗦�𔽉f
        D3DXMatrixScaling(&mtxScale, ObjSize.x, ObjSize.y, ObjSize.z);
        D3DXMatrixMultiply(&matWorld, &matWorld, &mtxScale);
        //�ʒu�𔽉f
        D3DXMatrixTranslation(&mtxTrans, ObjPos.x, ObjPos.y, ObjPos.z);
        D3DXMatrixMultiply(&matWorld, &matWorld, &mtxTrans);
        pDevice->SetTransform(D3DTS_WORLD, &matWorld);

        // ���[���h�s����쐬���AY �����ɔ��]����s����쐬
        matWorld = matWorld * matReflect;
        m_pReflect->SetMatrix(&matWorld, &LightDirReflect);

        // box
        pDevice->SetTexture(0, pTexture->GetTexture(CTexture::TEXTURE_NUM_TEST));
        m_pReflect->SetAmbient(&m_ReflectPlayerAmbiend);
        m_pReflect->BeginPass();
        map.pMesh->DrawSubset(0);
        m_pReflect->EndPass();
        D3DXVECTOR3 playerPos = pPlayer->GetPos();
        D3DXVECTOR3 playerRot = pPlayer->GetRot();

    //    size_t size = pPlayer->GetModelAnimeVec().size();
        m_pReflect->SetAmbient(&m_ReflectPlayerAmbiend);

    //    for (size_t nCount = 0; nCount < size; nCount++)
    //    {
    //        D3DXVECTOR3 AnimeModelPos = pPlayer->GetModelAnime(nCount)->GetPosAnime();
    //        D3DXVECTOR3 AnimeModelRot = pPlayer->GetModelAnime(nCount)->GetRotAnime();
    //        CModelAnime *pParent = pPlayer->GetModelAnime(nCount)->GetParent();
    //        D3DXMATRIX mtxParent, mtxPlayer;
    //        D3DXMatrixIdentity(&matWorld);
    //        D3DXMatrixIdentity(&mtxParent);
    //
    //        // ��]�𔽉f
    //        D3DXMatrixRotationYawPitchRoll(&mtxRot, AnimeModelRot.y, AnimeModelRot.x, AnimeModelRot.z);
    //        D3DXMatrixMultiply(&matWorld, &matWorld, &mtxRot);
    //
    //        D3DXVECTOR3 Pos = pPlayer->GetModelAnime(nCount)->GetModelInfo()->GetPos();
    //        D3DXVECTOR3 TextPos = pPlayer->GetModelAnime(nCount)->GetPosAnime();
    //
    //        //�ʒu�𔽉f
    //        D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);
    //
    //        D3DXMatrixMultiply(&matWorld, &matWorld, &mtxTrans);
    //
    //        //�e�����݂���ꍇ
    //        if (pParent)
    //        {
    //            //�e����ݒ�
    //            mtxParent = pParent->GetModelInfo()->GetMtxWorld();
    //        }
    //        //�e�����݂��Ȃ��ꍇ
    //        else
    //        {
    //            //�f�o�C�X����ݒ�
    //            mtxParent = pPlayer->GetMtxWorld();
    //        }
    //        
    //        //�e�̃}�g���N�X�Ɗ|�����킹��
    //        D3DXMatrixMultiply(&matWorld, &matWorld, &mtxParent);
    //        pDevice->SetTransform(D3DTS_WORLD, &matWorld);
    //
    //        // ���[���h�s����쐬���AY �����ɔ��]����s����쐬
    //        matWorld = matWorld * matReflect;
    //        m_pReflect->SetMatrix(&matWorld, &LightDir);
    //        pDevice->SetTexture(0, pTexture->GetTexture(CTexture::TEXTURE_NUM_TEST));
    //
    //        // �v���C���[�̕`��
    //        LPD3DXMESH mesh = pPlayer->GetModelAnime(nCount)->GetModelInfo()->GetMesh();
    //        size_t size = pPlayer->GetModelAnime(nCount)->GetModelInfo()->GetNumMat();
    //        for (size_t nCntMat = 0; nCntMat < size; nCntMat++)
    //        {
    //            m_pReflect->BeginPass();
    //            mesh->DrawSubset(nCntMat);
    //            m_pReflect->EndPass();
    //        }
    //    }

        //Z�o�b�t�@�����݋֎~
        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
        //�󃌃��_�����O
        pDevice->SetTexture(0, sky.apTexture[0]);
        D3DXMatrixIdentity(&matWorld);
        matWorld = matWorld * matReflect;
        m_pReflect->SetMatrix(&matWorld, &LightDirReflect);
        m_pReflect->SetAmbient(&m_ReflectSkyAmbiend);
        m_pReflect->BeginPass();
        sky.pMesh->DrawSubset(0);
        m_pReflect->EndPass();
        pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    
        pDevice->SetTexture(0, nullptr);

        m_pReflect->End();

        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
        pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

        //****************************************************************
        // �X�e�b�v�R : ���˃}�b�v���ڂ���
        //****************************************************************
        // �u���[��������̂�CLAMP�ɂ���
        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
        pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

        // �^�[�Q�b�g�ύX
        pDevice->SetRenderTarget(0, m_pBlurFilterSurface);
        pDevice->SetTexture(0, m_pReflectTexture);
        m_pBlurFilter->Render(0);
        pDevice->SetTexture(0, nullptr);

        // �ݒ�����ǂ�
        pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

        // �r���[�|�[�g�����ǂ�
        pDevice->SetViewport(&OldViewport);
        //****************************************************************
        // �X�e�b�v�S : �V�[���̃����_�����O
        //****************************************************************
        // �^�[�Q�b�g�ύX
        pDevice->SetRenderTarget(0, m_pColorSurface);
        // �N���A
        pDevice->Clear(0L,
            nullptr,
            D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
            BlackColor,
            1.0f,
            0L
        );

        // �w�i�����_�����O
        m_pLambert->Begin();
        D3DXMatrixIdentity(&matWorld);

        // �g�嗦�𔽉f
        D3DXMatrixScaling(&mtxScale, ObjSize.x, ObjSize.y, ObjSize.z);
        D3DXMatrixMultiply(&matWorld, &matWorld, &mtxScale);

        //�ʒu�𔽉f
        D3DXMatrixTranslation(&mtxTrans, ObjPos.x, -ObjPos.y, ObjPos.z);
        D3DXMatrixMultiply(&matWorld, &matWorld, &mtxTrans);
        pDevice->SetTransform(D3DTS_WORLD, &matWorld);

        m_pLambert->SetMatrix(&matWorld, &LightDir, m_fZdistance);
        pDevice->SetTexture(0, pTexture->GetTexture(CTexture::TEXTURE_NUM_TEST));
        m_pLambert->SetAmbient(&m_LambertPlayerAmbiend);
        m_pLambert->SetZEnable(false);
        m_pLambert->BeginPass(0);
        map.pMesh->DrawSubset(0);
        m_pLambert->EndPass();
//
//        //�󃌃��_�����O
//        //Z�o�b�t�@�����݋֎~
        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
        pDevice->SetTexture(0, sky.apTexture[0]);
        D3DXMatrixIdentity(&matWorld);
        m_pLambert->SetMatrix(&matWorld, &LightDir, m_fZdistance);
        m_pLambert->SetAmbient(&m_LambertSkyAmbiend);
        m_pLambert->SetZEnable(true);
        m_pLambert->BeginPass(0);
        sky.pMesh->DrawSubset(0);
        m_pLambert->EndPass();
        pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        m_pLambert->End();

//        //���u�����h��L���ɂ���
        //****************************************************************
        // �X�e�b�v�T : ���ʂ̃}�X�N�}�b�v�������_�����O
        //****************************************************************

        //Z�o�b�t�@�ɏ������݂��Ȃ�
        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

        // �T�[�t�F�X�ύX
        pDevice->SetRenderTarget(0, m_pWaterSurface);
        pDevice->SetTexture(0, nullptr);

        //Z�o�b�t�@�̓X�e�b�v�S�̌��ʂ��g�p���邽�ߏ��������Ȃ�
        pDevice->Clear(0L,
            nullptr,
            D3DCLEAR_TARGET ,
            BlackColor,
            1.0f,
            0L
        );

        // ���ʃ��f��
        m_pMask->Begin();
        D3DXMatrixIdentity(&matWorld);
        m_pMask->SetMatrix(&matWorld);
        m_pMask->BeginPass(0);
        model.pMesh->DrawSubset(0);
        m_pMask->EndPass();
        m_pMask->End();

        //****************************************************************
        // �X�e�b�v�U : �V�[���̃����_�����O�C���[�W���o�b�N�o�b�t�@�Ƀ����_�����O����
        //****************************************************************
        // �T�[�t�F�X���o�b�N�o�b�t�@�ɖ߂�
        pDevice->SetRenderTarget(0, OldSurface);
        if (OldSurface)
        {
            OldSurface->Release();
            OldSurface = nullptr;
        }

        pDevice->SetTexture(0, m_pColorTexture);

        // ���ʃ|���S���`��
    //    m_pSquObj->Draw();
        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

        //****************************************************************
        // �X�e�b�v�V : ����
        //****************************************************************
        //�X�e�[�W�Q�ƂR�͂䂪�ݏ������s������CLAMP�ɂ���
        pDevice->SetSamplerState(2, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
        pDevice->SetSamplerState(2, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
        pDevice->SetSamplerState(3, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
        pDevice->SetSamplerState(3, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
        pDevice->SetSamplerState(4, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(4, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

        pDevice->SetTexture(0, pTexture->GetTexture(CTexture::TEXTURE_NUM_TEST));
        pDevice->SetTexture(1, BumpMap);                // �o���v�}�b�v
        pDevice->SetTexture(2, m_pColorTexture);        // �V�[�������_�����O
        pDevice->SetTexture(3, m_pBlurFilterTexture);    // ���˃}�b�v�̂ڂ���
        pDevice->SetTexture(4, m_pWaterTexture);        // ���ʃ}�X�N�}�b�v

        // �����}�b�s���O
        m_pParallax->Begin();
        m_pParallax->SetAmbient(&m_ParallaxAmbiend);
        m_pParallax->SetSpecular(m_fParallaxSpecular);                    // 5.0f
        m_pParallax->SetSpecularPower(m_fParallaxSpecularPower);        // 0.75f
        m_pParallax->SetHeight(m_fParallaxHeight);                        // 0.16f
        m_pParallax->SetRefraction(m_fParallaxRefraction);                // 80.0f

        // ���ʃ��f���̕`��
        D3DXMatrixIdentity(&matWorld);
        //�ʒu�𔽉f
        D3DXMatrixTranslation(&mtxTrans, ObjPos.x, -150.0f, ObjPos.z);
        D3DXMatrixMultiply(&matWorld, &matWorld, &mtxTrans);

        m_pParallax->SetMatrix(&matWorld, &EyePos, &LightDir, m_fZdistance);
        m_pParallax->BeginPass(0);
        model.pMesh->DrawSubset(0);
        m_pParallax->EndPass();
        m_pParallax->End();

        // �e�N�X�`�����N���A
        pDevice->SetTexture(0, nullptr);
        pDevice->SetTexture(1, nullptr);
        pDevice->SetTexture(2, nullptr);
        pDevice->SetTexture(3, nullptr);
        pDevice->SetTexture(4, nullptr);

        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(1, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(1, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(2, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(2, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(3, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(3, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(4, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(4, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
        pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    }
}

//=============================================================================
// Imgui���
//=============================================================================
void CWaterFresnel::ShowInfo()
{
#ifdef _DEBUG

    //�����_���[�ŊǗ����Ă��̏��
    ImGui::Begin("DebugInfo");

    if (ImGui::CollapsingHeader("WaterFresnelInfo"))
    {
        LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();    // �f�o�C�X�̎擾

        if (ImGui::TreeNode("Wave"))
        {
            // �ړ���
            ImGui::SliderFloat("WaveSpeed", &m_fWaveSpeed, 0.0f, 2.0f);
            ImGui::SliderFloat("Zdistance", &m_fZdistance, 0.0f, 5000.0f);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Reflect"))
        {
            ImGui::SliderFloat4("PlayerAmbient", m_ReflectPlayerAmbiend, 0.0f, 1.0f);
            ImGui::SliderFloat4("SkyAmbient", m_ReflectSkyAmbiend, 0.0f, 1.0f);
            ImGui::SliderFloat("Height", &m_fReflectHeight, 0.0f, 30.0f);
            ImGui::TreePop();

        }
        if (ImGui::TreeNode("Lambert"))
        {
            ImGui::SliderFloat4("PlayerAmbient", m_LambertPlayerAmbiend, 0.0f, 1.0f);
            ImGui::SliderFloat4("SkyAmbient", m_LambertSkyAmbiend, 0.0f, 1.0f);
            ImGui::TreePop();

        }
        if (ImGui::TreeNode("Parallax"))
        {
            // �ړ���
            ImGui::SliderFloat4("Ambient", m_ParallaxAmbiend, 0.0f, 1.0f);
            ImGui::SliderFloat("Specular", &m_fParallaxSpecular, 0.0f, 10.0f);
            ImGui::SliderFloat("SpecularPower", &m_fParallaxSpecularPower, 0.0f, 5.0f);
            ImGui::SliderFloat("Height", &m_fParallaxHeight, 0.0f, 5.0f);
            ImGui::SliderFloat("Refraction", &m_fParallaxRefraction, 0.0f, 1000.0f);
            ImGui::TreePop();
        }
    }

    ImGui::End();
#endif // !_DEBUG
}