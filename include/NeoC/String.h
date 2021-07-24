#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "NeoC/Base/Object.h"
#include "NeoC/Base/Memory.h"
#include "NeoC/Base/Exception/Signal.h"
#include "NeoC/Base/Exception/Exception.h"
#include "NeoC/SPEC/CC.h"
#include "NeoC/Abbreviation.h"

class String_t {
	extends (Object_t);

	private int32_t _Size;
	private uint8_t *_String;

	/* 取得系 */
	public uint8_t *(* Unpack)(self *);
	public int32_t (* GetLength)(self *);
	public uint8_t (* GetCharAt)(self *, const int32_t index) throws (String.Exception);
	public uint8_t (* GetHeadChar)(self *) throws (String.Exception);
	public uint8_t (* GetLastChar)(self *) throws (String.Exception);

	public int32_t (* FirstIndexOf)(self *, const uint8_t ch) throws (String.Exception, String.Failure);
	public int32_t (* LastIndexOf)(self *, const uint8_t ch) throws (String.Exception, String.Failure);

	/* 加工系 */
	public struct String_t *(* Substring)(self *, const int32_t beginIndex, const int32_t lastIndex) throws (String.Exception);
	public struct String_t *(* DropLastChar)(self *) throws (String.Exception);
	public struct String_t *(* ReplaceWithChar)(self *, const uint8_t oldChar, const uint8_t newChar) throws (String.Exception);
	public struct String_t *(* Concat)(self *, struct String_t *str);
	public struct String_t *(* ConcatChar)(self *, const uint8_t ch);

	/* 検査系 */
	public bool (* IsEmpty)(self *);
	public bool (* Equals)(self *, struct String_t *anString);
	public bool (* StartsWith)(self *, struct String_t *prefix) throws (String.Exception);
	public bool (* StartsWithChar)(self *, const uint8_t ch) throws (String.Exception);
	public bool (* EndsWith)(self *, struct String_t *suffix) throws (String.Exception);
	public bool (* EndsWithChar)(self *, const uint8_t ch) throws (String.Exception);
} String_t;

class _String {
	private void (* _Setup)();

	public final SignalCode_t Exception;
	public final SignalCode_t Failure;

	public String_t *(* Init)(String_t *str, const uint8_t *string);
	public String_t *(* New)(const uint8_t *string);
	public String_t *(* NewN)(const size_t size);
	public String_t *(* NewFormat)(const uint8_t *format, ...);
	public String_t *(* NewChar)(const uint8_t ch);
	public void (* Reduce)(String_t *) throws (String.Exception);
	private void (* Release)(String_t *);
	public void (* Delete)(String_t *);

	/* 取得系 */
	public uint8_t *(* Unpack)(self_t *);
	public int32_t (* GetLength)(self_t *);
	public uint8_t (* GetCharAt)(self_t *, const int32_t index) throws (String.Exception);
	public uint8_t (* GetHeadChar)(self_t *) throws (String.Exception);
	public uint8_t (* GetLastChar)(self_t *) throws (String.Exception);

	public int32_t (* FirstIndexOf)(self_t *, const uint8_t ch) throws (String.Exception, String.Failure);
	public int32_t (* LastIndexOf)(self_t *, const uint8_t ch) throws (String.Exception, String.Failure);

	/* 加工系 */
	public String_t *(* Substring)(self_t *, const int32_t beginIndex, const int32_t lastIndex) throws (String.Exception);
	public String_t *(* DropLastChar)(self_t *) throws (String.Exception);
	public String_t *(* ReplaceWithChar)(self_t *, const uint8_t oldChar, const uint8_t newChar) throws (String.Exception);
	public String_t *(* Concat)(self_t *, String_t *str);
	public String_t *(* ConcatChar)(self_t *, const uint8_t ch);

	/* 検査系 */
	public bool (* IsEmpty)(self_t *);
	public bool (* Equals)(self_t *, String_t *anString);
	public bool (* StartsWith)(self_t *, String_t *prefix) throws (String.Exception);
	public bool (* StartsWithChar)(self_t *, const uint8_t ch) throws (String.Exception);
	public bool (* EndsWith)(self_t *, String_t *suffix) throws (String.Exception);
	public bool (* EndsWithChar)(self_t *, const uint8_t ch) throws (String.Exception);
} _String;

extern _String String;
