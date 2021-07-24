#pragma once

#include <stdint.h>

#include "NeoC/Annotation.h"
#include "NeoC/Object.h"

/** ASCII Control Chatacter
 *
 * cf. https://zariganitosh.hatenablog.jp/entry/20150209/ascii_code_secrets
 */

class _CC {
	public final uint8_t NUL; // 無
	public final uint8_t BEL; // 鐘
	public final uint8_t BS; // 一字後退
	public final uint8_t LF; // 改行
	public final uint8_t HT; // 水平タブ
	public final uint8_t VT; // 垂直タブ
	public final uint8_t FF; // 改ページ
	public final uint8_t CR; // 行頭復帰
	public final uint8_t ESC; // エスケープシーケンス開始
} _CC;

extern _CC CC;
