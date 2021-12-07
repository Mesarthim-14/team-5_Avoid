//=============================================================================
//
// ���C�u�������� [library.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "library.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "json.h"
#include "keyboard.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
bool CLibrary::m_bWireFrame = false;
bool CLibrary::m_bLighting = true;
bool CLibrary::m_bDebugPlayer = false;
int CLibrary::m_Culling = false;

//=============================================================================
// ������𕪊����A���o���N���X
//=============================================================================
string CLibrary::split(const string str, const char del, const int nNum)
{
    // ���[�J���ϐ��錾
    int first = 0;                          // ���Ԗڂ̕�����
    int last = str.find_first_of(del);      // �w��̕����܂ł̐�
    int t_last = str.find_first_of('\t');   // �^�u�܂ł̕�����
    int nCount = 0;                         // ������̃J�E���g
    int nCount_t = 0;                       // �^�u�̃J�E���g
    string result;                          // �Ԃ�������

    // �ϐ�str�̕����񐔂܂�
    while (first < (int)str.size())
    {
        if (last == -1 && t_last == 0)
        {
            int nCount_t = 0;
            
            while (str.find_first_of('\t', nCount_t) == 0)
            {
                // \t�̃J�E���g
                nCount_t++;

            }
            // �w��̔ԍ�����擾
            string subStr(str, first + nCount_t, str.size());

            // �w�肳�ꂽ�������̂Ƃ�
            if (nCount == nNum)
            {
                // �������Ԃ�
                result = subStr;
                break;
            }
        }
        else if (t_last == 0)
        {
            int nNum = t_last;

            while (nNum == 0)
            {
                // \t�̃J�E���g
                nCount_t++;
                nNum = str.find_first_of('\t', nCount_t-1);        // �^�u�܂ł̕�����
            }
            first += nCount_t;
        }

        // �����̔�r
        if (last < t_last)
        {
            // �w��̔ԍ�����擾
            string subStr(str, first, last - first);
            // �w�肳�ꂽ�������̂Ƃ�
            if (nCount == nNum)
            {
                // �������Ԃ�
                result = subStr;
                break;
            }

            // �w��̕�������
            first = last + 1;
        }
        else
        {
            // �w��̔ԍ�����擾
            string subStr(str, first, t_last - first);
            // �w�肳�ꂽ�������̂Ƃ�
            if (nCount == nNum)
            {
                // �������Ԃ�
                result = subStr;
                break;
            }

            // �^�u����������i�߂�
            first = t_last + 1;
        }

        // �����̎擾
        last = str.find_first_of(del, first);       // �w��̕������܂ł̐�
        t_last = str.find_first_of('\t', first);    // �^�u�܂ł̕�����

        // �����̔�r
        if (last < t_last)
        {
            if (last == string::npos)
            {
                last = str.size();
            }
        }
        else
        {
            if (t_last == string::npos)
            {
                t_last = str.size();
            }
        }

        // �񐔂̃J�E���g
        nCount++;
    }

    return result;
}

//=============================================================================
// �}�g���N�X�̐ݒ�
//=============================================================================
void CLibrary::ConfigMatrix(D3DXMATRIX* pMtx, D3DXVECTOR3 const &rPos, D3DXVECTOR3 const &rRot)
{
    D3DXMATRIX mtxRot, mtxTrans;

    //���[���h�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(pMtx);

    // ��]�𔽉f
    D3DXMatrixRotationYawPitchRoll(&mtxRot, rRot.y, rRot.x, rRot.z);
    D3DXMatrixMultiply(pMtx, pMtx, &mtxRot);

    // �ʒu�𔽉f
    D3DXMatrixTranslation(&mtxTrans, rPos.x, rPos.y, rPos.z);
    D3DXMatrixMultiply(pMtx, pMtx, &mtxTrans);
}

//=============================================================================
// �p�x�̏C��
//=============================================================================
void CLibrary::RotFix(float &fRot)
{
    //������3.14���ȏ�̎�
    if (fRot > D3DX_PI)
    {
        //6.28����
        fRot -= D3DX_PI * 2;
    }
    //������-3.14�ȉ��̎�
    if (fRot < -D3DX_PI)
    {
        //6.28���Z
        fRot += D3DX_PI * 2;
    }
}

//=============================================================================
// �p�x�̏C��
//=============================================================================
void CLibrary::RotFixVector3(D3DXVECTOR3 & rot)
{
    CLibrary::RotFix(rot.x);
    CLibrary::RotFix(rot.y);
    CLibrary::RotFix(rot.z);
}

