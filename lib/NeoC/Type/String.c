#include "NeoC/Type/String.h"

method static void _Setup() {
	String.Exception signal;
	String.Failure signal;

	String.GetExpr = Object.GetExpr;
}

method static uint8_t *Unpack(self_t *str) {
	return act(String_t, str)->_String;
}

method static int32_t GetLength(self_t *str) {
	return strlen(act(String_t, str)->_String);
}

method static uint8_t GetCharAt(self_t *str, const int32_t index) throws (String.Exception) {
	if (String.GetLength(str) < index) throw (Signal.New(String.Exception));

	return String.Unpack(str)[index];
}

method static uint8_t GetHeadChar(self_t *str) throws (String.Exception) {
	if (String.GetLength(str) < 1) throw (Signal.New(String.Exception));

	return String.GetCharAt(str, 0);
}

method static uint8_t GetLastChar(self_t *str) throws (String.Exception) {
	if (String.GetLength(str) < 1) throw (Signal.New(String.Exception));

	return String.GetCharAt(str, String.GetLength(str) - 1);
}

method static int32_t FirstIndexOf(self_t *str, const uint8_t ch) throws (String.Exception, String.Failure) {
	for (int32_t i = 0; i < String.GetLength(str); i++)
		if (String.GetCharAt(str, i) == ch) return i;

	throw (Signal.New(String.Failure));
}

method static int32_t LastIndexOf(self_t *str, const uint8_t ch) throws (String.Exception, String.Failure) {
	for (int32_t i = String.GetLength(str); 0 <= i; i--)
		if (String.GetCharAt(str, i) == ch) return i;

	throw (Signal.New(String.Failure));
}

method static self_t *Substring(self_t *str, const int32_t beginIndex, const int32_t lastIndex) throws (String.Exception) {
	if (   String.GetLength(str) + 1 < beginIndex
		|| String.GetLength(str) + 1 < lastIndex
		|| beginIndex > lastIndex ) throw (Signal.New(String.Exception));

	uint8_t *s = (uint8_t *)(
		_Memory.CountedAllocate(1 + lastIndex - beginIndex, sizeof(uint8_t))
	);
	strncpy(s, act(String_t, str)->_String + beginIndex, lastIndex - beginIndex);
	s[lastIndex - beginIndex - 1] = CC.NUL;

	return String.New(s);
}

method static self_t *DropLastChar(self_t *str) throws (String.Exception) {
	return String.Substring(str, 0, String.GetLength(str));
}

method static self_t *ReplaceWithChar(self_t *str, const uint8_t oldChar, const uint8_t newChar) throws (String.Exception) {
	uint8_t *s = (uint8_t *)(
		_Memory.CountedAllocate(String.GetLength(str) + 1, sizeof(uint8_t))
	);

	for (int32_t i = 0; i < String.GetLength(str); i++)
		s[i] = (String.GetCharAt(str, i) != oldChar)? String.GetCharAt(str, i) : newChar;

	return String.New(s);
}

method static self_t *Concat(self_t *str, self_t *str2) {
	uint8_t *s = (uint8_t *)(
		_Memory.CountedAllocate(String.GetLength(str) + String.GetLength(str2) + 1, sizeof(uint8_t))
	);

	strncpy(s, String.Unpack(str), String.GetLength(str));
	strncat(s, String.Unpack(str2), String.GetLength(str2));

	return String.New(s);
}

method static self_t *ConcatChar(self_t *str, const uint8_t ch) {
	uint8_t *s = (uint8_t *)(
		_Memory.CountedAllocate(1 + String.GetLength(str) + 1, sizeof(uint8_t))
	);

	char sArr[] = { ch };

	strncpy(s, String.Unpack(str), String.GetLength(str));
	strncat(s, sArr, strlen(sArr));

	return String.New(s);
}

method static bool IsEmpty(self_t *str) {
	return String.GetLength(str) == 0;
}

method static bool Equals(self_t *str, self_t *anString) {
	return !strncmp(
		String.Unpack(str),
		String.Unpack(anString),
		(String.GetLength(str) >= String.GetLength(anString))?
			String.GetLength(str) : String.GetLength(anString)
	) == 1;
}

method static bool StartsWith(self_t *str, self_t *prefix) throws (String.Exception) {
	if (String.GetLength(str) < String.GetLength(prefix))
		throw (Signal.New(String.Exception));

	for (uint32_t i = 0; i < String.GetLength(prefix); i++)
		if (String.GetCharAt(str, i) != String.GetCharAt(prefix, i))
			return false;

	return true;
}

