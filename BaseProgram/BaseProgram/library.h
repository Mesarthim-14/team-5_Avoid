#ifndef _LIBRARY_H_
#define _LIBRARY_H_
//=============================================================================
//
// ライブラリ処理 [library.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "ImGui/Imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "json.h"

//=============================================================================
// 当たり判定クラス
//=============================================================================
class CLibrary
{
public:

    static string split(string str, char del, int nNum);                                                        // 文字列を分割し、取り出す関数
    static void ConfigMatrix(D3DXMATRIX *pMtx, D3DXVECTOR3 const &rPos, D3DXVECTOR3 const &rRot);               // マトリクスの設定
    static void RotFix(float &fRot);                                                                            // 角度の修正
    static void RotFixVector3(D3DXVECTOR3 &rot);                                                                // 角度の修正
    static int Random(const int &nNum);                                                                         // ランダム変数
    static int Random(const int &nMin, const int &nMax);                                                        // ランダム変数
    static float Random(const float &fNum);                                                                     // ランダム変数
    static float Random(const float &fMin, const float &fMax);                                                  // ランダム変数
    static void Rotate3D(D3DXVECTOR3 &PointPos, const D3DXVECTOR3 &rot);                                        // 点の三次元回転処理
    static float CalDistance(const D3DXVECTOR3 &pos1, const D3DXVECTOR3 &pos2);                                 // 二点の距離を計算
    static float LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0); // 分離軸に投影された軸成分から投影線分長を算出
    static D3DXVECTOR3 MultiplyVector3(const D3DXVECTOR3 &vector1, const D3DXVECTOR3 &vector2);                 // vector3同士の乗算
    static D3DXVECTOR3 DivisionVector3(const D3DXVECTOR3 &vector1, const D3DXVECTOR3 &vector2);                 // vector3同士の除算
    static float DivisionCheck(const float &num1, const float &num2);                                           // 0チェック有の除算(float型のみ)
    static BOOL KeyboardPress(const int &nKey);                                                                 // キーボードの押し込み判定
    static BOOL KeyboardTrigger(const int &nKey);                                                               // キーボードの押した判定
    static BOOL KeyboardRelease(const int &nKey);                                                               // キーボードの離した判定
    static float CalAngleXZ(const D3DXVECTOR3 &This, const D3DXVECTOR3 &Target);                                // XZ(平面)角度のを求める
    static D3DXVECTOR3 FollowMoveXZ(const D3DXVECTOR3 &This, const D3DXVECTOR3 &Target, const float &fSpeed);   // XZ(平面)の追従
    
    // ジェイソンのファイルロード
    static picojson::value JsonLoadFile(const string &FileName);

    // ジェイソンのデータ受け取り
    template <typename T> static void JsonGetState(
        picojson::value &v, const string &ObjName, const string &StateName, T &Data)
    {
        picojson::object& obj = v.get<picojson::object>();
        Data = (T)(obj[ObjName].get<picojson::object>()[StateName].get<double>());
    }

    // ジェイソンへデータ設定
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
    static HRESULT InitImgui(HWND hWnd);    // Imgui生成処理
    static void UninitImgui();              // Imgui終了
    static void ShowDebugInfo();            // デバッグ情報表示
    static void CheckWireMode();            // ワイヤーフレーム確認

private:
    static bool m_bWireFrame;       // ワイヤーフレーム
    static bool m_bLighting;        // ライティングするか
    static bool m_bDebugPlayer;     // プレイヤーデバック
    static int m_Culling;           // カリング情報
};

#endif