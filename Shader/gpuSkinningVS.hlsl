#include "common.hlsl"



void main(in VS_IN In, out PS_IN Out)
{
    
    //matrix SkinMatrix =
    //    BoneMatrix[In.BoneIndices[0]] * In.BoneWeights[0] +
    //    BoneMatrix[In.BoneIndices[1]] * In.BoneWeights[1] +
    //    BoneMatrix[In.BoneIndices[2]] * In.BoneWeights[2] +
    //    BoneMatrix[In.BoneIndices[3]] * In.BoneWeights[3];
    
    //float4 worldPos = mul(In.Position, SkinMatrix);
    //Out.Position = mul(worldPos, View); // ViewProjectionMatrix�͊O������n�����ׂ��ł��B
    
    //float4 worldNormal = mul(In.Normal, SkinMatrix);
    //Out.Normal = normalize(worldNormal);
    
    Out.TexCoord = In.TexCoord;
}
