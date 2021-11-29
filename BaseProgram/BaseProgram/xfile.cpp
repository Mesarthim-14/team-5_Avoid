//=============================================================================
//
// X�t�@�C���̊Ǘ��N���X [xfile.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "xfile.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CXfile::CXfile()
{
    memset(m_aXfile, 0, sizeof(m_aXfile));
    memset(m_pFileName, 0, sizeof(m_pFileName));
    memset(m_nMaxParts, 0, sizeof(m_nMaxParts));

    // �K�w�\�����f��������
    for (int nCount = 0; nCount < HIERARCHY_XFILE_NUM_MAX; nCount++)
    {
        m_apHierarchyModel[nCount].clear();
    }

    // ���f���t�@�C��������
    for (int nCount = 0; nCount < HIERARCHY_XFILE_NUM_MAX; nCount++)
    {
        // ����������
        m_apModelFile[nCount].clear();
    }

    // X�t�@�C���l�[�����擾
    m_aXfileName =
    {
        { "data/Model/Normal/block.x" },            // �e�X�g�u���b�N
        { "data/Model/Normal/map.x" },              // �}�b�v
        { "data/Model/Normal/CheckFlag.x" },        // �`�F�b�N�|�C���g
        { "data/Model/Normal/plane.x" },            // ����
        { "data/Model/Normal/sky.x" },              // ��
        { "data/Model/Normal/enemy_box.x" },        // ���G�l�~�[
        { "data/Model/Normal/susumuashiba.x" },     // �i�ޑ���
        { "data/Model/Normal/Rubble1.x" },          // ���I
        { "data/Model/Normal/Rubble2.x" },          // ���I
        { "data/Model/Normal/kaitenyuka_shita.x" }, // ��]��
        { "data/Model/Normal/kaitenyuka_ue.x" },    // ��]��
        { "data/Model/Normal/Cylinder.x" },         // ��M
        { "data/Model/Normal/Slope.x" },            // �⓹
        { "data/Model/Normal/HeelPoint.x" },        // �񕜃|�C���g
        { "data/Model/Normal/Cannon.x" },           // ��C
        { "data/Model/Normal/hashiwatashi.x" },     // ��
        { "data/Model/Normal/CannonBullet.x" },     // ��C�̒e
        { "data/Model/Normal/ugokuashiba.x" },      // �Q�̑���
        { "data/Model/Normal/sky_blue5.x" },        // ����
        { "data/Model/Normal/Kraken_Bullet.x" },    // �N���[�P���̒e
    };
    
    // �K�w�\�����f��
    m_aHierarchyXfileName =
    {
        { "data/Text/Test/motion_test.txt"},        // �v���C���[
    };
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CXfile::~CXfile()
{
    m_aXfileName.clear();
    m_aHierarchyXfileName.clear();
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CXfile * CXfile::Create()
{
    // �������m��
    CXfile *pXfile = new CXfile;
    if (pXfile)
    {
    return pXfile;
    }

    return nullptr;
}

//=============================================================================
// X�t�@�C�����[�h
//=============================================================================
HRESULT CXfile::ModelLoad()
{
    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    size_t size = m_aXfileName.size();
    for (size_t nCount = 0; nCount < size; nCount++)
    {
        // X�t�@�C���̓ǂݍ���
        D3DXLoadMeshFromX(m_aXfileName.at(nCount).data(),
            D3DXMESH_SYSTEMMEM,
            pDevice,
            nullptr,
            &m_aXfile[nCount].pBuffMat,
            nullptr,
            &m_aXfile[nCount].dwNumMat,
            &m_aXfile[nCount].pMesh);
    }
    
    for (int nCount = 0; nCount < XFILE_NUM_MAX; nCount++)
    {
        //�}�e���A�����̉��
        D3DXMATERIAL *materials = (D3DXMATERIAL*)m_aXfile[nCount].pBuffMat->GetBufferPointer();

        for (int nCntMat = 0; nCntMat < (int)m_aXfile[nCount].dwNumMat; nCntMat++)
        {
            LPDIRECT3DTEXTURE9 pTexture = nullptr;
            
            // �t�@�C���l�[���̎擾
            char cData[256] = {};
            sprintf(cData, "data/Texture/%s", materials[nCntMat].pTextureFilename);
            
            // �e�N�X�`���̓ǂݍ���
            D3DXCreateTextureFromFile(pDevice, cData, &pTexture);
            
            // �e�N�X�`�����擾
            m_aXfile[nCount].apTexture.push_back(pTexture);
        }
    }

    return S_OK;
}

//=============================================================================
// X�t�@�C���A�����[�h
//=============================================================================
void CXfile::ModelUnLoad()
{
    for (int nCount = 0; nCount < XFILE_NUM_MAX; nCount++)
    {
        //���b�V���̔j��
        if (m_aXfile[nCount].pMesh)
        {
            m_aXfile[nCount].pMesh->Release();
            m_aXfile[nCount].pMesh = nullptr;
        }
        //�}�e���A���̔j��
        if (m_aXfile[nCount].pBuffMat)
        {
            m_aXfile[nCount].pBuffMat->Release();
            m_aXfile[nCount].pBuffMat = nullptr;
        }
        
        // �e�N�X�`���̔j��
        size_t size = m_aXfile[nCount].apTexture.size();
        for (size_t nCntTexture = 0; nCntTexture < size; nCntTexture++)
        {
            if (m_aXfile[nCount].apTexture.at(nCntTexture))
            {
                m_aXfile[nCount].apTexture.at(nCntTexture)->Release();
                m_aXfile[nCount].apTexture.at(nCntTexture) = nullptr;
            }
        }
        
        // �e�N�X�`���̔z��N���A
        m_aXfile[nCount].apTexture.clear();
    }
}

//=============================================================================
// �K�w�\���̃��f���t�@�C���ǂݍ���
//=============================================================================
HRESULT CXfile::HierarchyReadFile()
{
    FILE *pFile = nullptr;        //FILE�|�C���^
    
    // �t�@�C���̖��O��ݒ�
    SetHierarchyFileName();
    
    for (int nModelCnt = 0; nModelCnt < HIERARCHY_XFILE_NUM_MAX; nModelCnt++)
    {
        // �t�@�C���I�[�v��
        pFile = fopen(m_pFileName[nModelCnt].c_str(), "r");
        
        string aHeadData;
        string aModeName;
        
        int nModelIndex = 0;    // ���f���̃C���f�b�N�X
        int nMotionType = 0;    // ���[�V�����̃^�C�v
        int nKeyNum = 0;        // �L�[�ԍ�
        int nMotionNum = 0;        // ���[�V�����ԍ�
        
        if (pFile)
        {
            do
            {
                // ��������N���A����
                aHeadData.clear();
                
                //���ǂݍ���Ń��[�h���𒊏o
                getline((ifstream)pFile, aHeadData);
                
                aModeName = aHeadData;
                
                if (aHeadData.find("MODEL_FILENAME") != string::npos)
                {
                    // ���f���t�@�C���̍\����
                    MODELFILE aModelFile = {};
                
                    aModelFile.aFileName = CLibrary::split(aHeadData, ' ', 2);
                
                    if (aModelFile.aFileName.c_str() != NULL)
                    {
                        // �t�@�C�����m��
                        m_apModelFile[nModelCnt].push_back(aModelFile);
                
                        //�C���f�b�N�X���P�i�߂�
                        nModelIndex++;
                    }
                }
                
                if (aModeName.compare(string("CHARACTERSET")) == 0)
                {
                    //�C���f�b�N�X���ŏ��ɖ߂�
                    nModelIndex = 0;
                    
                    //END_MOTIONSET��ǂݍ��ނ܂ŌJ��Ԃ�
                    while (aModeName.compare(string("END_CHARACTERSET")) != 0)
                    {
                        //���ǂݍ���Ń��[�h���𒊏o
                        getline((ifstream)pFile, aHeadData);
                    
                        // �����̕���
                        aModeName = CLibrary::split(aHeadData, ' ', 0);
                    
                        if (aModeName.compare(string("PARTSSET")) == 0)
                        {
                            //END_PARTSSET��ǂݍ��ނ܂ŌJ��Ԃ�
                            while (aModeName.compare(string("END_PARTSSET")) != 0)
                            {
                                //���ǂݍ���Ń��[�h���𒊏o
                                getline((ifstream)pFile, aHeadData);
                                aModeName = CLibrary::split(aHeadData, ' ', 0);
                    
                                if (aModeName.find(string("PARENT")) == 0)
                                {
                                    //�e�q���̐ݒ�
                                    sscanf(aHeadData.c_str(), "%*s %*s %d", &m_apModelFile[nModelCnt].at(nModelIndex).nParent);
                    
                                }
                                //if (strcmp(aModeName, "POS") == 0)
                                if (aModeName.find(string("POS")) == 0)
                                {
                                    //�ʒu�̐ݒ�
                                    sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_apModelFile[nModelCnt].at(nModelIndex).offsetPos.x,
                                        &m_apModelFile[nModelCnt].at(nModelIndex).offsetPos.y, &m_apModelFile[nModelCnt].at(nModelIndex).offsetPos.z);
                                }
                                //if (strcmp(aModeName, "ROT") == 0)
                                if (aModeName.find(string("ROT")) == 0)
                                {
                                    //�����̐ݒ�
                                    sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_apModelFile[nModelCnt].at(nModelIndex).offsetRot.x,
                                        &m_apModelFile[nModelCnt].at(nModelIndex).offsetRot.y, &m_apModelFile[nModelCnt].at(nModelIndex).offsetRot.z);
                                }
                            }
                    
                            //�C���f�b�N�X���P�i�߂�
                            nModelIndex++;
                    
                            // �p�[�c���𐔂���
                            m_nMaxParts[nModelCnt]++;
                    
                        }
                    }
                }
            
            } while (aModeName.find("END_SCRIPT") == string::npos);
            
            // �t�@�C���N���[�Y
            ::fclose(pFile);
        }
        else
        {
            // ���s�����ꍇ���b�Z�[�W�{�b�N�X��\��
            MessageBox(nullptr, "�q�G�����L�[�t�@�C�����J���̂Ɏ��s���܂���", "�x��", MB_OK | MB_ICONEXCLAMATION);
        
            return    E_FAIL;
        }
    }
    
    return S_OK;
}

