//=============================================================================
//
// ライブラリ処理 [library.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "library.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "json.h"
#include "keyboard.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
bool CLibrary::m_bWireFrame = false;
bool CLibrary::m_bLighting = true;
bool CLibrary::m_bDebugPlayer = false;
int CLibrary::m_Culling = false;

//=============================================================================
// 文字列を分割し、取り出すクラス
//=============================================================================
string CLibrary::split(const string str, const char del, const int nNum)
{
    // ローカル変数宣言
    int first = 0;                          // 何番目の文字か
    int last = str.find_first_of(del);      // 指定の文字までの数
    int t_last = str.find_first_of('\t');   // タブまでの文字数
    int nCount = 0;                         // 文字列のカウント
    int nCount_t = 0;                       // タブのカウント
    string result;                          // 返す文字列

    // 変数strの文字列数まで
    while (first < (int)str.size())
    {
        if (last == -1 && t_last == 0)
        {
            int nCount_t = 0;
            
            while (str.find_first_of('\t', nCount_t) == 0)
            {
                // \tのカウント
                nCount_t++;

            }
            // 指定の番号から取得
            string subStr(str, first + nCount_t, str.size());

            // 指定された分割数のとき
            if (nCount == nNum)
            {
                // 文字列を返す
                result = subStr;
                break;
            }
        }
        else if (t_last == 0)
        {
            int nNum = t_last;

            while (nNum == 0)
            {
                // \tのカウント
                nCount_t++;
                nNum = str.find_first_of('\t', nCount_t-1);        // タブまでの文字数
            }
            first += nCount_t;
        }

        // 距離の比較
        if (last < t_last)
        {
            // 指定の番号から取得
            string subStr(str, first, last - first);
            // 指定された分割数のとき
            if (nCount == nNum)
            {
                // 文字列を返す
                result = subStr;
                break;
            }

            // 指定の文字数分
            first = last + 1;
        }
        else
        {
            // 指定の番号から取得
            string subStr(str, first, t_last - first);
            // 指定された分割数のとき
            if (nCount == nNum)
            {
                // 文字列を返す
                result = subStr;
                break;
            }

            // タブ分文字数を進める
            first = t_last + 1;
        }

        // 距離の取得
        last = str.find_first_of(del, first);       // 指定の文字数までの数
        t_last = str.find_first_of('\t', first);    // タブまでの文字数

        // 距離の比較
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

        // 回数のカウント
        nCount++;
    }

    return result;
}

//=============================================================================
// マトリクスの設定
//=============================================================================
void CLibrary::ConfigMatrix(D3DXMATRIX* pMtx, D3DXVECTOR3 const &rPos, D3DXVECTOR3 const &rRot)
{
    D3DXMATRIX mtxRot, mtxTrans;

    //ワールドマトリックスの初期化
    D3DXMatrixIdentity(pMtx);

    // 回転を反映
    D3DXMatrixRotationYawPitchRoll(&mtxRot, rRot.y, rRot.x, rRot.z);
    D3DXMatrixMultiply(pMtx, pMtx, &mtxRot);

    // 位置を反映
    D3DXMatrixTranslation(&mtxTrans, rPos.x, rPos.y, rPos.z);
    D3DXMatrixMultiply(pMtx, pMtx, &mtxTrans);
}

//=============================================================================
// 角度の修正
//=============================================================================
void CLibrary::RotFix(float &fRot)
{
    //差分が3.14を以上の時
    if (fRot > D3DX_PI)
    {
        //6.28引く
        fRot -= D3DX_PI * 2;
    }
    //差分が-3.14以下の時
    if (fRot < -D3DX_PI)
    {
        //6.28加算
        fRot += D3DX_PI * 2;
    }
}

//=============================================================================
// 角度の修正
//=============================================================================
void CLibrary::RotFixVector3(D3DXVECTOR3 & rot)
{
    CLibrary::RotFix(rot.x);
    CLibrary::RotFix(rot.y);
    CLibrary::RotFix(rot.z);
}

//=============================================================================
// ランダムの値を返す (指定した+-の範囲を出力)
//=============================================================================
int CLibrary::Random(const int &nNum)
{
    random_device rnd;
    mt19937 mt(rnd());
    uniform_int_distribution<> rand(-nNum, nNum);

    return rand(mt);
}