//=============================================================================
// �����_���̒l��Ԃ� (�w�肵��+-�͈̔͂��o��)
//=============================================================================
int CLibrary::Random(const int &nNum)
{
    random_device rnd;
    mt19937 mt(rnd());
    uniform_int_distribution<> rand(-nNum, nNum);

    return rand(mt);
}

//=============================================================================
// �����_���̒l��Ԃ� (�w�肵����͈̔͂��o��)
//=============================================================================
int CLibrary::Random(const int &nMin, const int &nMax)
{
    random_device rnd;
    mt19937 mt(rnd());
    uniform_int_distribution<> rand(nMin, nMax);

    return rand(mt);
}

//=============================================================================
// �����_���̒l��Ԃ� (�w�肵��+-�͈̔͂��o��)
//=============================================================================
float CLibrary::Random(const float &fNum)
{
    random_device rnd;
    mt19937 mt(rnd());
    uniform_real_distribution<> rand(-fNum, fNum);

    return (float)rand(mt);
}

//=============================================================================
// �����_���̒l��Ԃ� (�w�肵����͈̔͂��o��)
//=============================================================================
float CLibrary::Random(const float &fMin, const float &fMax)
{
    random_device rnd;
    mt19937 mt(rnd());
    uniform_real_distribution<> rand(fMin, fMax);

    return (float)rand(mt);
}

//*****************************************************************************
// �_�̎O������]����
//*****************************************************************************
void CLibrary::Rotate3D(D3DXVECTOR3 &PointPos, const D3DXVECTOR3 &rot)
{
    //X����]
    PointPos = D3DXVECTOR3(
        PointPos.x,
        PointPos.y * cosf(rot.x) + PointPos.z * -sinf(rot.x),
        PointPos.y * sinf(rot.x) + PointPos.z * cosf(rot.x));
    float a = cosf(rot.x);
    //Y����]
    PointPos = D3DXVECTOR3(
        PointPos.x * cosf(rot.y) + PointPos.z * sinf(rot.y),
        PointPos.y,
        PointPos.x * -sinf(rot.y) + PointPos.z * cosf(rot.y));

    //Z����]
    PointPos = D3DXVECTOR3(
        PointPos.x * cosf(rot.z) + PointPos.y * -sinf(rot.z),
        PointPos.x * sinf(rot.z) + PointPos.y * cosf(rot.z),
        PointPos.z);
}

//*****************************************************************************
// �������ɓ��e���ꂽ���������瓊�e���������Z�o
//*****************************************************************************
float CLibrary::LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3)
{
    // 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
    // ������Sep�͕W��������Ă��邱��
    float r1 = (float)fabs(D3DXVec3Dot(Sep, e1));
    float r2 = (float)fabs(D3DXVec3Dot(Sep, e2));
    float r3 = (float)(e3 ? (fabs(D3DXVec3Dot(Sep, e3))) : 0);
    return r1 + r2 + r3;
}

//*****************************************************************************
// vector3���m�̏�Z
//*****************************************************************************
D3DXVECTOR3 CLibrary::MultiplyVector3(const D3DXVECTOR3 &vector1, const D3DXVECTOR3 &vector2)
{
    return D3DXVECTOR3(vector1.x * vector2.x, vector1.y * vector2.y, vector1.z * vector2.z);
}

//*****************************************************************************
// vector3���m�̏��Z
//*****************************************************************************
D3DXVECTOR3 CLibrary::DivisionVector3(const D3DXVECTOR3 & vector1, const D3DXVECTOR3 & vector2)
{
    return D3DXVECTOR3(DivisionCheck(vector1.x, vector2.x), DivisionCheck(vector1.y, vector2.y), DivisionCheck(vector1.z, vector2.z));
}

//*****************************************************************************
// 0�`�F�b�N�L�̏��Z(float�^�̂�)
//*****************************************************************************
float CLibrary::DivisionCheck(const float & num1, const float & num2)
{
    if (num1 == 0.0f && num2 == 0.0f)
    {
        return 0.0f;
    }

    return num1 / num2;
}

//=============================================================================
// ��_�̋������v�Z
//=============================================================================
float CLibrary::CalDistance(const D3DXVECTOR3 & pos1, const D3DXVECTOR3 & pos2)
{
    return D3DXVec3Length(&(pos1 - pos2));
}

//=============================================================================
// �L�[�{�[�h�̉������ݔ���
//=============================================================================
BOOL CLibrary::KeyboardPress(const int &nKey)
{
    CInputKeyboard *pKeyboard = CManager::GetInstance()->GetKeyboard();
    return pKeyboard->GetPress(nKey);
}

