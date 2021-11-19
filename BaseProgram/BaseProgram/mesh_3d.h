#ifndef _MESH_3D_H_
#define _MESH_3D_H_
//=============================================================================
//
// 3D���b�V�������N���X�w�b�_�[ [mesh_3d.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene_base.h"

//=============================================================================
// ���b�V���t�B�[���h�N���X
//=============================================================================
class CMesh3d : public CSceneBase
{
public:
    //=============================================================================
    // �񋓌^
    //=============================================================================
    enum MESH_TYPE
    {
        MESH_TYPE_NONE = -1,    // �����l
        MESH_TYPE_TUBE_6,       // 6�p�`�̉~��
        MESH_TYPE_PILLAR_6,     // 6�p�`�̉~��
        MESH_TYPE_MAX           // �ő�l
    };


    CMesh3d(PRIORITY Priority = PRIORITY_0);    // �R���X�g���N�^
    ~CMesh3d();                                 // �f�X�g���N�^

    virtual HRESULT Init() = 0;                 // ����������
    virtual void Update() = 0;                  // �X�V����
    virtual void Draw();                        // �`�揈��

    static HRESULT ReadFile();                  // �t�@�C���ǂݍ���

protected:
    // ���p�`�����擾����\����
    struct CYLINDER
    {
        int nNumX;  // ���p�`���̒l
        int nNumY;  // ���p�`���̒l
    };

    // 3D���b�V���̍\����
    struct MESH_3D
    {
        CYLINDER CylinderNum;   // ���p�`��
        D3DXVECTOR2 size;       // �T�C�Y
    };

    // Set�֐�
    inline void SetNumVertex(const int &nNumVertex)                 { m_nNumVertex = nNumVertex; }      // ���_��
    inline void SetNumIndex(const int &nNumIndex)                   { m_nNumIndex = nNumIndex; }        // �C���f�b�N�X��
    inline void SetNumPolygon(const int &nNumPolygon)               { m_nNumPolygon = nNumPolygon; }    // �|���S����
    inline void BindIdxBuff(const LPDIRECT3DINDEXBUFFER9 &IdxBuff)  { m_pIdxBuff = IdxBuff; }           // �o�b�t�@�ԍ��̐ݒ�
    inline void BindMtxWorld(const D3DXMATRIX &mtxWorld)            { m_mtxWorld = mtxWorld; }          // �}�g���N�X���
    inline void SetOneSize(const D3DXVECTOR2 &OneSize)              { m_OneSize = OneSize; }            // ��̃u���b�N�̑傫��
    inline void SetPieceNum(const INT_VERTEX_2D &PieceNum)          { m_PieceNum = PieceNum; }          // �u���b�N�̐�
    inline void SetMeshNum(const MESH_TYPE &MeshNum)                { m_MeshNum = MeshNum; }            // ���b�V���̔ԍ��̐ݒ�
    void SetCylinderNum(const CYLINDER &CylinderNum, 
        const MESH_TYPE &typeNum)                            { m_Mesh3D[typeNum].CylinderNum = CylinderNum; }    // ���p�`���ݒ肷��

    // Get�֐�
    inline int &GetNumVertex()                                  { return m_nNumVertex; }                    // ���_���̏��
    inline int &GetNumIndex()                                   { return m_nNumIndex; }                     // �C���f�b�N�X���̏��
    inline int &GetNumPolygon()                                 { return m_nNumPolygon; }                   // �|���S�����̏��
    inline CYLINDER &GetCylinderNum(const MESH_TYPE &typeNum)   { return m_Mesh3D[typeNum].CylinderNum; }   // ���p�`���̏��
    inline MESH_TYPE &GetMeshNum()                              { return m_MeshNum; }                       // ���b�V���̔ԍ�
    inline D3DXVECTOR2 &GetOneSize()                            { return m_OneSize; }                       // �T�C�Y
    inline INT_VERTEX_2D &GetPieceNum()                         { return m_PieceNum; }                      // �u���b�N�̐�
    inline LPDIRECT3DINDEXBUFFER9 GetIdxBuff()                  { return m_pIdxBuff; }                      // �o�b�t�@�ԍ��̏��
    inline D3DXMATRIX GetMtxWorld()                             { return m_mtxWorld; }                      // �}�g���N�X���
    inline static MESH_3D GetMesh3D(const MESH_TYPE &MeshNum)   { return m_Mesh3D[MeshNum]; }               // ���b�V���̏��

private:
    LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;      // �o�b�t�@�̔ԍ�
    D3DXMATRIX m_mtxWorld;                  // ���[���h�}�g���b�N�X
    D3DXVECTOR3 m_move;                     // �ړ�
    D3DXVECTOR2 m_OneSize;                  // ��̃|���S���̑傫��
    INT_VERTEX_2D m_PieceNum;               // 1�u���b�N�̐�
    MESH_TYPE m_MeshNum;                    // ���b�V���̔ԍ�
    int m_nNumVertex;                       // �����_��
    int m_nNumIndex;                        // ���C���f�b�N�X��
    int m_nNumPolygon;                      // ���|���S����
    static MESH_3D m_Mesh3D[MESH_TYPE_MAX]; // 3D���b�V���̍\���̏��
};

#endif