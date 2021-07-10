#include "String.h"

static void _Setup() {
	String.Exception signal;
	String.RuntimeException signal;
}

static String_t *New(const uint8_t *string) {
	String_t *str = (String_t *)(Memory.Allocate(sizeof(String_t)));
	str->_Size		= (string != NULL)? strlen(string) + 1 : 1;
	str->_String	= (uint8_t *)(Memory.CountedAllocate(str->_Size, sizeof(uint8_t)));
	if (string != NULL) strncpy(str->_String, string, strlen(string));
	str->_String[(string != NULL)? str->_Size - 1 : 0] = CC.NUL;

	return str;
}

static String_t *NewN(const size_t size) {
	String_t *str = String.New(NULL);
	String.Release(str);

	str->_Size = size;
	str->_String = (uint8_t *)(Memory.CountedAllocate(str->_Size, sizeof(uint8_t)));

	return str;
}

static String_t *NewFormat(const uint8_t *format, ...) {
	String_t *str = NewN(String._NEW_FORMAT_MAX_ALLOCATION_SIZE); // 要実装

	va_list ap;

	va_start(ap, format);
	vsprintf(str->_String, format, ap);
	va_end(ap);

	str->_String[str->_Size - 1] = CC.NUL; //
	String.Reduce(str);

	return str;
}

static String_t *NewChar(const uint8_t ch) {
	uint8_t tmp[] = { ch };
	return String.New(tmp);
}

static void Reduce(String_t *str) {
	uint8_t *tmp = (uint8_t *)(Memory.CountedAllocate(String.GetLength(str) + 1, sizeof(uint8_t)));
	strncpy(tmp, String.Unpack(str), String.GetLength(str) + 1);

	str->_Size = String.GetLength(str) + 1;
	String.Release(str);
	str->_String = (uint8_t *)(Memory.CountedAllocate(str->_Size, sizeof(uint8_t)));
	strncpy(str->_String, tmp, str->_Size);
	str->_String[str->_Size - 1] = CC.NUL;

	free(tmp);
}

static void Release(String_t *str) {
	free(str->_String);
}

static void Delete(String_t *str) {
	String.Release(str);
	free(str);
}

static uint8_t *Unpack(String_t *str) {
	return str->_String;
}

static int32_t GetLength(String_t *str) {
	return strlen(str->_String);
}

static uint8_t GetCharAt(String_t *str, const int32_t index) throws (String.Exception) {
	if (String.GetLength(str) < index) throw (String.Exception);

	return String.Unpack(str)[index];
}

static uint8_t GetHeadChar(String_t *str) throws (String.Exception) {
	if (String.GetLength(str) < 1) throw (String.Exception);

	return String.GetCharAt(str, 0);
}

static uint8_t GetLastChar(String_t *str) throws (String.Exception) {
	if (String.GetLength(str) < 1) throw (String.Exception);

	return String.GetCharAt(str, String.GetLength(str) - 1);
}

static int32_t FirstIndexOf(String_t *str, const uint8_t ch) throws (String.Exception, String.RuntimeException) {
	for (int32_t i = 0; i < String.GetLength(str); i++)
		if (String.GetCharAt(str, i) == ch) return i;

	throw (String.RuntimeException);
}

static int32_t LastIndexOf(String_t *str, const uint8_t ch) throws (String.Exception, String.RuntimeException) {
	for (int32_t i = String.GetLength(str); 0 <= i; i--)
		if (String.GetCharAt(str, i) == ch) return i;

	throw (String.RuntimeException);
}

static String_t *Substring(String_t *str, const int32_t beginIndex, const int32_t lastIndex) throws (String.Exception) {
	if (   String.GetLength(str) + 1 < beginIndex
		|| String.GetLength(str) + 1 < lastIndex
		|| beginIndex > lastIndex ) throw (String.Exception);

	uint8_t *s = (uint8_t *)(
		Memory.CountedAllocate(1 + lastIndex - beginIndex, sizeof(uint8_t))
	);
	strncpy(s, str->_String + beginIndex, lastIndex - beginIndex);
	s[lastIndex - beginIndex - 1] = CC.NUL;

	return String.New(s);
}

static String_t *DropLastChar(String_t *str) throws (String.Exception) {
	return String.Substring(str, 0, String.GetLength(str));
}

static String_t *ReplaceWithChar(String_t *str, const uint8_t oldChar, const uint8_t newChar) throws (String.Exception) {
	uint8_t *s = (uint8_t *)(
		Memory.CountedAllocate(String.GetLength(str) + 1, sizeof(uint8_t))
	);

	for (int32_t i = 0; i < String.GetLength(str); i++)
		s[i] = (String.GetCharAt(str, i) != oldChar)? String.GetCharAt(str, i) : newChar;

	return String.New(s);
}

static String_t *Concat(String_t *str, String_t *str2) {
	uint8_t *s = (uint8_t *)(
		Memory.CountedAllocate(String.GetLength(str) + String.GetLength(str2) + 1, sizeof(uint8_t))
	);

	strncpy(s, String.Unpack(str), String.GetLength(str));
	strncat(s, String.Unpack(str2), String.GetLength(str2));

	return String.New(s);
}

static String_t *ConcatChar(String_t *str, const uint8_t ch) {
	uint8_t *s = (uint8_t *)(
		Memory.CountedAllocate(1 + String.GetLength(str) + 1, sizeof(uint8_t))
	);

	char sArr[] = { ch };

	strncpy(s, String.Unpack(str), String.GetLength(str));
	strncat(s, sArr, strlen(sArr));

	return String.New(s);
}

static bool IsEmpty(String_t *str) {
	return String.GetLength(str) == 0;
}

static bool Equals(String_t *str, String_t *anString) {
	return !strncmp(
		String.Unpack(str),
		String.Unpack(anString),
		(String.GetLength(str) >= String.GetLength(anString))?
			String.GetLength(str) : String.GetLength(anString)
	) == 1;
}

static bool StartsWith(String_t *str, String_t *prefix) throws (String.Exception) {
	if (String.GetLength(str) < String.GetLength(prefix))
		throw (String.Exception);

	for (uint32_t i = 0; i < String.GetLength(prefix); i++)
		if (String.GetCharAt(str, i) != String.GetCharAt(prefix, i))
			return false;

	return true;
}

static bool StartsWithChar(String_t *str, const uint8_t ch) throws (String.Exception) {
	return String.GetHeadChar(str) == ch;
}

static bool EndsWith(String_t *str, String_t *suffix) throws (String.Exception) {
	if (String.GetLength(str) < String.GetLength(suffix))
		throw (String.Exception);

	return !strncmp(
		str->_String + String.GetLength(str) - String.GetLength(suffix),
		String.Unpack(suffix),
		String.GetLength(str)
	) == 1;
}

static bool EndsWithChar(String_t *str, const uint8_t ch) throws (String.Exception) {
	return String.GetLastChar(str) == ch;
}

_String String = {
	._Setup								= _Setup,

	._NEW_FORMAT_MAX_ALLOCATION_SIZE		= 100000,

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
