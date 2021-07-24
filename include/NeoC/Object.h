#pragma once

/* ------------------------------------------------------ */
// クラス定義
#define class typedef struct

// 継承
#define extends(SPRCLS) private SPRCLS _SPRCLS
#define inherit(SPRCLS) private SPRCLS _SPRCLS

#define act(T, VAR) ((T *)(VAR))

#define self void
#define this void

#define self_t void
#define this_t void

#define derived void
#define sub void
#define child void
/* ------------------------------------------------------ */
