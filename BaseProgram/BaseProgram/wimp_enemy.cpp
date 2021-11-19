//=============================================================================
//
// サメクラス [wimp_enemy.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "wimp_enemy.h"
#include "manager.h"
#include "player.h"
#include "library.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PERCEPTION_DISTANCE (6000.0f)    // 感知できる距離
#define FOLLOW_TIME         (50)         // 重力がかからない時間
#define PLAYER_ADD_HEIGHT   (500.0f)       // プレイヤーを適当に量増し

//=============================================================================
// コンストラクタ
//=============================================================================
CWimpEnemy::CWimpEnemy(PRIORITY Priority) : CEnemy(Priority)
{
    isRush = false;
    m_nRushCount = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CWimpEnemy::~CWimpEnemy()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CWimpEnemy::Init()
{
    CEnemy::Init();
    SetGravityFlag(false);

    return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CWimpEnemy::Update()
{
    CEnemy::Update();
    if (isRush)
    {
        // 重力の切り替え
        GravitySwitch();
    }
}


//=============================================================================
// 突進
//=============================================================================
void CWimpEnemy::Rush()
{
    // 突進
    if (Follow())
    {
        isRush = true;
    }
}

//=============================================================================
// 重力をかける
//=============================================================================
void CWimpEnemy::GravitySwitch()
{
    m_nRushCount++;
    if (m_nRushCount >= FOLLOW_TIME)
    {
        m_nRushCount = 0;
        SetGravityFlag(true);
    }
}

//=============================================================================
// 追従
//=============================================================================
bool CWimpEnemy::Follow()
{
    // メモリ取得
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        D3DXVECTOR3 Ppos = pPlayer->GetPos();
        Ppos.y += PLAYER_ADD_HEIGHT;
        D3DXVECTOR3 Epos = GetPos();
        float fSpeed = GetSpeed();

        // 2点間のベクトルを求める（終点[目標地点] - 始点[自身の位置]）
        D3DXVECTOR3 Vector = Ppos - Epos;
        Vector = *D3DXVec3Normalize(&Vector, &Vector);
        Vector *= fSpeed;
        //自機を取得する
        float fAngle = atan2f((Epos.x - Ppos.x), (Epos.z - Ppos.z));    // 角度
        float fDistance = CLibrary::CalDistance(Ppos, Epos);
        if (fDistance <= PERCEPTION_DISTANCE)
        {
            // 透明な敵の移動
            D3DXVECTOR3 FollowMove = D3DXVECTOR3(
                (sinf(fAngle)*-fSpeed),
                0.0f, cosf(fAngle)*-fSpeed);

            // 移動量の設定
            SetMove(Vector);

            return true;
        }
    }

    return false;
}
