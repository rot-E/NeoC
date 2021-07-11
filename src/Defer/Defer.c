#include "Defer.h"

static void _Setup() {
	_Defer._Task = (void (**)())(
		_Memory.CountedAllocate(_Defer._TASK_MAX, sizeof(void (*)()))
	);
}

static void Set(void (* Task)()) {
	if (_Defer._Index >= _Defer._TASK_MAX) _Error.Panic("\e[92m", "Defer System");

	_Defer._Task[_Defer._Index++] = Task;
}

static void Rewind() {
	while (_Defer._Index > 0) _Defer._Task[--_Defer._Index]();
}

static void *Execute(void *(* Procedure)()) {
	void *r = Procedure();
	_Defer.Rewind();
	return r;
}

__Defer _Defer = {
	._Setup			= _Setup,

	._Index			= 0,
	._TASK_MAX		= 10000,

	.Set			= Set,
	.Rewind			= Rewind,
	.Execute		= Execute,
};
