//=============================================================================
//
// Tutrial処理 [tutrial.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"
#include "debugproc.h"
#include "sprite.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
struct Tutrial
{
	XMFLOAT3	pos;		// ポリゴンの座標
	float		w, h;		// 幅と高さ
	int			texNo;		// 使用しているテクスチャ番号

	float		scrl;		// スクロール
	XMFLOAT3	old_pos;	// １フレ前のポリゴンの座標
	float		scrl2;		// スクロール
};


#define	SKY_H	(150.0f)	// 空のポリゴンの高さ


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTutrial(void);
void UninitTutrial(void);
void UpdateTutrial(void);
void DrawTutrial(void);

Tutrial* GetTutrial(void);



