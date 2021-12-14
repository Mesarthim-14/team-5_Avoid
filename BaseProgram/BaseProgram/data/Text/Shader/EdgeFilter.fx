//=============================================================================
//
// �G�b�W�V�F�[�_ [EdgeFillter1.fx]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
float2   m_Texel;                 //�P�e�N�Z���̃T�C�Y
float    m_Limit;                 //�G�b�W�ƂȂ邩�𔻒肷�邽�߂̊�l�B1.0f�ŃG�b�W�t�B���^�[�������ɂȂ�B

//=============================================================================
// �e�N�X�`�����
//=============================================================================
sampler tex0 : register(s0);      //�V�[���̃J���[�����i�[�����e�N�X�`���[
sampler tex1 : register(s1);      //�V�[����Z�l���i�[�����e�N�X�`���[

//=============================================================================
// �\����
//=============================================================================
struct VS_OUTPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
};

//=============================================================================
// ���_�V�F�[�_
//=============================================================================
VS_OUTPUT VS(float4 Pos : POSITION, float4 Col : COLOR0, float2 Tex : TEXCOORD0)
{
	VS_OUTPUT Out;
	
	Out.Pos = Pos;
	Out.Tex = Tex;
	
	return Out;
}

//=============================================================================
// �s�N�Z���V�F�[�_
//=============================================================================
float4 PS(VS_OUTPUT In) : COLOR0
{
	float4 Col = float4(0.0f, 0.0f, 0.0f, 1.0f);
	
	// �y�l���ŏ�������ł���e�N�X�`���[���Q�Ƃ��A���݂̃s�N�Z���ʒu�̂y�l���擾
	float Z1 = tex2D( tex1, In.Tex ).r;

	// ���ӂ̃s�N�Z���ʒu�̂y�l���擾
	float Z2 = tex2D(tex1, clamp( In.Tex + float2(  m_Texel.x,  m_Texel.y ), 0.0f, 1.0f ) ).r;
	float Z3 = tex2D(tex1, clamp( In.Tex + float2(  m_Texel.x, -m_Texel.y ), 0.0f, 1.0f ) ).r;
	float Z4 = tex2D(tex1, clamp( In.Tex + float2( -m_Texel.x,  m_Texel.y ), 0.0f, 1.0f ) ).r;
	float Z5 = tex2D(tex1, clamp( In.Tex + float2( -m_Texel.x, -m_Texel.y ), 0.0f, 1.0f ) ).r;

	// ���ӂ̃s�N�Z���ʒu�̂y�l�Ɣ�r���Am_Limit���傫���Ƃ��낪��������G�b�W�����Ɣ��肷��
	if (abs(Z1 - Z2) < m_Limit*0.1f &&
		abs(Z1 - Z3) < m_Limit*0.1f &&
		abs(Z1 - Z4) < m_Limit*0.1f &&
		abs(Z1 - Z5) < m_Limit*0.1f)
	{
		Col = tex2D(tex0, In.Tex);
	}
	
	return Col;
}

//=============================================================================
// �e�N�j�b�N
//=============================================================================
technique TShader
{
	pass P0
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_2_0 PS();
	}
}