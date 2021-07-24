#include "NeoC/Base/Environment.h"
#include "NeoC/Base/Exception/Signal.h"
#include "NeoC/Base/Exception/Exception.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"

void main() $_ {
	try {
		String_t *s = String.New(u8"test string");

		Console.WriteLine(String.NewFormat(u8"s=\"%s\"   |s|=%d   s(0)='%c'   s(|s|-1)='%c'",
			String.Unpack(s),
			String.GetLength(s),
			String.GetCharAt(s, 0),
			String.GetLastChar(s)
		));

		Console.WriteLine(String.NewFormat(u8"s=\"%s\"   |s|=%d   s(0)='%c'   s(|s|-1)='%c'",
			s->Unpack(s),
			s->GetLength(s),
			s->GetCharAt(s, 0),
			s->GetLastChar(s)
		));

		Console.WriteLine(String.NewFormat(u8"first index of 's': %d",
			String.FirstIndexOf(s, 's')
		));

		Console.WriteLine(String.NewFormat(u8"last index of 's': %d",
			String.LastIndexOf(s, 's')
		));

		Console.WriteLine(String.NewFormat(u8"\"%s\" is empty? %s", String.Unpack(s),
			(String.IsEmpty(s))? u8"YES" : u8"NO"
		));


		s = String.New(u8"");
		Console.WriteLine(String.NewFormat(u8"\"%s\" is empty? %s", String.Unpack(s),
			(String.IsEmpty(s))? u8"YES" : u8"NO"
		));


		s					= String.New(u8"あいうえお aiueo");
		String_t *aiu		= String.New(u8"あいう");
		String_t *ueo_latin	= String.New(u8"ueo");

		Console.WriteLine(String.NewFormat(u8"\"%s\" starts with \"%s\"? %s", String.Unpack(s), u8"あいう",
			( String.StartsWith(s, aiu) )? u8"YES" : u8"NO"
		));

		Console.WriteLine(String.NewFormat(u8"\"%s\" starts with \"%s\"? %s", String.Unpack(s), u8"ueo",
			( String.StartsWith(s, ueo_latin) )? u8"YES" : u8"NO"
		));

		Console.WriteLine(String.NewFormat(u8"\"%s\" ends with \"%s\"? %s", String.Unpack(s), u8"あいう",
			( String.EndsWith(s, aiu) )? u8"YES" : u8"NO"
		));

		Console.WriteLine(String.NewFormat(u8"\"%s\" ends with \"%s\"? %s", String.Unpack(s), u8"ueo",
			( String.EndsWith(s, ueo_latin) )? u8"YES" : u8"NO"
		));


		String_t *aiueo	= String.New(u8"あいうえお aiueo");

		Console.WriteLine(String.NewFormat(u8"\"%s\" equals \"%s\"? %s", String.Unpack(s), String.Unpack(s),
			(String.Equals(s, s))? u8"YES" : u8"NO"
		));

		Console.WriteLine(String.NewFormat(u8"\"%s\" equals \"%s\"? %s", String.Unpack(s), String.Unpack(aiueo),
			(String.Equals(s, aiueo))? u8"YES" : u8"NO"
		));


		aiueo = String.New(u8"あいうえお aiueo ");
		Console.WriteLine(String.NewFormat(u8"\"%s\" equals \"%s\"? %s", String.Unpack(s), String.Unpack(aiueo),
			(String.Equals(s, aiueo))? u8"YES" : u8"NO"
		));

		Console.WriteLine(String.NewFormat(u8"\"%s\" equals \"%s\"? %s", String.Unpack(aiueo), String.Unpack(s),
			(String.Equals(aiueo, s))? u8"YES" : u8"NO"
		));

		s = String.New(u8"aiueotttttX");
		Console.WriteLine(String.NewFormat(u8"Original: %s", String.Unpack(s)));
		Console.WriteLine(String.NewFormat(u8"DropLastChar: %s", String.Unpack(String.DropLastChar(s)) ));
		Console.WriteLine(String.NewFormat(u8"Substring['0-2'3]: %s", String.Unpack(String.Substring(s, 0, 3)) ));
		Console.WriteLine(String.NewFormat(u8"Substring[2'3-4'5]: %s", String.Unpack(String.Substring(s, 3, 5)) ));
		Console.WriteLine(String.NewFormat(u8"t -> X: %s", String.Unpack(String.ReplaceWithChar(s, 't', 'X')) ));
		Console.WriteLine(String.NewFormat(u8"s#s: %s", String.Unpack(String.Concat(s, s)) ));
		Console.WriteLine(String.NewFormat(u8"s#kakikukeko: %s", String.Unpack(String.Concat(s, String.New(u8"kakikukeko"))) ));

		s = String.NewN(100);
		Console.WriteLine(String.NewFormat(u8"before: %s", String.Unpack(s)));
		strcpy(String.Unpack(s), u8"外部からの代入");
		String.Reduce(s);
		Console.WriteLine(String.NewFormat(u8"after: %s", String.Unpack(s)));

		s = String.NewFormat(u8"%d %d %s %c %f", 3, 2, u8"test test", 'z', 3.14);
		Console.WriteLine(String.NewFormat(u8"%s", String.Unpack(s)));

		String.New(NULL); // chars[0] = '\0'

		Console.WriteLine(String.NewFormat(u8"%s", String.Unpack(String.NewChar('t'))));

		throw (Signal.New(String.Failure));
	} catch (String.Failure) {
		Console.WriteErrorLine(String.New(u8"String.Failure"));
	} catchN (String.Exception) {
		Console.WriteErrorLine(String.New(u8"String.Exception"));
	} fin
} _$
