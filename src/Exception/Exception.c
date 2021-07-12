#include "Exception.h"

static Context_t *New() {
	return (Context_t *)(_Memory.Allocate(sizeof(Context_t)));
}

static void Delete(Context_t *cxt) {
	free(cxt);
}

_Context Context = {
	.New			= New,
	.Delete			= Delete,
};


static void _Setup() {
	_Exception._Context = (Context_t *)(_Memory.CountedAllocate(_Exception._NEST_MAX, sizeof(Context_t)));
}

static Signal_t GenerateSignal() {
	return _Exception._SIGNAL_MAX++;
}

static void Try(const void (* Try)(), const void (* Catch)(), const void (* Finally)()) {
	if (_Exception._Nest >= _Exception._NEST_MAX - 1) _Error.Panic("\e[93m", "Exception System");

	if (setjmp(_Exception._Context[_Exception._Nest++]._Context) == 0) {
		Try();
	} else {
		Catch();
	}
	Finally();
}

static void Throw(const Signal_t sig) {
	if (_Exception._Nest < 0) _Error.Panic(u8"\e[93m", u8"Exception System");

	_Defer.Rewind();

	_Exception._Context[--_Exception._Nest]._Signal = sig;
	longjmp(_Exception._Context[_Exception._Nest]._Context, 1);
}

static Signal_t ElicitSignal() {
	return _Exception._Context[_Exception._Nest]._Signal;
}

__Exception _Exception = {
	._Setup					= _Setup,

	._SIGNAL_MAX			= 0,
	.GenerateSignal			= GenerateSignal,

	._Nest					= 0,
	._NEST_MAX				= 1000,

	.Try					= Try,
	.Throw					= Throw,
	.ElicitSignal			= ElicitSignal,
};
