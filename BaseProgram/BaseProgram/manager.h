#ifndef _MANAGER_H_
#define _MANAGER_H_
//=============================================================================
//
// マネージャー処理 [manager.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GET_TEXTURE_PTR		(CManager::GetInstance()->GetResourceManager()->GetTextureClass())	// テクスチャのポインタ
#define GET_SOUND_PTR		(CManager::GetInstance()->GetResourceManager()->GetSoundClass())	// サウンドのポインタ
#define GET_XFILE_PTR		(CManager::GetInstance()->GetResourceManager()->GetXfileClass())	// Xファイルのポインタ
#define GET_RENDERER_DEVICE	(CManager::GetInstance()->GetRenderer()->GetDevice())				// デバイス取得

//=============================================================================
//前方宣言
//=============================================================================
class CRenderer;
class CInputKeyboard;
class CMouse;
class CFade;
class CInputJoypad;
class CScene;
class CResourceManager;
class CGame;
class CModeBase;
class CLight;
class CCamera;
class CPlayer;
class CPause;

//=============================================================================
//マネージャークラス
//=============================================================================
class CManager
{
public:
	//=========================================================================
	//列挙型定義
	//=========================================================================
	enum MODE_TYPE
	{
		MODE_TYPE_NONE = 0,
		MODE_TYPE_TITLE,			// タイトルモード
		MODE_TYPE_GAME,				// ゲームモード
		MODE_TYPE_PLAYER_EDITOR,	// プレイヤーのエディタ
		MODE_TYPE_MAX,
	};


	~CManager();	// デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);		// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理

	// Set関数

	void SetMode(MODE_TYPE mode);							// モードの設定

	// Get関数

	MODE_TYPE GetMode(void);															// モードの情報
	CModeBase *GetModePtr(void);														// ゲームの情報
	CRenderer *GetRenderer(void)				{ return m_pRenderer.get(); }			// レンダラー情報
	CInputKeyboard *GetKeyboard(void)			{ return m_pInput.get(); }				// キーボード情報
	CMouse *GetMouse(void)						{ return m_pInputMouse.get(); }			// マウス情報
	CFade *GetFade(void)						{ return m_pFade.get(); }				// フェード情報
	CInputJoypad *GetJoypad(void)				{ return m_pJoypad.get(); }				// ジョイパッドコントローラの情報
	CScene *GetScene(void)						{ return m_pScene.get(); }				// シーン情報
	CResourceManager *GetResourceManager(void)	{ return m_pResourceManager.get(); }	// リソースマネージャのポインタ
	CCamera *GetCamera(void)					{ return m_pCamera.get(); }				// カメラのポインタ
	CLight *GetLight(void)						{ return m_pLight.get(); }				// ライトのポインタ
	CPlayer *GetPlayer(void);															// プレイヤーの取得
	CPause *GetPause(void) { return m_pPause; }					// ポーズの取得処理
	static void SetActivePause(bool bPause) { m_bPause = bPause; }					// ポーズのセット
	static bool GetActivePause(void) { return m_bPause; }					// フェードの取得処理

	static CManager* GetInstance();		// インスタンス情報

private:
	// private関数
	void LoadAll(void);										// 全てのロード処理
	void UnLoadAll(void);									// 全てのアンロード処理

	// メンバ変数
	unique_ptr<CRenderer> m_pRenderer;					// レンダラークラスのポインタ
	unique_ptr<CInputKeyboard> m_pInput;				// インプットクラスのポインタ
	unique_ptr<CMouse> m_pInputMouse;					// マウスインプットクラスのポインタ
	unique_ptr<CFade> m_pFade;							// フェードクラスのポインタ
	unique_ptr<CInputJoypad> m_pJoypad;					// ジョイパッドコントローラのポインタ
	unique_ptr<CScene> m_pScene;						// シーンのポインタ
	unique_ptr<CResourceManager> m_pResourceManager;	// リソースマネージャのポインタ
	unique_ptr<CModeBase> m_pModeBase;					// モードのポインタ
	unique_ptr<CCamera> m_pCamera;						// カメラのポインタ
	unique_ptr<CLight> m_pLight;						// ライトのポインタ
	MODE_TYPE m_mode;									// モード
	CPause *m_pPause;									// ポーズ
	// シングルトン
	CManager();		// コンストラクタ
	static CManager* m_pManager;

	static bool m_bPause;									// ポーズフラグ
};

#endif