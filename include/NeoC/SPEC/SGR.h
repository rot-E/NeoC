#pragma once

#include <stdint.h>

#include "NeoC/Base/Object.h"
#include "NeoC/SPEC/CSI.h"

/** ANSI Escape Sequence / Select Graphic Rendition
 *
 * cf. https://zariganitosh.hatenablog.jp/entry/20150224/escape_sequence
 * cf. https://qiita.com/PruneMazui/items/8a023347772620025ad6
 * cf. https://misc.flogisoft.com/bash/tip_colors_and_formatting
 * cf. https://en.wikipedia.org/wiki/ANSI_escape_code
 */

class _SGR {
	private void (* _Setup)();

	public struct {
		public final uint8_t *BOLD;
		public final uint8_t *DIM;
		public final uint8_t *UNDERLINED;
		public final uint8_t *BLINK;
		public final uint8_t *REVERSE;
		public final uint8_t *HIDDEN;
	} SET;

	public struct {
		public final uint8_t *ALL;
		public final uint8_t *BOLD;
		public final uint8_t *DIM;
		public final uint8_t *UNDERLINED;
		public final uint8_t *BLINK;
		public final uint8_t *REVERSE;
		public final uint8_t *HIDDEN;
	} RESET;

	public struct {
		public final uint8_t *DEFAULT;
		public final uint8_t *BLACK;
		public final uint8_t *RED;
		public final uint8_t *GREEN;
		public final uint8_t *YELLOW;
		public final uint8_t *BLUE;
		public final uint8_t *MAGENTA;
		public final uint8_t *CYAN;
		public final uint8_t *LIGHT_GRAY;
		public final uint8_t *DARK_GRAY;
		public final uint8_t *LIGHT_RED;
		public final uint8_t *LIGHT_GREEN;
		public final uint8_t *LIGHT_YELLOW;
		public final uint8_t *LIGHT_BLUE;
		public final uint8_t *LIGHT_MAGENTA;
		public final uint8_t *LIGHT_CYAN;
		public final uint8_t *WHITE;
	} TEXT;

	public struct {
		public final uint8_t *DEFAULT;
		public final uint8_t *BLACK;
		public final uint8_t *RED;
		public final uint8_t *GREEN;
		public final uint8_t *YELLOW;
		public final uint8_t *BLUE;
		public final uint8_t *MAGENTA;
		public final uint8_t *CYAN;
		public final uint8_t *LIGHT_GRAY;
		public final uint8_t *DARK_GRAY;
		public final uint8_t *LIGHT_RED;
		public final uint8_t *LIGHT_GREEN;
		public final uint8_t *LIGHT_YELLOW;
		public final uint8_t *LIGHT_BLUE;
		public final uint8_t *LIGHT_MAGENTA;
		public final uint8_t *LIGHT_CYAN;
		public final uint8_t *WHITE;
	} BACKGROUND;
} _SGR;

extern _SGR SGR;
