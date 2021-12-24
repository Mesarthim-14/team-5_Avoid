//=============================================================================
//
// 水面反射のシェーダ [Reflect.fx]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// グローバル変数宣言
//=============================================================================
float4x4 m_WVPP;                 //ワールド行列 × ビュー × 遠近射影行列
float4x4 m_W;                    //ワールド行列のみ
float4 m_LightDir;
float4 m_Ambient;
float  m_Height;

float4x4 matWorld[4]: WORLD;		// ワールド変換行列配列

float4x4 matView : VIEW;            // ビュー変換行列
float4x4 matProj : PROJECTION;      // 射影変換行列
int iBlendNum;                      // ブレンドする配列の数

// オブジェクトのテクスチャー
sampler tex0 : register(s0);

//=============================================================================
// 構造体
//=============================================================================
struct VS_OUTPUT
{
	float4 Pos : POSITION;		// 自身
	float4 Col : COLOR0;		// 色
	float2 Tex : TEXCOORD0;		// テクスチャ座標
	float4 WPos : TEXCOORD1;	// ワールド座標
};

//=============================================================================
// 頂点シェーダ
//=============================================================================
VS_OUTPUT VS(float4 Pos : POSITION, float4 Normal: NORMAL, float2 Tex : TEXCOORD0)
{
	VS_OUTPUT Out;
	
	Out.Pos = mul( Pos, m_WVPP );	// ワールド変換
	Out.Tex = Tex;					// テクスチャ座標
	
	float3 Light = -m_LightDir.xyz;					// ライトの反転
	float3 NorLight = normalize(Normal.xyz);		// 正規化
	Out.Col = max(m_Ambient, dot(NorLight, Light));	// 色の設定
	Out.WPos = mul( Pos, m_W );						// ワールド行列のみ
	
	return Out;
}

//=============================================================================
// ピクセルシェーダ
//=============================================================================
float4 PS( VS_OUTPUT In ) : COLOR0
{
	// 変数宣言
	float4 Color;
	
	// 反射イメージのワールド座標形状での頂点の Y 座標がm_Height変数より高いとき描画しないようにする
	// これにより水面下のイメージのみレンダリングする
	clip( m_Height - In.WPos.y );	// clip(x) xが0以下になったらピクセルを破棄
	
	// 色情報をRGBに格納する
	Color.rgb = tex2D( tex0, In.Tex ).rgb * In.Col.rgb;
	Color.a = 1.0f;
	   
	return Color;
}

//=============================================================================
// 頂点シェーダ(スキンメッシュ)
//=============================================================================
VS_OUTPUT SkinmeshVS(float4 Pos : POSITION, float4 World : BLENDWEIGHT,
    float4 Normal : NORMAL, float2 Tex : TEXCOORD0)
{
    VS_OUTPUT Out;

    float4 P_after;							// 出力頂点座標
    float Weight[4] = (float[4])World;		// 重みをfloatに分割します
    float LastBlendWeight = 0.0f;			// 最後の行列に掛けられる重み
    float4x4 matCombWorld = 0.0f;			// 合成ワールド変換行列
    for (int nCount = 0; nCount < iBlendNum - 1; nCount++)
    {
        LastBlendWeight += Weight[nCount];		// 最後の重みをここで計算しておく
        matCombWorld += matWorld[nCount] * Weight[nCount];
    }

    // 最後の重みを足し算
    matCombWorld += matWorld[iBlendNum - 1] * (1.0f - LastBlendWeight);

    P_after = mul(Pos, matCombWorld);	// ワールド変換
    //Z値は遠近射影行列で取得する
    Out.WPos = mul(Pos, P_after);

    P_after = mul(P_after, matView);    // ビュー変換
    P_after = mul(P_after, matProj);    // 射影変換

    Out.Pos = P_after;
    Out.Tex = Tex;

    float3 Light = -m_LightDir.xyz;                 // ライトの反転
    float3 NorLight = normalize(Normal.xyz);        // 正規化
    Out.Col = max(m_Ambient, dot(NorLight, Light)); // 色の設定

    return Out;
}

//=============================================================================
// テクニック
//=============================================================================
technique TShader
{
	pass P0
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_2_0 PS();
	}
    pass P1
    {
        VertexShader = compile vs_1_1 SkinmeshVS();
        PixelShader = compile ps_2_0 PS();
    }

}