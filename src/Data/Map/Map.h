#pragma once

/* ------------------------------------------------------ */
#define T(KT, VT) sizeof(KT), sizeof(VT)

#define $put(T, VAL)		\
	({						\
		T _tmp = VAL;		\
		(void *)(&_tmp);	\
	})

#define in(...)
/* ------------------------------------------------------ */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <threads.h>

#include "../Annotation.h"
#include "../Exception/Signal.h"
#include "../Exception/Exception.h"

#include "../Debug.h"

typedef struct {
	public void *Key;
	public void *Value;
} Set_t;

typedef struct Map_t {
	Set_t *_Set;
	private int32_t _Size;
	private int32_t _KeySize;
	private int32_t _ValueSize;
	private bool (* _KeyComparer)(void *mapKey, void *key);
	private bool (* _ValueComparer)(void *mapValue, void *value);

	mtx_t _Mtx;

	/* 操作系 */
	public void (* Put)(struct Map_t *, void *key, void *value);
	public void (* Remove)(struct Map_t *, void *key);

	/* 取得系 */
	public int32_t (* GetSize)(struct Map_t *);
	public Set_t (* GetSet)(struct Map_t *, int32_t);

	/* 検査系 */
	public bool (* IsEmpty)(struct Map_t *);
	public bool (* ContainsKey)(struct Map_t *, void *key);
	public bool (* ContainsValue)(struct Map_t *, void *value);
} Map_t;

typedef struct {
	private void (* _Setup)();
	public final SignalCode_t Exception;
	private final int32_t _SIZE_MAX;

	public Map_t *(* New)(
		const size_t keySize,
		const size_t valueSize,
		bool (* keyComparer)(void *mapKey, void *key),
		bool (* valueComparer)(void *mapValue, void *value)
	);
	public void (* Delete)(Map_t *);

	/* 操作系 */
	public void (* Put)(struct Map_t *, void *key, void *value);
	public void (* Remove)(Map_t *, void *key);

	/* 取得系 */
	public int32_t (* GetSize)(Map_t *);
	public Set_t (* GetSet)(Map_t *, int32_t);

	/* 検査系 */
	public bool (* IsEmpty)(Map_t *);
	public bool (* ContainsKey)(Map_t *, void *key);
	public bool (* ContainsValue)(Map_t *, void *value);
} _Map;

extern _Map Map;