//=============================================================================
//
// Tutrial���� [tutrial.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"
#include "debugproc.h"
#include "sprite.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
struct Tutrial
{
	XMFLOAT3	pos;		// �|���S���̍��W
	float		w, h;		// ���ƍ���
	int			texNo;		// �g�p���Ă���e�N�X�`���ԍ�

	float		scrl;		// �X�N���[��
	XMFLOAT3	old_pos;	// �P�t���O�̃|���S���̍��W
	float		scrl2;		// �X�N���[��
};


#define	SKY_H	(150.0f)	// ��̃|���S���̍���


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTutrial(void);
void UninitTutrial(void);
void UpdateTutrial(void);
void DrawTutrial(void);

Tutrial* GetTutrial(void);



