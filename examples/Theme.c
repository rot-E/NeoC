#include "NeoC/String.h"
#include "NeoC/CC.h"
#include "NeoC/CSI.h"
#include "NeoC/SGR.h"
#include "NeoC/Console.h"
#include "NeoC/Exception.h"
#include "NeoC/System.h"

void main() $NeoC {
	String_t *neoC = String.New("NeoC");
	String_t *isA = String.New(" is a ");
	String_t *neo = String.New("Neo ");
	String_t *CPEL = String.New("C Programming Environment Library");
	String_t *exc = String.New(" !");

	Console.WriteLine(String.NewFormat(
		"%c%c%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
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
		"%s%s%s%s%s", String.Unpack(neoC), String.Unpack(isA),
		String.Unpack(neo), String.Unpack(CPEL), String.Unpack(exc)
	);

	Console.WriteChar(CC.HT); Console.WriteChar(CC.HT);
	for (;;) {
		for (int32_t i = 0; i < String.GetLength(text); i++) {
			Console.WriteChar((String.GetCharAt(text, i) == 'm')? '^' : '.');
			System.USleep(30 * 1000);
		}

		for (int32_t i = String.GetLength(text); i > 0; i--) {
			Console.WriteChar(CC.BS);
			Console.WriteChar((String.GetCharAt(text, i + 1) != 'm')? '^' : '.');
			Console.WriteChar(CC.BS);
			System.USleep(30 * 1000);
		}
	}
} NeoC$
