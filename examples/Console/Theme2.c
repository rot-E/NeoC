#include "NeoC/Base/Environment.h"
#include "NeoC/String.h"
#include "NeoC/SPEC/CC.h"
#include "NeoC/SPEC/SGR.h"
#include "NeoC/Console.h"
#include "NeoC/System.h"

void main() $_ {
	String_t *neoC = String.New(u8"NeoC");
	String_t *isA = String.New(u8" is a ");
	String_t *neo = String.New(u8"Neo ");
	String_t *CPEL = String.New(u8"C Programming Environment Library");
	String_t *exc = String.New(u8" !");

	Console.WriteLine(String.NewFormat(
		u8"%c%c%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
		CC.HT, CC.HT, SGR.SET.BOLD, SGR.TEXT.LIGHT_YELLOW,
		String.Unpack(neoC), SGR.RESET.BOLD, SGR.TEXT.YELLOW,
		String.Unpack(isA), SGR.SET.BOLD, SGR.SET.BLINK,
		SGR.TEXT.LIGHT_RED, String.Unpack(neo),SGR.RESET.BOLD,
		SGR.RESET.BLINK, SGR.SET.UNDERLINED, SGR.TEXT.GREEN,
		String.Unpack(CPEL), SGR.RESET.UNDERLINED, SGR.SET.BOLD,
		SGR.TEXT.LIGHT_CYAN, String.Unpack(exc), SGR.RESET.BOLD,
		SGR.TEXT.DEFAULT
	));

	String_t *text = String.NewFormat(
		u8"%s%s%s%s%s", String.Unpack(neoC), String.Unpack(isA),
		String.Unpack(neo), String.Unpack(CPEL), String.Unpack(exc)
	);

	Console.WriteChar(CC.HT); Console.WriteChar(CC.HT); Console.SetState(CSI.DECTCEM('l'));
	for (;;) {
		for (int32_t i = 0; i < String.GetLength(text); i++) {
			Console.WriteChar((String.GetCharAt(text, i) == 'm')? '^' : '.');
			System.USleep(30 * 1000);
		}

		for (int32_t i = String.GetLength(text) - 1; i >= 0; i--) {
			Console.WriteChar(CC.BS);
			Console.WriteChar((String.GetCharAt(text, i) != 'm')? '_' : '~');
			Console.WriteChar(CC.BS);
			System.USleep(30 * 1000);
		}
	}
} _$
