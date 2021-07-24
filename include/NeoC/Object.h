#pragma once

/* ------------------------------------------------------ */
// クラス定義
#define class typedef struct

// 継承
#define extends(SPRCLS) private SPRCLS _SPRCLS
#define inherit(SPRCLS) private SPRCLS _SPRCLS

// 生成
#define new(T) (T *)(_Memory.Allocate(sizeof(T)))

// 消去
#define delete(VAR) _Memory.Free(VAR)

#define act(T, VAR) ((T *)(VAR))

#define self void
#define this void

#define self_t void
#define this_t void

#define derived void
#define sub void
#define child void
/* ------------------------------------------------------ */

#include "NeoC/Annotation.h"
#include "NeoC/Memory.h"
