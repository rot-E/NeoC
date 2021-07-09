#include "NeoC/Exception.h"
#include "NeoC/String.h"

#include <stdio.h>

void main() {
	try {
		String_t *s = String.New("test string");

		printf("s=\"%s\"   |s|=%d   s(0)='%c'   s(|s|-1)='%c'\n",
			String.Unpack(s),
			String.GetLength(s),
			String.GetCharAt(s, 0),
			String.GetLastChar(s)
		);

		printf("first index of 's': %d\n",
			String.FirstIndexOf(s, 's')
		);

		printf("last index of 's': %d\n",
			String.LastIndexOf(s, 's')
		);

		printf("\"%s\" is empty? %s\n", String.Unpack(s),
			(String.IsEmpty(s))? "YES" : "NO"
		);
		String.Delete(s);


		s = String.New("");
		printf("\"%s\" is empty? %s\n", String.Unpack(s),
			(String.IsEmpty(s))? "YES" : "NO"
		);
		String.Delete(s);


		s					= String.New("あいうえお aiueo");
		String_t *aiu		= String.New("あいう");
		String_t *ueo_latin	= String.New("ueo");

		printf("\"%s\" starts with \"%s\"? %s\n", String.Unpack(s), "あいう",
			( String.StartsWith(s, aiu) )? "YES" : "NO"
		);
		printf("\"%s\" starts with \"%s\"? %s\n", String.Unpack(s), "ueo",
			( String.StartsWith(s, ueo_latin) )? "YES" : "NO"
		);
		printf("\"%s\" ends with \"%s\"? %s\n", String.Unpack(s), "あいう",
			( String.EndsWith(s, aiu) )? "YES" : "NO"
		);
		printf("\"%s\" ends with \"%s\"? %s\n", String.Unpack(s), "ueo",
			( String.EndsWith(s, ueo_latin) )? "YES" : "NO"
		);
		String.Delete(aiu);
		String.Delete(ueo_latin);


		String_t *aiueo		= String.New("あいうえお aiueo");
		printf("\"%s\" equals \"%s\"? %s\n", String.Unpack(s), String.Unpack(s),
			(String.Equals(s, s))? "YES" : "NO"
		);
		printf("\"%s\" equals \"%s\"? %s\n", String.Unpack(s), String.Unpack(aiueo),
			(String.Equals(s, aiueo))? "YES" : "NO"
		);
		aiueo				= String.New("あいうえお aiueo ");
		printf("\"%s\" equals \"%s\"? %s\n", String.Unpack(s), String.Unpack(aiueo),
			(String.Equals(s, aiueo))? "YES" : "NO"
		);
		aiueo				= String.New("あいうえお aiueo ");
		printf("\"%s\" equals \"%s\"? %s\n", String.Unpack(aiueo), String.Unpack(s),
			(String.Equals(aiueo, s))? "YES" : "NO"
		);

		String.Delete(s);
		s				= String.New("aiueotttttX");
		printf("Original: %s\n", String.Unpack(s));
		printf("DropLastChar: %s\n", String.Unpack(String.DropLastChar(s)) );
		printf("Substring['0-2'3]: %s\n", String.Unpack(String.Substring(s, 0, 3)) ); // マルチバイト/ワイド文字は使用不能
		printf("Substring[2'3-4'5]: %s\n", String.Unpack(String.Substring(s, 3, 5)) );
		printf("t -> X: %s\n", String.Unpack(String.ReplaceWithChar(s, 't', 'X')) );

		printf("s#s: %s\n", String.Unpack(String.Concat(s, s)) );
		printf("s#kakikukeko: %s\n", String.Unpack(String.Concat(s, String.New("kakikukeko"))) );

		String.Delete(s);
		s = String.NewN(100);
		printf("before: %s\n", String.Unpack(s));
		strcpy(String.Unpack(s), "外部からの代入");
		String.Reduce(s);
		printf("after: %s\n", String.Unpack(s));

		String.Delete(s);
		s = String.NewFormat("%d %d %s %c %f", 3, 2, "test test", 'z', 3.14);
		printf("%s\n", String.Unpack(s));

		String.New(NULL); // chars[0] = '\0'
	} catch (String.Exception) {
		printf("String.Exception\n");
	} catchN (String.RuntimeException) {
		printf("String.RuntimeException\n");
	} finally {
		printf("finally\n");
	} end
}
