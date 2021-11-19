//=============================================================================
// �e�X�g[test_character.cpp]
// Author : Konishi Yuuto
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "test_character.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"
#include "collision.h"
#include "fade.h"
#include "texture.h"
#include "resource_manager.h"
#include "motion.h"
#include "game.h"

//=============================================================================
// �}�N����`
// Author : Konishi Yuuto
//=============================================================================
#define PLAYER_SPEED            (10.0f)                                 // �v���C���[�̈ړ���
#define PLAYER_ROT_SPEED        (0.1f)                                  // �L�����N�^�[�̉�]���鑬�x
#define SIZE                    (D3DXVECTOR3(1200.0f,1000.0f,1200.0f))  // �T�C�Y

//=============================================================================
// ���������֐�
// Author : Konishi Yuuto
//=============================================================================
CTestCharacter *CTestCharacter::Create(const D3DXVECTOR3 &pos)
{
    CTestCharacter *pPlayer = new CTestCharacter;

    // !nullcheck
    if (pPlayer)
    {
        // ����������
        pPlayer->SetCharacterInfo(pos, ZeroVector3);
        pPlayer->Init();

        return pPlayer;
    }

    return nullptr;
}

//=============================================================================
// �R���X�g���N�^
// Author : Konishi Yuuto
//=============================================================================
CTestCharacter::CTestCharacter(PRIORITY Priority) : CCharacter(Priority)
{
    m_rotDest = ZeroVector3;
    m_bMove = false;
}

//=============================================================================
// �f�X�g���N�^
// Author : Konishi Yuuto
//=============================================================================
CTestCharacter::~CTestCharacter()
{
}

//=============================================================================
// �����������֐�
// Author : Konishi Yuuto
//=============================================================================
HRESULT CTestCharacter::Init()
{
    // CXfile�擾
    CXfile *pXfile = CManager::GetInstance()->GetResourceManager()->GetXfileClass();

    // !nullcheck
    if (pXfile)
    {
        SetUseShadow();                                 // �e�̎g�p
        ModelCreate(CXfile::HIERARCHY_XFILE_NUM_TEST);  // ���f���̐���
        SetShadowRotCalculation();                      // �e�̌���
    }

    // ����������
    CCharacter::Init();

    JsonLoad();

    // ������
    m_rotDest = GetRot();   // ����
    SetSize(SIZE);          // �T�C�Y�ݒ�
    SetSpeed(PLAYER_SPEED); // �X�s�[�h�ݒ�

    return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Konishi Yuuto
//=============================================================================
void CTestCharacter::Uninit()
{
    CCharacter::Uninit();
}

//=============================================================================
// �X�V�֐������֐�
// Author : Konishi Yuuto
//=============================================================================
void CTestCharacter::Update()
{

}

//=============================================================================
// �`�揈���֐�
// Author : Konishi Yuuto
//=============================================================================
void CTestCharacter::Draw()
{
    // �`��
    CCharacter::Draw();
}

//=============================================================================
// ��ԍX�V
// Author : Konishi Yuuto
//=============================================================================
void CTestCharacter::UpdateState()
{

}

//=============================================================================
// �ړ�����
// Author : Konishi Yuuto
//=============================================================================
void CTestCharacter::Move()
{

}

HRESULT CTestCharacter::JsonLoad()
{
 // JSON�f�[�^�̓ǂݍ��݁B
    ifstream ifs("data/Text/json/test.json", ios::in);
    if (ifs.fail()) 
    {
        cerr << "failed to read test.json" << endl;
        return 1;
    }

    const string json((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());

    // JSON�f�[�^����͂���B
    picojson::value v;
    const string err = picojson::parse(v, json);
    if (err.empty() == false) 
    {
        cerr << err << endl;
        return 2;
    }

    picojson::object& obj = v.get<picojson::object>();

    double dSpeed = obj["Player"].get<picojson::object>()
        ["SPEED"].get<double>();
    dSpeed = 10.00;

//    picojson::array arr;
//    arr.emplace_back(picojson::value(dSpeed));

    obj["Player"].get<picojson::object>()
        ["SPEED"] = picojson::value(dSpeed);

    std::ofstream ofs("data/Text/json/test.json");
    ofs << picojson::value(obj).serialize(true) << std::endl;

    ifs.close();
    ofs.close();

    return S_OK;
}

void CTestCharacter::JsonWrite()
{
}

void CTestCharacter::CreateModel()
{
}
