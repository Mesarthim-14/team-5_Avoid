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
	static string split(string str, char del, int nNum);											// 文字列を分割し、取り出す関数
	static void ConfigMatrix(D3DXMATRIX *pMtx, D3DXVECTOR3 const &rPos, D3DXVECTOR3 const &rRot);	// マトリクスの設定
	static void RotFix(float &fRot);																// 角度の修正
	static void RotFixVector3(D3DXVECTOR3 &rot);													// 角度の修正
	static int Random(const int nNum);																// ランダム変数
	static int Random(const int nMin, const int nMax);												// ランダム変数
	static float Random(const float fNum);															// ランダム変数
	static float Random(const float fMin, const float fMax);										// ランダム変数
	static float DistanceCal(const D3DXVECTOR3 &pos1, const D3DXVECTOR3 &pos2);						// 二点の距離を計算
	static BOOL KeyboardPress(const int &nKey);														// キーボードの押し込み判定
	static BOOL KeyboardTrigger(const int &nKey);													// キーボードの押した判定
	static BOOL KeyboardRelease(const int &nKey);													// キーボードの離した判定

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
	static HRESULT InitImgui(HWND hWnd);	//Imgui生成処理
	static void UninitImgui(void);			//Imgui終了
	static void ShowDebugInfo(void);		//デバッグ情報表示
	static void CheckWireMode(void);		//ワイヤーフレーム確認

private:
	static bool m_bWireFrame;		// ワイヤーフレーム
	static bool m_bLighting;		//ライティングするか
	static bool m_bDebugPlayer;		//プレイヤーデバック
	static int m_Culling;			//カリング情報
};

#endif