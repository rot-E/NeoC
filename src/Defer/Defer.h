#pragma once


#define defer _Defer.Set(({ void Task()

#define set Task; }));

#define execute _Defer.Execute(({ void *Procedure()

#define ret Procedure; }));

#include <stdint.h>

#include "Annotation.h"
#include "Memory.h"

typedef struct {
	private void (* _Setup)();

	private final int32_t _TASK_MAX;
	private int32_t _Index;
	private void (** _Task)();

	public void (* Set)(void (* Task)());
	public void *(* Execute)(void *(* Procedure)());
} __Defer;

extern __Defer _Defer;
