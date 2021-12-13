//=============================================================================
//
// トゥーンシェーダ [ToonShader.fx]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// グローバル変数宣言
//=============================================================================
float4x4 m_WVP;						// ワールド × ビュー × 遠近射影
float4x4 m_pMtxWorld;				// マトリクスワールド
float4 m_LightDir;					// 平行光源の方向ベクトル
float2 m_Texel;						// １テクセルのサイズ
float m_Limit;						// エッジとなるかを判定するための基準値。1.0fでエッジフィルターが無効になる。
float4 m_EyePos;					// カメラの座標
float4 m_Diffuse;					// マテリアルの色

float4x4 matWorld[4]: WORLD;		// ワールド変換行列配列

float4x4 matView : VIEW;            // ビュー変換行列
float4x4 matProj : PROJECTION;      // 射影変換行列
int iBlendNum;                      // ブレンドする配列の数

//=============================================================================
// テクスチャ情報
//=============================================================================
sampler tex0 : register(s0);		// オブジェクトのテクスチャー/取得した色のテクスチャ
sampler tex1 : register(s1);		// トゥーンマップテクスチャー/Z値を参照し輪郭を出すためのテクスチャ

//=============================================================================
// 構造体
//=============================================================================
struct VS_OUTPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
	float3 Normal : TEXCOORD1;
	float4 Depth : TEXCOORD2;
};

//=============================================================================
// ピクセルシェーダーで出力する色情報
//=============================================================================
struct PS_OUTPUT
{
	float4 Col1 : COLOR0;   //シーンの色情報
	float4 Col2 : COLOR1;   //シーンのZ値情報
    float4 Canvas : COLOR2; // キャンバス用の情報
};

//=============================================================================
// 頂点シェーダ(スキンメッシュ)
//=============================================================================
VS_OUTPUT VS(float4 Pos : POSITION, float4 World : BLENDWEIGHT,
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
	matCombWorld += matWorld[iBlendNum-1] * (1.0f - LastBlendWeight);

	P_after = mul(Pos, matCombWorld);	// ワールド変換
	P_after = mul(P_after, matView);    // ビュー変換
	P_after = mul(P_after, matProj);    // 射影変換

	Out.Pos = P_after;
	Out.Tex = Tex;

	Out.Normal = normalize(Normal.xyz);
	//Z値は遠近射影行列で取得する
	Out.Depth = Out.Pos;

	return Out;
}

//=============================================================================
// ピクセルシェーダ
//=============================================================================
PS_OUTPUT PS(VS_OUTPUT In) : COLOR0
{
	float4 Out;
	PS_OUTPUT ps = (PS_OUTPUT)0;
	// ハーフランバート拡散照明によるライティング計算
	float p = dot(In.Normal, -m_LightDir.xyz);
	p = p * 0.5f + 0.5f;
	p = p * p;
	
    float canvas = dot(In.Normal, -m_LightDir.xyz);
    canvas = canvas * 1.0f + 0.6f;
    canvas = canvas * canvas;

	//****************************************************************
	// トゥーンシェーダー処理
	//****************************************************************
	//色情報をテクセルのＵ成分とし、トゥーンマップテクスチャーから光の反射率を取得する
	float4 Col = tex2D(tex1, float2(p, 0.0f));
	Out = Col * tex2D(tex0, In.Tex);
	//色情報をRGBに格納する
	ps.Col1 = Out * tex2D(tex0, In.Tex);

	//深度情報を格納する。
	//Z / W により 0 から 1 の間に正規化されたZ値情報に変換する。
	ps.Col2 = In.Depth.z / In.Depth.w;
	
    ps.Canvas = max((float4)0, canvas);
    ps.Canvas.a = 1.0f;

	return ps;
}

