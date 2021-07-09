#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "Startup.h"
#include "Memory.h"
#include "Exception.h"

typedef struct String_t {
	int32_t _Size;
	uint8_t *_String;
} String_t;

typedef struct {
	void (* Startup)();

	int32_t Exception;
	int32_t RuntimeException;

	int32_t NEW_FORMAT_MAX_ALLOCATION_SIZE;

	struct {
		uint8_t Null;
		uint8_t CR;
		uint8_t LF;
	} CHARSET;

	String_t *(* New)(const uint8_t *str);
	String_t *(* NewN)(const size_t size);
	String_t *(* NewFormat)(const uint8_t *format, ...);
	void (* Reduce)(String_t *);
	void (* Release)(String_t *);
	void (* Delete)(String_t *);

	/* 取得系 */
	uint8_t *(* Unpack)(String_t *);
	int32_t (* GetLength)(String_t *);
	uint8_t (* GetCharAt)(String_t *, const int32_t index);
	uint8_t (* GetHeadChar)(String_t *);
	uint8_t (* GetLastChar)(String_t *);

	int32_t (* FirstIndexOf)(String_t *, const uint8_t ch);
	int32_t (* LastIndexOf)(String_t *, const uint8_t ch);

	/* 加工系 */
	String_t *(* Substring)(String_t *, const int32_t beginIndex, const int32_t lastIndex);
	String_t *(* DropLastChar)(String_t *);
	String_t *(* ReplaceWithChar)(String_t *, const uint8_t oldChar, const uint8_t newChar);
	String_t *(* Concat)(String_t *, String_t *str);
	String_t *(* ConcatChar)(String_t *, const uint8_t ch);

	/* 検査系 */
	bool (* IsEmpty)(String_t *);
	bool (* Equals)(String_t *, String_t *anString);
	bool (* StartsWith)(String_t *, String_t *prefix);
	bool (* StartsWithChar)(String_t *, const uint8_t ch);
	bool (* EndsWith)(String_t *, String_t *suffix);
	bool (* EndsWithChar)(String_t *, const uint8_t ch);
} _String;

extern _String String;
