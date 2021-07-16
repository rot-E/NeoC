#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "Annotation.h"
#include "Memory.h"
#include "Exception/Signal.h"
#include "Exception/Exception.h"
#include "SPEC/CC.h"
#include "Abbreviation.h"

typedef struct {
	private int32_t _Size;
	private uint8_t *_String;
} String_t;

typedef struct {
	private void (* _Setup)();

	public final SignalCode_t Exception;
	public final SignalCode_t Failure;

	private int32_t _NEW_FORMAT_MAX_ALLOCATION_SIZE;

	public String_t *(* New)(const uint8_t *str);
	public String_t *(* NewN)(const size_t size);
	public String_t *(* NewFormat)(const uint8_t *format, ...);
	public String_t *(* NewChar)(const uint8_t ch);
	public void (* Reduce)(String_t *) throws (String.Exception);
	private void (* Release)(String_t *);
	public void (* Delete)(String_t *);

	/* 取得系 */
	public uint8_t *(* Unpack)(String_t *);
	public int32_t (* GetLength)(String_t *);
	public uint8_t (* GetCharAt)(String_t *, const int32_t index) throws (String.Exception);
	public uint8_t (* GetHeadChar)(String_t *) throws (String.Exception);
	public uint8_t (* GetLastChar)(String_t *) throws (String.Exception);

	public int32_t (* FirstIndexOf)(String_t *, const uint8_t ch) throws (String.Exception, String.Failure);
	public int32_t (* LastIndexOf)(String_t *, const uint8_t ch) throws (String.Exception, String.Failure);

	/* 加工系 */
	public String_t *(* Substring)(String_t *, const int32_t beginIndex, const int32_t lastIndex) throws (String.Exception);
	public String_t *(* DropLastChar)(String_t *) throws (String.Exception);
	public String_t *(* ReplaceWithChar)(String_t *, const uint8_t oldChar, const uint8_t newChar) throws (String.Exception);
	public String_t *(* Concat)(String_t *, String_t *str);
	public String_t *(* ConcatChar)(String_t *, const uint8_t ch);

	/* 検査系 */
	public bool (* IsEmpty)(String_t *);
	public bool (* Equals)(String_t *, String_t *anString);
	public bool (* StartsWith)(String_t *, String_t *prefix) throws (String.Exception);
	public bool (* StartsWithChar)(String_t *, const uint8_t ch) throws (String.Exception);
	public bool (* EndsWith)(String_t *, String_t *suffix) throws (String.Exception);
	public bool (* EndsWithChar)(String_t *, const uint8_t ch) throws (String.Exception);
} _String;

extern _String String;
