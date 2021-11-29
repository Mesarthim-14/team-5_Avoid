#ifndef _LIBRARY_H_
#define _LIBRARY_H_
//=============================================================================
//
// ���C�u�������� [library.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "ImGui/Imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "json.h"

//=============================================================================
// �����蔻��N���X
//=============================================================================
class CLibrary
{
public:

    static string split(string str, char del, int nNum);                                                        // ������𕪊����A���o���֐�
    static void ConfigMatrix(D3DXMATRIX *pMtx, D3DXVECTOR3 const &rPos, D3DXVECTOR3 const &rRot);               // �}�g���N�X�̐ݒ�
    static void RotFix(float &fRot);                                                                            // �p�x�̏C��
    static void RotFixVector3(D3DXVECTOR3 &rot);                                                                // �p�x�̏C��
    static int Random(const int &nNum);                                                                         // �����_���ϐ�
    static int Random(const int &nMin, const int &nMax);                                                        // �����_���ϐ�
    static float Random(const float &fNum);                                                                     // �����_���ϐ�
    static float Random(const float &fMin, const float &fMax);                                                  // �����_���ϐ�
    static void Rotate3D(D3DXVECTOR3 &PointPos, const D3DXVECTOR3 &rot);                                        // �_�̎O������]����
    static float CalDistance(const D3DXVECTOR3 &pos1, const D3DXVECTOR3 &pos2);                                 // ��_�̋������v�Z
    static float LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0); // �������ɓ��e���ꂽ���������瓊�e���������Z�o
    static D3DXVECTOR3 MultiplyVector3(const D3DXVECTOR3 &vector1, const D3DXVECTOR3 &vector2);                 // vector3���m�̏�Z
    static D3DXVECTOR3 DivisionVector3(const D3DXVECTOR3 &vector1, const D3DXVECTOR3 &vector2);                 // vector3���m�̏��Z
    static float DivisionCheck(const float &num1, const float &num2);                                           // 0�`�F�b�N�L�̏��Z(float�^�̂�)
    static BOOL KeyboardPress(const int &nKey);                                                                 // �L�[�{�[�h�̉������ݔ���
    static BOOL KeyboardTrigger(const int &nKey);                                                               // �L�[�{�[�h�̉���������
    static BOOL KeyboardRelease(const int &nKey);                                                               // �L�[�{�[�h�̗���������
    static float CalAngleXZ(const D3DXVECTOR3 &This, const D3DXVECTOR3 &Target);                                // XZ(����)�p�x�̂����߂�
    static D3DXVECTOR3 FollowMoveXZ(const D3DXVECTOR3 &This, const D3DXVECTOR3 &Target, const float &fSpeed);   // XZ(����)�̒Ǐ]
    
    // �W�F�C�\���̃t�@�C�����[�h
    static picojson::value JsonLoadFile(const string &FileName);

    // �W�F�C�\���̃f�[�^�󂯎��
    template <typename T> static void JsonGetState(
        picojson::value &v, const string &ObjName, const string &StateName, T &Data)
    {
        picojson::object& obj = v.get<picojson::object>();
        Data = (T)(obj[ObjName].get<picojson::object>()[StateName].get<double>());
    }

    // �W�F�C�\���փf�[�^�ݒ�
    template <typename T> static void JsonSetState(const string &FileName,
        const string &ObjName, const string &StateName, T &Data)
    {
        picojson::value& v = JsonLoadFile(FileName);
        picojson::object& obj = v.get<picojson::object>();
        obj[ObjName].get<picojson::object>()
            [StateName] = picojson::value(Data);

        std::ofstream ofs(FileName);
        ofs << picojson::value(obj).serialize(true) << endl;
        ofs.close();
    }

    // Imgui
    static HRESULT InitImgui(HWND hWnd);    // Imgui��������
    static void UninitImgui();              // Imgui�I��
    static void ShowDebugInfo();            // �f�o�b�O���\��
    static void CheckWireMode();            // ���C���[�t���[���m�F

private:
    static bool m_bWireFrame;       // ���C���[�t���[��
    static bool m_bLighting;        // ���C�e�B���O���邩
    static bool m_bDebugPlayer;     // �v���C���[�f�o�b�N
    static int m_Culling;           // �J�����O���
};

#endif