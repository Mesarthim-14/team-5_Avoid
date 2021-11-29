#ifndef _XFILE_H_
#define _XFILE_H_
//=============================================================================
//
// X�t�@�C���Ǘ��w�b�_�[ [xfile.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
//�N���X�錾
//=============================================================================
class CXfile
{
public:
    //=============================================================================
    //�@���f�����̍\����
    //=============================================================================
    struct MODEL
    {
        LPD3DXMESH pMesh;                       // ���b�V�����ւ̃|�C���^
        LPD3DXBUFFER pBuffMat;                  // �}�e���A�����ւ̃|�C���^
        DWORD dwNumMat;                         // �}�e���A�����̐�
        vector<LPDIRECT3DTEXTURE9> apTexture;   // �e�N�X�`���̐�
    };
    
    //=============================================================================
    //�@���f���t�@�C�����̍\����
    //=============================================================================
    struct MODELFILE
    {
    	string aFileName;       // �t�@�C���l�[��
    	D3DXVECTOR3 offsetPos;  // �ʒu�̃I�t�Z�b�g���
    	D3DXVECTOR3 offsetRot;  // �����̃I�t�Z�b�g���
    	int nParent;            // �e���
    };
    
    //=============================================================================
    // X�t�@�C�����f���̔ԍ��̗񋓌^
    //=============================================================================
    enum XFILE_NUM
    {
    
    	XFILE_NUM_NONE = -1,        // �����l
    	XFILE_NUM_TEST_BLOCK,       // �e�X�g�u���b�N
    	XFILE_NUM_MAP,              // �}�b�v
    	XFILE_NUM_CHECK_FLAG,       // �`�F�b�N�|�C���g�̃t���O
    	XFILE_NUM_PLANE,            // ����
    	XFILE_NUM_SKY,              // ��
    	XFILE_NUM_ENEMY_BOX,        // box
    	XFILE_NUM_MOVE_SCAFFOLD,    // �i�ޑ���
    	XFILE_NUM_MOVE_RUBBLE1,     // ���I
    	XFILE_NUM_MOVE_RUBBLE2,     // ���I
    	XFILE_NUM_ROTATE_FLOOR,     // ��]��
    	XFILE_NUM_ROTATE_BODY,      // ��]�{��
    	XFILE_NUM_CYLINDER,         // ��M
    	XFILE_NUM_SLOPE,            // �⓹
    	XFILE_NUM_RECOVER,          // �񕜃|�C���g
    	XFILE_NUM_CANNON,           // ��C
    	XFILE_NUM_BRIDGE,           // ��
    	XFILE_NUM_CANNON_BULLET,    // ��C�̒e
    	XFILE_NUM_SWIRL_SCAFFOLD,   // �Q�̑���
        XFILE_NUM_SKY_BLUE,         // ��
        XFILE_NUM_KRAKEN_BULLET,    // �N���[�P���̒e
    	XFILE_NUM_MAX
    };
    
    //=============================================================================
    // �K�w�\�����f���̔ԍ�
    //=============================================================================
    enum HIERARCHY_XFILE_NUM
    {
        HIERARCHY_XFILE_NUM_NONE = -1,  // �����l
        HIERARCHY_XFILE_NUM_TEST,       // �v���C���[���f��
        HIERARCHY_XFILE_NUM_MAX         // �ő吔
    };
    
    CXfile();   // �R���X�g���N�^
    ~CXfile();  // �f�X�g���N�^
    
    
    static CXfile *Create();    // �C���X�^���X����
    void LoadAll();             // �S�Ẵ��[�h
    void UnLoadAll();           // �S�ẴA�����[�h
    
    // Get�֐�
    inline MODEL GetXfile(const XFILE_NUM &Tex_Num)                                         { return m_aXfile[Tex_Num]; }					// ���f���̏��
    inline MODELFILE GetModelFile(const int &nCount, const HIERARCHY_XFILE_NUM &FileNum)    { return m_apModelFile[FileNum].at(nCount); }	// ���f���p�[�c�̏��
    inline int GetModelParts(const HIERARCHY_XFILE_NUM &FileNum)                            { return m_nMaxParts[FileNum]; }				// ���f���̃p�[�c��
    inline string GetModelFileName(const HIERARCHY_XFILE_NUM &FileNum)                      { return m_pFileName[FileNum]; }				// ���f���t�@�C���̖��O
    inline vector<MODEL> GetHierarchyXfile(const HIERARCHY_XFILE_NUM &FileNum)              { return m_apHierarchyModel[FileNum]; }         // �K�w�\�����f��
    LPDIRECT3DTEXTURE9 *GetXfileTexture(const XFILE_NUM &TexNum);                                                                           // �e�N�X�`���̏��

private:
    // private�֐�
    HRESULT ModelLoad();            // ���f�����[�h
    void ModelUnLoad();             // ���f���A�����[�h
    HRESULT HierarchyReadFile();    // �K�w�\���̂��郂�f���ǂݍ���
    HRESULT HierarchyModelLoad();   // �K�w�\���̃��f�����[�h
    void HierarchyModelUnLoad();    // �K�w�\���̃��f���A�����[�h
    void SetHierarchyFileName();    // �t�@�C���̖��O��ݒ�

    // �����o�ϐ�
    MODEL m_aXfile[XFILE_NUM_MAX];						// X�t�@�C�����̍\����
    vector<string> m_aXfileName;						// X�t�@�C���̖��O
    
    // �K�w�\���̃��f���p
    vector<MODEL> m_apHierarchyModel[HIERARCHY_XFILE_NUM_MAX];  // �K�w�\�����f���̃|�C���^
    vector<MODELFILE> m_apModelFile[HIERARCHY_XFILE_NUM_MAX];   // �K�w�\�����f���̃|�C���^
    vector<string> m_aHierarchyXfileName;                       // �K�w�\��X�t�@�C���̖��O
    string m_pFileName[HIERARCHY_XFILE_NUM_MAX];                // �t�@�C���̖��O
    int m_nMaxParts[HIERARCHY_XFILE_NUM_MAX];                   // �t�@�C�����Ƃ̃p�[�c��
};
#endif