//=============================================================================
// ランダムの値を返す (指定した二つの範囲を出力)
//=============================================================================
int CLibrary::Random(const int &nMin, const int &nMax)
{
    random_device rnd;
    mt19937 mt(rnd());
    uniform_int_distribution<> rand(nMin, nMax);

    return rand(mt);
}

//=============================================================================
// ランダムの値を返す (指定した+-の範囲を出力)
//=============================================================================
float CLibrary::Random(const float &fNum)
{
    random_device rnd;
    mt19937 mt(rnd());
    uniform_real_distribution<> rand(-fNum, fNum);

    return (float)rand(mt);
}

//=============================================================================
// ランダムの値を返す (指定した二つの範囲を出力)
//=============================================================================
float CLibrary::Random(const float &fMin, const float &fMax)
{
    random_device rnd;
    mt19937 mt(rnd());
    uniform_real_distribution<> rand(fMin, fMax);

    return (float)rand(mt);
}

//*****************************************************************************
// 点の三次元回転処理
//*****************************************************************************
void CLibrary::Rotate3D(D3DXVECTOR3 &PointPos, const D3DXVECTOR3 &rot)
{
    //X軸回転
    PointPos = D3DXVECTOR3(
        PointPos.x,
        PointPos.y * cosf(rot.x) + PointPos.z * -sinf(rot.x),
        PointPos.y * sinf(rot.x) + PointPos.z * cosf(rot.x));

    //Y軸回転
    PointPos = D3DXVECTOR3(
        PointPos.x * cosf(rot.y) + PointPos.z * sinf(rot.y),
        PointPos.y,
        PointPos.x * -sinf(rot.y) + PointPos.z * cosf(rot.y));

    //Z軸回転
    PointPos = D3DXVECTOR3(
        PointPos.x * cosf(rot.z) + PointPos.y * -sinf(rot.z),
        PointPos.x * sinf(rot.z) + PointPos.y * cosf(rot.z),
        PointPos.z);
}

//*****************************************************************************
// 分離軸に投影された軸成分から投影線分長を算出
//*****************************************************************************
float CLibrary::LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3)
{
    // 3つの内積の絶対値の和で投影線分長を計算
    // 分離軸Sepは標準化されていること
    float r1 = (float)fabs(D3DXVec3Dot(Sep, e1));
    float r2 = (float)fabs(D3DXVec3Dot(Sep, e2));
    float r3 = (float)(e3 ? (fabs(D3DXVec3Dot(Sep, e3))) : 0);
    return r1 + r2 + r3;
}

//*****************************************************************************
// vector3同士の乗算
//*****************************************************************************
D3DXVECTOR3 CLibrary::MultiplyVector3(const D3DXVECTOR3 &vector1, const D3DXVECTOR3 &vector2)
{
    return D3DXVECTOR3(vector1.x * vector2.x, vector1.y * vector2.y, vector1.z * vector2.z);
}

//*****************************************************************************
// vector3同士の除算
//*****************************************************************************
D3DXVECTOR3 CLibrary::DivisionVector3(const D3DXVECTOR3 & vector1, const D3DXVECTOR3 & vector2)
{
    return D3DXVECTOR3(DivisionCheck(vector1.x, vector2.x), DivisionCheck(vector1.y, vector2.y), DivisionCheck(vector1.z, vector2.z));
}

//*****************************************************************************
// 0チェック有の除算(float型のみ)
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
// 二点の距離を計算
//=============================================================================
float CLibrary::CalDistance(const D3DXVECTOR3 & pos1, const D3DXVECTOR3 & pos2)
{
    return D3DXVec3Length(&(pos1 - pos2));
}

//=============================================================================
// キーボードの押し込み判定
//=============================================================================
BOOL CLibrary::KeyboardPress(const int &nKey)
{
    CInputKeyboard *pKeyboard = CManager::GetInstance()->GetKeyboard();
    return pKeyboard->GetPress(nKey);
}

//=============================================================================
// キーボードの押した判定
//=============================================================================
BOOL CLibrary::KeyboardTrigger(const int &nKey)
{
    CInputKeyboard *pKeyboard = CManager::GetInstance()->GetKeyboard();
    return pKeyboard->GetTrigger(nKey);
}

//=============================================================================
// キーボードの離した判定
//=============================================================================
BOOL CLibrary::KeyboardRelease(const int &nKey)
{
    CInputKeyboard *pKeyboard = CManager::GetInstance()->GetKeyboard();
    return pKeyboard->GetRelease(nKey);
}

