#pragma once
#include "gameObject.h"

// パーティクル用頂点レイアウト
struct VERTEX_3D_PARTICLE
{
    D3DXVECTOR3 Position;
    D3DXVECTOR2 TexCoord;
};
//今回使うパーティクルの資料例
struct ParticleCompute {
    // 座標
    D3DXVECTOR3 pos;
    // 速度
    D3DXVECTOR3 vel;
    // ライフ
    float life;
};

class Particle : public GameObject
{
private:
    // コンピュートシェーダー
    ID3D11ComputeShader* m_ComputeShader{};
    // パーティクル
    ParticleCompute* m_Particle;
    // バッファ
    ID3D11Buffer* m_VertexBuffer;
    ID3D11Buffer* m_ParticleBuffer;
    ID3D11Buffer* m_ResultBuffer;
    ID3D11Buffer* m_PositionBuffer;
    // SRV
    ID3D11ShaderResourceView* mpParticleSRV;
    ID3D11ShaderResourceView* mpPositionSRV;
    // UAV
    ID3D11UnorderedAccessView* mpResultUAV;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};



