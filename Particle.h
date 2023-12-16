#pragma once
#include "gameObject.h"

// �p�[�e�B�N���p���_���C�A�E�g
struct VERTEX_3D_PARTICLE
{
    D3DXVECTOR3 Position;
    D3DXVECTOR2 TexCoord;
};
//����g���p�[�e�B�N���̎�����
struct ParticleCompute {
    // ���W
    D3DXVECTOR3 pos;
    // ���x
    D3DXVECTOR3 vel;
    // ���C�t
    float life;
};

class Particle : public GameObject
{
private:
    // �R���s���[�g�V�F�[�_�[
    ID3D11ComputeShader* m_ComputeShader{};
    // �p�[�e�B�N��
    ParticleCompute* m_Particle;
    // �o�b�t�@
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