//=============================================================================
// XZ(平面)の角度を求める
//=============================================================================
float CLibrary::CalAngleXZ(const D3DXVECTOR3 & This, const D3DXVECTOR3 & Target)
{
    return atan2f((This.x - Target.x), (This.z - Target.z));
}

//=============================================================================
// XZ(平面)の追従
//=============================================================================
D3DXVECTOR3 CLibrary::FollowMoveXZ(const D3DXVECTOR3 &This, const D3DXVECTOR3 &Target, const float &fSpeed)
{
    float fAngle = CLibrary::CalAngleXZ(This, Target);    // 角度を決める

    return D3DXVECTOR3(sinf(fAngle)*-fSpeed, 0.0f, cosf(fAngle)*-fSpeed);
}

//=============================================================================
// ワールド座標からスクリーン座標に変換
//=============================================================================
D3DXVECTOR3 CLibrary::ConvWorldToScreen(const D3DXVECTOR3& pos, const D3DXMATRIX& mtxView, const D3DXMATRIX& mtxProj)
{
    D3DXVECTOR3 WorldPos = ZeroVector3;
    D3DXMATRIX mtxScreen =
    {
        SCREEN_WIDTH*0.5f, 0, 0, 0,
        0, -SCREEN_HEIGHT*0.5f, 0, 0,
        0, 0, 1, 0,
        SCREEN_WIDTH*0.5f, SCREEN_HEIGHT*0.5f, 0, 1
    };//スクリーン座標行列

    //ビュー座標からプロジェクション、プロジェクションからスクリーン座標に変換
    D3DXVec3TransformCoord(&WorldPos, &pos, &mtxView);
    D3DXVec3TransformCoord(&WorldPos, &WorldPos, &mtxProj);
    D3DXVec3TransformCoord(&WorldPos, &WorldPos, &mtxScreen);

    return WorldPos;
}

//=============================================================================
// jsonのファイルロード
//=============================================================================
picojson::value CLibrary::JsonLoadFile(const string &FileName)
{
    // JSONデータの読み込み。
    ifstream ifs(FileName, ios::in);
    if (ifs.fail())
    {
        cerr << "failed to jsonfile" << endl;
    }
    const string json((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
    // JSONデータを解析する。
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
// Imguiの生成
//=============================================================================
HRESULT CLibrary::InitImgui(HWND hWnd)
{
    //ゲームパッドとキーボードの情報取得
    //所有権は貰ってないから開放の必要はない
    CInputKeyboard *pKeyboard = CManager::GetInstance()->GetKeyboard();

    //NULLチェック
    if (!pKeyboard)
    {
        return E_FAIL;
    }

    //create
    IMGUI_CHECKVERSION();

    //生成
    ImGui::CreateContext();

    //デフォルトカラー設定
    ImGui::StyleColorsDark();

    //初期化
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX9_Init(CManager::GetInstance()->GetRenderer()->GetDevice());

    return S_OK;
}

//=============================================================================
// Imguiの終了処理
//=============================================================================
void CLibrary::UninitImgui()
{
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

//=============================================================================
// Imgui デバッグ情報表示
//=============================================================================
void CLibrary::ShowDebugInfo()
{
#ifdef _DEBUG

    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    //開始
    if (ImGui::CollapsingHeader("Debug"))
    {
        //FPS情報
        if (ImGui::TreeNode("FPS"))
        {
            //FPS
            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::TreePop();
        }

        //情報
        if (ImGui::TreeNode("DebugCommand"))
        {
            //ワイヤーフレーム
            if (ImGui::Checkbox("WireFrame", &m_bWireFrame))
            {
                CheckWireMode();
            }

            //ライティング
            if (ImGui::Checkbox("Lighting", &m_bLighting))
            {
                pDevice->SetRenderState(D3DRS_LIGHTING, m_bLighting);        // ライティングモード切り替え
            }
            //プレイヤーデバッグ
            if (ImGui::Checkbox("DebugPlayer", &m_bDebugPlayer))
            {

            }
            ImGui::TreePop();
        }
    }

#endif //DEBUG
}

//=============================================================================
//ワイヤーフレームかどうか確認
//Imguiのウィンドウだけワイヤーフレームにならない為に必要
//=============================================================================
void CLibrary::CheckWireMode()
{
    //デバイス取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    //trueかfalseかで決める
    m_bWireFrame ?
        pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME) :
        pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}