//=============================================================================
// ピクセルシェーダ(テクスチャ無し)
//=============================================================================
PS_OUTPUT ps_not_tex(VS_OUTPUT In) : COLOR0
{
    float4 Out;
    PS_OUTPUT ps = (PS_OUTPUT)0;
    // ハーフランバート拡散照明によるライティング計算
    float p = dot(In.Normal, -m_LightDir.xyz);
    p = p * 0.5f + 0.5f;
    p = p * p;
    
    float canvas = dot(In.Normal, -m_LightDir.xyz);
    canvas = canvas * 1.0f + 0.6f;
    canvas = canvas * canvas;
    
    //****************************************************************
    // トゥーンシェーダー処理
    //****************************************************************
    //色情報をテクセルのＵ成分とし、トゥーンマップテクスチャーから光の反射率を取得する
    float4 Col = tex2D(tex1, float2(p, 0.0f));
    Out = Col * m_Diffuse;

    //色情報をRGBに格納する
    ps.Col1 = Out * m_Diffuse;
    
    //深度情報を格納する。
    //Z / W により 0 から 1 の間に正規化されたZ値情報に変換する。
    ps.Col2 = In.Depth.z / In.Depth.w;
    
    ps.Canvas = max((float4)0, canvas);
    ps.Canvas.a = 1.0f;

    return ps;
}


//=============================================================================
// 構造体
//=============================================================================
struct EdgeVS_OUTPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
};

//=============================================================================
// 頂点シェーダ
//=============================================================================
EdgeVS_OUTPUT EdgeVS(float4 Pos : POSITION, 
	float4 Col : COLOR0, float2 Tex : TEXCOORD0)
{
	EdgeVS_OUTPUT Out;

	Out.Pos = Pos;
	Out.Tex = Tex;

	return Out;
}

//=============================================================================
// ピクセルシェーダ
//=============================================================================
float4 EdgePS(EdgeVS_OUTPUT In) : COLOR0
{
	float4 Col = float4(0.0f, 0.0f, 0.0f, 1.0f);

	// Ｚ値情報で書き込んであるテクスチャーを参照し、現在のピクセル位置のＺ値を取得
	float Z1 = tex2D(tex1, In.Tex).r;

	// 周辺のピクセル位置のＺ値を取得
	float Z2 = tex2D(tex1, clamp(In.Tex + float2(m_Texel.x,  m_Texel.y), 0.0f, 1.0f)).r;
	float Z3 = tex2D(tex1, clamp(In.Tex + float2(m_Texel.x, -m_Texel.y), 0.0f, 1.0f)).r;
	float Z4 = tex2D(tex1, clamp(In.Tex + float2(-m_Texel.x,  m_Texel.y), 0.0f, 1.0f)).r;
	float Z5 = tex2D(tex1, clamp(In.Tex + float2(-m_Texel.x, -m_Texel.y), 0.0f, 1.0f)).r;

	// 周辺のピクセル位置のＺ値と比較し、m_Limitより大きいところがあったらエッジ部分と判定する
	if (abs(Z1 - Z2) < m_Limit &&
		abs(Z1 - Z3) < m_Limit &&
		abs(Z1 - Z4) < m_Limit &&
		abs(Z1 - Z5) < m_Limit)
	{
		Col = tex2D(tex0, In.Tex);
	}

	return Col;
}

//=============================================================================
// 頂点シェーダ
//=============================================================================
VS_OUTPUT NormalVS(float4 Pos : POSITION,
    float4 Normal : NORMAL, float2 Tex : TEXCOORD0)
{
    VS_OUTPUT Out;

    Out.Pos = mul(Pos, m_WVP);
    Out.Tex = Tex;

    Out.Normal = normalize(Normal.xyz);

    //Z値は遠近射影行列で取得する
    Out.Depth = mul(Pos, m_WVP);

    return Out;
}

//=============================================================================
// テクニック
//=============================================================================
technique TShader
{
	// トゥーンシェーダ
	pass P0
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_2_0 PS();
	}

	// エッジシェーダ
	pass P1
	{
		VertexShader = compile vs_1_1 EdgeVS();
		PixelShader = compile ps_2_0 EdgePS();
	}
    // エッジシェーダ
    pass P2
    {
        VertexShader = compile vs_1_1 NormalVS();
        PixelShader = compile ps_2_0 PS();
    }
    // 
    pass P3
    {
        VertexShader = compile vs_1_1 VS();
        PixelShader = compile ps_2_0 ps_not_tex();

    }

}