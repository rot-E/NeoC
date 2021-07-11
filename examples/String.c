#include "NeoC/Environment.h"
#include "NeoC/Exception.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"

void main() $_ {
	try {
		String_t *s = String.New(u8"test string");

		Console.WriteLine(String.NewFormat("s=\"%s\"   |s|=%d   s(0)='%c'   s(|s|-1)='%c'",
			String.Unpack(s),
			String.GetLength(s),
			String.GetCharAt(s, 0),
			String.GetLastChar(s)
		));

		Console.WriteLine(String.NewFormat("first index of 's': %d",
			String.FirstIndexOf(s, 's')
		));

		Console.WriteLine(String.NewFormat("last index of 's': %d",
			String.LastIndexOf(s, 's')
		));

		Console.WriteLine(String.NewFormat("\"%s\" is empty? %s", String.Unpack(s),
			(String.IsEmpty(s))? "YES" : "NO"
		));


		s = String.New("");
		Console.WriteLine(String.NewFormat("\"%s\" is empty? %s", String.Unpack(s),
			(String.IsEmpty(s))? "YES" : "NO"
		));


		s					= String.New("あいうえお aiueo");
		String_t *aiu		= String.New("あいう");
		String_t *ueo_latin	= String.New("ueo");

		Console.WriteLine(String.NewFormat("\"%s\" starts with \"%s\"? %s", String.Unpack(s), "あいう",
			( String.StartsWith(s, aiu) )? "YES" : "NO"
		));

		Console.WriteLine(String.NewFormat("\"%s\" starts with \"%s\"? %s", String.Unpack(s), "ueo",
			( String.StartsWith(s, ueo_latin) )? "YES" : "NO"
		));

		Console.WriteLine(String.NewFormat("\"%s\" ends with \"%s\"? %s", String.Unpack(s), "あいう",
			( String.EndsWith(s, aiu) )? "YES" : "NO"
		));

		Console.WriteLine(String.NewFormat("\"%s\" ends with \"%s\"? %s", String.Unpack(s), "ueo",
			( String.EndsWith(s, ueo_latin) )? "YES" : "NO"
		));


		String_t *aiueo	= String.New("あいうえお aiueo");

		Console.WriteLine(String.NewFormat("\"%s\" equals \"%s\"? %s", String.Unpack(s), String.Unpack(s),
			(String.Equals(s, s))? "YES" : "NO"
		));

		Console.WriteLine(String.NewFormat("\"%s\" equals \"%s\"? %s", String.Unpack(s), String.Unpack(aiueo),
			(String.Equals(s, aiueo))? "YES" : "NO"
		));


		aiueo = String.New("あいうえお aiueo ");
		Console.WriteLine(String.NewFormat("\"%s\" equals \"%s\"? %s", String.Unpack(s), String.Unpack(aiueo),
			(String.Equals(s, aiueo))? "YES" : "NO"
		));

		Console.WriteLine(String.NewFormat("\"%s\" equals \"%s\"? %s", String.Unpack(aiueo), String.Unpack(s),
			(String.Equals(aiueo, s))? "YES" : "NO"
		));

		s = String.New("aiueotttttX");
		Console.WriteLine(String.NewFormat("Original: %s", String.Unpack(s)));
		Console.WriteLine(String.NewFormat("DropLastChar: %s", String.Unpack(String.DropLastChar(s)) ));
		Console.WriteLine(String.NewFormat("Substring['0-2'3]: %s", String.Unpack(String.Substring(s, 0, 3)) ));
		Console.WriteLine(String.NewFormat("Substring[2'3-4'5]: %s", String.Unpack(String.Substring(s, 3, 5)) ));
		Console.WriteLine(String.NewFormat("t -> X: %s", String.Unpack(String.ReplaceWithChar(s, 't', 'X')) ));
		Console.WriteLine(String.NewFormat("s#s: %s", String.Unpack(String.Concat(s, s)) ));
		Console.WriteLine(String.NewFormat("s#kakikukeko: %s", String.Unpack(String.Concat(s, String.New("kakikukeko"))) ));

		s = String.NewN(100);
		Console.WriteLine(String.NewFormat("before: %s", String.Unpack(s)));
		strcpy(String.Unpack(s), "外部からの代入");
		String.Reduce(s);
		Console.WriteLine(String.NewFormat("after: %s", String.Unpack(s)));

		s = String.NewFormat("%d %d %s %c %f", 3, 2, "test test", 'z', 3.14);
		Console.WriteLine(String.NewFormat("%s", String.Unpack(s)));

		String.New(NULL); // chars[0] = '\0'

		Console.WriteLine(String.NewFormat("%s", String.Unpack(String.NewChar('t'))));

		throw (String.Failure);
	} catch (String.Failure) {
		Console.WriteErrorLine(String.New("String.Failure"));
	} catchN (String.Exception) {
		Console.WriteErrorLine(String.New("String.Exception"));
	} fin
} _$
