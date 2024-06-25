//=============================================================================
//
// Tutrial���� [tutrial.cpp]
// Author : 
//
//=============================================================================
#include "tutrial.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WIDTH				(8000)			// (SCREEN_WIDTH)	// �w�i�T�C�Y
#define TEXTURE_HEIGHT				(1080)			// (SCREEN_HEIGHT)	// 
#define TEXTURE_MAX					(3)				// �e�N�X�`���̐�

#define TEXTURE_WIDTH_LOGO			(480)			// ���S�T�C�Y
#define TEXTURE_HEIGHT_LOGO			(80)			// 

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;		// ���_���
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char *g_TexturName[TEXTURE_MAX] = {
	"data/TEXTURE/map.png",
	"data/TEXTURE/sky000.jpg",
	"data/TEXTURE/sky001.jpg",
};


static BOOL	g_Load = FALSE;		// ���������s�������̃t���O
static Tutrial	g_Tutrial;



//=============================================================================
// ����������
//=============================================================================
HRESULT InitTutrial(void)
{
	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TexturName[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}


	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	// �ϐ��̏�����
	g_Tutrial.w     = TEXTURE_WIDTH;
	g_Tutrial.h     = TEXTURE_HEIGHT;
	g_Tutrial.pos   = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Tutrial.texNo = 0;

	g_Tutrial.scrl  = 0.0f;		// TEX�X�N���[��
	g_Tutrial.scrl2 = 0.0f;		// TEX�X�N���[��

	g_Load = TRUE;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTutrial(void)
{
	if (g_Load == FALSE) return;

	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Texture[i])
		{
			g_Texture[i]->Release();
			g_Texture[i] = NULL;
		}
	}

	g_Load = FALSE;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutrial(void)
{
	g_Tutrial.old_pos = g_Tutrial.pos;	// �P�t���O�̏���ۑ�


	//g_BG.scrl -= 0.0f;		// 0.005f;		// �X�N���[��


#ifdef _DEBUG	// �f�o�b�O����\������


#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutrial(void)
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	// �^�C�g���̔w�i��`��
	{
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_Tutrial.texNo]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteLTColor(g_VertexBuffer,
			0 - g_Tutrial.pos.x, 0 - g_Tutrial.pos.y, g_Tutrial.w, g_Tutrial.h,
			0.0f, 0.0f, 1.0f, 1.0f,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}


	// ���`��
	{
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		//float	tx = (g_BG.pos.x - g_BG.old_pos.x) * ((float)SCREEN_WIDTH / TEXTURE_WIDTH);
		//g_BG.scrl += tx * 0.001f;
		g_Tutrial.scrl += 0.001f;

		SetSpriteLTColor(g_VertexBuffer,
			0.0f, 0.0f, SCREEN_WIDTH, SKY_H,
			g_Tutrial.scrl, 0.0f, 1.0f, 1.0f,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}

	{
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[2]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		float	tx = (g_Tutrial.pos.x - g_Tutrial.old_pos.x) * ((float)SCREEN_WIDTH / TEXTURE_WIDTH);
		g_Tutrial.scrl2 += tx * 0.01f;
		//g_BG.scrl2 += 0.003f;

		SetSpriteLTColor(g_VertexBuffer,
			0.0f, SKY_H/2, SCREEN_WIDTH, SKY_H,
			g_Tutrial.scrl2, 0.0f, 1.0f, 1.0f,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}


}


//=============================================================================
// BG�\���̂̐擪�A�h���X���擾
//=============================================================================
Tutrial* GetBG(void)
{
	return &g_Tutrial;
}





