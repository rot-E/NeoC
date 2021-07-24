#pragma once

/* ------------------------------------------------------ */
/* 事後処理登録 */
#define defer _Defer.Set(({ void Task()

#define set Task; }));

/* 実処理登録 */
// 戻り値無し
#define execute _Defer.Execute(({ void *Procedure()

// 戻り値在り: 内部でポインタをreturnすること
#define retrieve return _Defer.Execute(({ void *Procedure()

#define ret Procedure; }));
/* ------------------------------------------------------ */

#include <stdint.h>

#include "NeoC/Annotation.h"
#include "NeoC/Object.h"
#include "NeoC/Memory.h"

class __Defer {
	private void (* _Setup)();

	private final int32_t _TASK_MAX;
	private int32_t _Index;
	private void (** _Task)();

	public void (* Set)(void (* Task)());
	library public void (* Rewind)();
	public void *(* Execute)(void *(* Procedure)());
} __Defer;

extern __Defer _Defer;
