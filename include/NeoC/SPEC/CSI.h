#pragma once

#include <stdint.h>
#include "NeoC/Base/Object.h"
#include "NeoC/Base/Memory.h"
#include "NeoC/Base/Exception/Signal.h"
#include "NeoC/Base/Exception/Exception.h"
#include "NeoC/SPEC/CC.h"

/** ANSI Escape Sequence / Control Sequence Introducer
 *
 * cf. https://zariganitosh.hatenablog.jp/entry/20150224/escape_sequence
 * cf. https://qiita.com/PruneMazui/items/8a023347772620025ad6
 * cf. https://misc.flogisoft.com/bash/tip_colors_and_formatting
 * cf. https://en.wikipedia.org/wiki/ANSI_escape_code
 */

class _CSI {
	private void (* _Setup)();

	public final SignalCode_t Exception;

	private int32_t _ESCAPE_SEQUENCE_LEMGTH_MAX;

	/* カーソル移動 */
	public uint8_t *(* CUU)(const int32_t n); // n行上
	public uint8_t *(* CUD)(const int32_t n); // n行下
	public uint8_t *(* CUF)(const int32_t n); // n文字右
	public uint8_t *(* CUB)(const int32_t n); // n文字左
	public uint8_t *(* CNL)(const int32_t n); // n行下の行頭
	public uint8_t *(* CPL)(const int32_t n); // n行上の行頭
	public uint8_t *(* CHA)(const int32_t n); // n列
	public uint8_t *(* CUP)(const int32_t n, const int32_t m); // n行m列
	public uint8_t *(* CHT)(const int32_t n); // nタブ右
	public uint8_t *(* CBT)(const int32_t n); // nタブ左

	public uint8_t *(* ED)(const int32_t n) throws (CSI.Exception);
	public uint8_t *(* EL)(const int32_t n) throws (CSI.Exception);
	public uint8_t *(* ECH)(const int32_t n);
	public uint8_t *(* DCH)(const int32_t n);
	public uint8_t *(* IL)(const int32_t n);
	public uint8_t *(* DL)(const int32_t n);
	public uint8_t *(* TBC)(const int32_t n);
	public uint8_t *(* DECSTBM)(const int32_t n, const int32_t m);
	public uint8_t *(* SU)(const int32_t n);
	public uint8_t *(* SD)(const int32_t n);
	public uint8_t *(* REP)(const int32_t n);
	public uint8_t *(* DSR)(const int32_t n);
	public uint8_t *(* DECTCEM)(const uint8_t code);
	public uint8_t *(* GenerateSGR)(const int32_t code);
} _CSI;

extern _CSI CSI;
