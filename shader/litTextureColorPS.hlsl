
#include "common.hlsl"


Texture2D		g_Texture : register(t0);
SamplerState	g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{

	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	if (outDiffuse.a < 0.01f)
	{

		float3 monochro;

		monochro.r = 0.21f * outDiffuse.r;
		monochro.g = 0.72f * outDiffuse.g;
		monochro.b = 0.07f * outDiffuse.b;

		float3 color1 = In.Diffuse;
		float3 color2 = float3(0.0f, 0.0f, 1.0f);

		color1 *= monochro;
		color2 *= (1.0f - monochro);


	}
	else { discard; }

}