method static bool StartsWithChar(self_t *str, const uint8_t ch) throws (String.Exception) {
	return String.GetHeadChar(str) == ch;
}

method static bool EndsWith(self_t *str, self_t *suffix) throws (String.Exception) {
	if (String.GetLength(str) < String.GetLength(suffix))
		throw (Signal.New(String.Exception));

	return !strncmp(
		act(String_t, str)->_String + String.GetLength(str) - String.GetLength(suffix),
		String.Unpack(suffix),
		String.GetLength(str)
	) == 1;
}

method static bool EndsWithChar(self_t *str, const uint8_t ch) throws (String.Exception) {
	return String.GetLastChar(str) == ch;
}

method static String_t *Init(String_t *str, const uint8_t *string) {
	Object.Init(act(Object_t, str));
	act(Object_t, str)->_Expr	= u8"(Object_t ~> String_t)";

	str->_Size					= (string != NULL)? strlen(string) + 1 : 1;
	str->_String				= (uint8_t *)(_Memory.CountedAllocate(str->_Size, sizeof(uint8_t)));
	if (string != NULL) strncpy(str->_String, string, strlen(string));
	str->_String[(string != NULL)? str->_Size - 1 : 0] = CC.NUL;

	str->GetExpr				= Object.GetExpr;

	str->Unpack					= Unpack;
	str->GetLength				= GetLength;
	str->GetCharAt				= GetCharAt;
	str->GetHeadChar			= GetHeadChar;
	str->GetLastChar			= GetLastChar;
	str->FirstIndexOf			= FirstIndexOf;
	str->LastIndexOf			= LastIndexOf;
	str->Substring				= Substring;
	str->DropLastChar			= DropLastChar;
	str->ReplaceWithChar		= ReplaceWithChar;
	str->Concat					= Concat;
	str->ConcatChar				= ConcatChar;
	str->IsEmpty				= IsEmpty;
	str->Equals					= Equals;
	str->StartsWith				= StartsWith;
	str->StartsWithChar			= StartsWithChar;
	str->EndsWith				= EndsWith;
	str->EndsWithChar			= EndsWithChar;

	return str;
}

method static String_t *New(const uint8_t *string) {
	return String.Init(new (String_t), string);
}

method static String_t *NewN(const size_t size) {
	String_t *str = String.New(NULL);
	String.Release(str);

	str->_Size = size;
	str->_String = (uint8_t *)(_Memory.CountedAllocate(str->_Size, sizeof(uint8_t)));

	return str;
}

method static String_t *NewFormat(const uint8_t *format, ...) {
	String_t *str = NewN(INT32_MAX); // 要実装

	use (format) {
		vsprintf(str->_String, format, ap);
	} release

	String.Reduce(str);
	return str;
}

method static String_t *NewChar(const uint8_t ch) {
	// strndup(&ch, 2);
	uint8_t tmp[] = { ch };
	return String.New(tmp);
}

method static void Reduce(String_t *str) throws (String.Exception) {
	uint8_t *tmp = strdup(str->_String);
	if (tmp == NULL) throw (Signal.New(String.Exception));

	str->_Size = String.GetLength(str) + 1;

	String.Release(str);
	str->_String = strdup(tmp);
	if (str->_String == NULL) throw (Signal.New(String.Exception));

	_Memory.Free(tmp);
}

method static void Release(String_t *str) {
	_Memory.Free(str->_String);
}

method static void Delete(String_t *str) {
	if (str == NULL) return;

	String.Release(str);
	delete (str);
}

_String String = {
	._Setup								= _Setup,

	.Init								= Init,
	.New								= New,
	.NewN								= NewN,
	.NewFormat							= NewFormat,
	.NewChar							= NewChar,
	.Reduce								= Reduce,
	.Release							= Release,
	.Delete								= Delete,

	.Unpack								= Unpack,
	.GetLength							= GetLength,
	.GetCharAt							= GetCharAt,
	.GetHeadChar						= GetHeadChar,
	.GetLastChar						= GetLastChar,
	.FirstIndexOf						= FirstIndexOf,
	.LastIndexOf						= LastIndexOf,
	.Substring							= Substring,
	.DropLastChar						= DropLastChar,
	.ReplaceWithChar					= ReplaceWithChar,
	.Concat								= Concat,
	.ConcatChar							= ConcatChar,
	.IsEmpty							= IsEmpty,
	.Equals								= Equals,
	.StartsWith							= StartsWith,
	.StartsWithChar						= StartsWithChar,
	.EndsWith							= EndsWith,
	.EndsWithChar						= EndsWithChar,
};