//=============================================================================
// �L�[�{�[�h�̉���������
//=============================================================================
BOOL CLibrary::KeyboardTrigger(const int &nKey)
{
    CInputKeyboard *pKeyboard = CManager::GetInstance()->GetKeyboard();
    return pKeyboard->GetTrigger(nKey);
}

//=============================================================================
// �L�[�{�[�h�̗���������
//=============================================================================
BOOL CLibrary::KeyboardRelease(const int &nKey)
{
    CInputKeyboard *pKeyboard = CManager::GetInstance()->GetKeyboard();
    return pKeyboard->GetRelease(nKey);
}

//=============================================================================
// XZ(����)�̊p�x�����߂�
//=============================================================================
float CLibrary::CalAngleXZ(const D3DXVECTOR3 & This, const D3DXVECTOR3 & Target)
{
    return atan2f((This.x - Target.x), (This.z - Target.z));
}

//=============================================================================
// XZ(����)�̒Ǐ]
//=============================================================================
D3DXVECTOR3 CLibrary::FollowMoveXZ(const D3DXVECTOR3 &This, const D3DXVECTOR3 &Target, const float &fSpeed)
{
    float fAngle = CLibrary::CalAngleXZ(This, Target);    // �p�x�����߂�

    return D3DXVECTOR3(sinf(fAngle)*-fSpeed, 0.0f, cosf(fAngle)*-fSpeed);
}

//=============================================================================
// json�̃t�@�C�����[�h
//=============================================================================
picojson::value CLibrary::JsonLoadFile(const string &FileName)
{
    // JSON�f�[�^�̓ǂݍ��݁B
    ifstream ifs(FileName, ios::in);
    if (ifs.fail())
    {
        cerr << "failed to jsonfile" << endl;
    }
    const string json((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
    // JSON�f�[�^����͂���B
    picojson::value v;
    const string err = picojson::parse(v, json);
    if (err.empty() == false)
    {
        cerr << err << endl;
    }

    ifs.close();
    return v;
}

//=============================================================================
// Imgui�̐���
//=============================================================================
HRESULT CLibrary::InitImgui(HWND hWnd)
{
    //�Q�[���p�b�h�ƃL�[�{�[�h�̏��擾
    //���L���͖���ĂȂ�����J���̕K�v�͂Ȃ�
    CInputKeyboard *pKeyboard = CManager::GetInstance()->GetKeyboard();

    //NULL�`�F�b�N
    if (!pKeyboard)
    {
        return E_FAIL;
    }

    //create
    IMGUI_CHECKVERSION();

    //����
    ImGui::CreateContext();

    //�f�t�H���g�J���[�ݒ�
    ImGui::StyleColorsDark();

    //������
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX9_Init(CManager::GetInstance()->GetRenderer()->GetDevice());

    return S_OK;
}

//=============================================================================
// Imgui�̏I������
//=============================================================================
void CLibrary::UninitImgui()
{
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

//=============================================================================
// Imgui �f�o�b�O���\��
//=============================================================================
void CLibrary::ShowDebugInfo()
{
#ifdef _DEBUG

    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    //�J�n
    if (ImGui::CollapsingHeader("Debug"))
    {
        //FPS���
        if (ImGui::TreeNode("FPS"))
        {
            //FPS
            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::TreePop();
        }

        //���
        if (ImGui::TreeNode("DebugCommand"))
        {
            //���C���[�t���[��
            if (ImGui::Checkbox("WireFrame", &m_bWireFrame))
            {
                CheckWireMode();
            }

            //���C�e�B���O
            if (ImGui::Checkbox("Lighting", &m_bLighting))
            {
                pDevice->SetRenderState(D3DRS_LIGHTING, m_bLighting);        // ���C�e�B���O���[�h�؂�ւ�
            }
            //�v���C���[�f�o�b�O
            if (ImGui::Checkbox("DebugPlayer", &m_bDebugPlayer))
            {

            }
            ImGui::TreePop();
        }
    }

#endif //DEBUG
}

//=============================================================================
//���C���[�t���[�����ǂ����m�F
//Imgui�̃E�B���h�E�������C���[�t���[���ɂȂ�Ȃ��ׂɕK�v
//=============================================================================
void CLibrary::CheckWireMode()
{
    //�f�o�C�X�擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    //true��false���Ō��߂�
    m_bWireFrame ?
        pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME) :
        pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}