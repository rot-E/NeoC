#pragma once

/* ------------------------------------------------------ */
/* header */
// クラス定義
#define class typedef struct

// 継承
#define extends(SPRCLS) private SPRCLS _SPRCLS
#define inherit(SPRCLS) private SPRCLS _SPRCLS

// 函数・値注釈
#define private			// 非公開
#define protected		// 公開・変更非推奨
#define public			// 公開
#define undefined		// 未定義
#define library			// ライブラリ専用

// 値注釈
#define final			// 変更不能

// インスタンスメソッド第一引数の型
#define self void
#define this void

#define self_t void
#define this_t void

#define derived void
#define sub void
#define child void


/* source */
// メソッド注釈
#define method

// 生成
#define new(T) (T *)(_Memory.Allocate(sizeof(T)))

// 消去
#define delete(VAR) _Memory.Free(VAR)

// キャスト(基底<>派生クラス)
#define act(T, VAR) ((T *)(VAR))
/* ------------------------------------------------------ */

#include <stdint.h>
#include "NeoC/Base/Memory.h"

class Object_t {
	private uint8_t *_Expr;

	public uint8_t *(* GetExpr)(self *);
} Object_t;

class _Object {
	public Object_t *(* Init)(Object_t *);
	public Object_t *(* New)();
	public void (* Delete)(Object_t *);

	public uint8_t *(* GetExpr)(self_t *);
} _Object;

extern _Object Object;
