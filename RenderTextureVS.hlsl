#include "RenderTexture.hlsli"

VSOutput main(float4 pos : POSITION, float2 uv : TEXCOORD)
{
	//VSOutput output;
	//output.svpos = pos;
	//output.uv = uv;
	//return output;

	VSOutput output; // �s�N�Z���V�F�[�_�[�ɓn���l
	output.svpos = mul(mat, pos); // ���W�ɍs�����Z
	output.uv = uv;
	return output;
}