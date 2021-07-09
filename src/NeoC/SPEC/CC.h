#pragma once

#include <stdint.h>

/** ASCII Control Chatacter
 *
 * cf. https://zariganitosh.hatenablog.jp/entry/20150209/ascii_code_secrets
 */

typedef struct {
	uint8_t NUL; // 無
	uint8_t BEL; // 鐘
	uint8_t BS; // 一字後退
	uint8_t LF; // 改行
	uint8_t HT; // 水平タブ
	uint8_t VT; // 垂直タブ
	uint8_t FF; // 改ページ
	uint8_t CR; // 行頭復帰
	uint8_t ESC; // エスケープシーケンス開始
} _CC;

extern _CC CC;
