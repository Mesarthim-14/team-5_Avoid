//=============================================================================
//
// �g�V�F�[�_ [wave.fx]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
float2 TexOffset;						// �P�e�N�Z�����㉺���E�ʒu�ւ̃I�t�Z�b�g�l
float  SpringPower;						// �΂ˋ��x�B�l��傫������Ɣg�̈ړ����x�������Ȃ�B0.5f
float2 AddWavePos;						// �ǉ�����g�̃e�N�Z���ʒu
float  AddWaveHeight;					// �ǉ�����g�̍���

//=============================================================================
// �e�N�X�`�����
//=============================================================================
sampler tex0 : register(s0);	// �g�}�b�v

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
VS_OUTPUT VS(float4 Pos : POSITION, float4 Color : COLOR0, float2 Tex : TEXCOORD0)
{
	VS_OUTPUT Out;

	Out.Pos = Pos;
	Out.Tex = Tex;

	return Out;
}

//=============================================================================
// �g�̍X�V����
//=============================================================================
float4 PS_WaveMap(VS_OUTPUT In) : COLOR0
{
	// �g�}�b�v���獂��( R���� )���A���x( G���� )���擾
	float4 Wave = tex2D(tex0, In.Tex);

	// ���͂̃e�N�Z���̍������擾
	float H1 = tex2D(tex0, In.Tex + float2(TexOffset.x, 0.0f)).r;
	float H2 = tex2D(tex0, In.Tex + float2(0.0f, TexOffset.y)).r;
	float H3 = tex2D(tex0, In.Tex + float2(-TexOffset.x, 0.0f)).r;
	float H4 = tex2D(tex0, In.Tex + float2(0.0f, -TexOffset.y)).r;

	//���x�̍X�V
	float V = ((H1 + H2 + H3 + H4) * 0.2f - Wave.r) * SpringPower + Wave.g;	// ���݂̑��x�����Z�B���͂̃e�N�Z���̍����Ǝ����̍����̍����v�Z����B���̒l�����x�ƂȂ�B0.25����

	//�����̍X�V
	float H = Wave.r + V;	//�v�Z�������x�����Z�B���݂̍����B

	//�V�K�ɔg��ǉ�
	if (distance(In.Tex, AddWavePos) < 0.003f)	// 0.005	�g�̑傫��
	{
		H += 0.5f;
		//V += 0.2f;
		V += AddWaveHeight;
	}

	// �g�̍��������X�� 0.0f �ʒu�Ɉړ�����悤�ɕ␳����B
	// �V�K�ɔg��ǉ����Ȃ��ꍇ�A���X�ɕ��R�ɂȂ�B
//	H = H - H * 0.004f;				// 0.005f

	return float4(H, V, 1.0f, 1.0f);
}

//=============================================================================
// �@���}�b�v�쐬
//=============================================================================
float4 PS_BumpMap(VS_OUTPUT In) : COLOR0
{
	float4 Out;

	// �㉺���E�̃e�N�Z���ʒu�̍������擾����
	float H1 = tex2D(tex0, In.Tex + float2(TexOffset.x, 0.0f)).r;
	float H2 = tex2D(tex0, In.Tex + float2(0.0f, TexOffset.y)).r;
	float H3 = tex2D(tex0, In.Tex + float2(-TexOffset.x, 0.0f)).r;
	float H4 = tex2D(tex0, In.Tex + float2(0.0f, -TexOffset.y)).r;
	
	// X �����̍����̕ω��ʂ��v�Z����
	// �g�̍������� -1.0f �` 1.0f �͈̔͂Ŋi�[����Ă���̂� 0.0f �` 1.0f �ɕϊ�����
	float tu = 0.5f * (H3 - H1) + 0.5f;
	
	// Y �����̍����̕ω��ʂ��v�Z����
	// �g�̍������� -1.0f �` 1.0f �͈̔͂Ŋi�[����Ă���̂� 0.0f �` 1.0f �ɕϊ�����
	float tv = 0.5f * (H4 - H2) + 0.5f;
	
	// �����}�b�s���O�͍��������g�p����B���̂��߃������ɍ��������i�[����
	Out = float4(tu, tv, 1.0f , tex2D(tex0, In.Tex).r * 0.9f + 0.5f); // tex2D(tex0, In.Tex).r * 0.5f + 0.5f
	
	return Out;
}

//=============================================================================
// �e�N�j�b�N
//=============================================================================
technique TShader
{
	pass P0
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_2_0 PS_WaveMap();
	}

	pass P1
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_2_0 PS_BumpMap();
	}
}