//=============================================================================
// �K�w�\���̃��f�����[�h
//=============================================================================

HRESULT CXfile::HierarchyModelLoad()
{
    //�f�o�C�X���̎擾

    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    for (int nXFileNumCnt = 0; nXFileNumCnt < HIERARCHY_XFILE_NUM_MAX; nXFileNumCnt++)
    {
        for (int nCount = 0; nCount < m_nMaxParts[nXFileNumCnt]; nCount++)
        {
            MODEL Hierarchy = { nullptr, nullptr, 0, {} };

            //���f���̓ǂݍ���
            D3DXLoadMeshFromX(m_apModelFile[nXFileNumCnt].at(nCount).aFileName.c_str(),
                D3DXMESH_SYSTEMMEM,
                pDevice,
                nullptr,
                &Hierarchy.pBuffMat,
                nullptr,
                &Hierarchy.dwNumMat,
                &Hierarchy.pMesh);

            //�}�e���A�����̉��
            D3DXMATERIAL *materials = (D3DXMATERIAL*)Hierarchy.pBuffMat->GetBufferPointer();

            for (int nCntMat = 0; nCntMat < (int)Hierarchy.dwNumMat; nCntMat++)
            {
                LPDIRECT3DTEXTURE9 pTexture = nullptr;

                if (materials[nCntMat].pTextureFilename)
                {
                    // �t�@�C���l�[���̎擾
                    char cData[256] = {};
                    sprintf(cData, "data/Texture/%s", materials[nCntMat].pTextureFilename);

                    // �e�N�X�`���̓ǂݍ���
                    D3DXCreateTextureFromFile(pDevice, cData, &pTexture);
                }

                // �e�N�X�`�������擾
                Hierarchy.apTexture.push_back(pTexture);
            }

            // ���f�������擾
            m_apHierarchyModel[nXFileNumCnt].push_back(Hierarchy);
        }
    }

    return S_OK;
}

