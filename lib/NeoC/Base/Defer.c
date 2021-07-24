#include "NeoC/Base/Defer.h"

method static void _Setup() {
	_Defer._Task = (void (**)())(
		_Memory.CountedAllocate(_Defer._TASK_MAX, sizeof(void (*)()))
	);
}

method static void Set(void (* Task)()) {
	if (_Defer._Index >= _Defer._TASK_MAX) _Error.Panic(u8"\e[92m", u8"Defer System");

	_Defer._Task[_Defer._Index++] = Task;
}

method static void Rewind() {
	while (_Defer._Index > 0) _Defer._Task[--_Defer._Index]();
}

method static void *Execute(void *(* Procedure)()) {
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