//=============================================================================
// �K�w�\���̃A�����f�����[�h
//=============================================================================

void CXfile::HierarchyModelUnLoad()
{
    for (int nXFileNumCnt = 0; nXFileNumCnt < HIERARCHY_XFILE_NUM_MAX; nXFileNumCnt++)
    {
        size_t size = m_apHierarchyModel[nXFileNumCnt].size();
        for (size_t nCount = 0; nCount < size; nCount++)
        {
            //�}�e���A�����̔j��
            if (m_apHierarchyModel[nXFileNumCnt].at(nCount).pBuffMat)
            {
                m_apHierarchyModel[nXFileNumCnt].at(nCount).pBuffMat->Release();
                m_apHierarchyModel[nXFileNumCnt].at(nCount).pBuffMat = nullptr;
            }

            //���b�V�����̔j��
            if (m_apHierarchyModel[nXFileNumCnt].at(nCount).pMesh)
            {
                m_apHierarchyModel[nXFileNumCnt].at(nCount).pMesh->Release();
                m_apHierarchyModel[nXFileNumCnt].at(nCount).pMesh = nullptr;
            }

            // �e�N�X�`���̊J��
            for (size_t nCntTexture = 0; nCntTexture < m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.size(); nCntTexture++)
            {
                if (m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.at(nCntTexture))
                {
                    m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.at(nCntTexture)->Release();
                    m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.at(nCntTexture) = nullptr;
                }
            }

            // �e�N�X�`���̔z��N���A
            m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.clear();
        }

        // �K�w�\���̔z��N���A
        m_apHierarchyModel[nXFileNumCnt].clear();
    }
}

//=============================================================================
// �t�@�C���̖��O��ݒ�
//=============================================================================

void CXfile::SetHierarchyFileName()
{
    size_t size = m_aHierarchyXfileName.size();
    for (size_t nCount = 0; nCount < size; nCount++)
    {
        // ���O������
        m_pFileName[nCount] = m_aHierarchyXfileName.at(nCount);
    }
}

//=============================================================================
// �S�Ẵ��[�h
//=============================================================================

void CXfile::LoadAll()
{
    // ���f�����[�h
    ModelLoad();

    // �K�w�\���̃t�@�C���ǂݍ���
    HierarchyReadFile();

    // �K�w�\���̃��f���ǂݍ���
    HierarchyModelLoad();
}

//=============================================================================
// �S�ẴA�����[�h
//=============================================================================

void CXfile::UnLoadAll()
{
    ModelUnLoad();
    HierarchyModelUnLoad();
}

//=============================================================================
// ���f���Ɏg�p����e�N�X�`�����
//=============================================================================

LPDIRECT3DTEXTURE9 *CXfile::GetXfileTexture(const XFILE_NUM &TexNum)
{
    if (TexNum < XFILE_NUM_MAX)
    {
        if (m_aXfile[TexNum].apTexture.data())
        {
            return m_aXfile[TexNum].apTexture.data();
        }
    }

    return nullptr;
}