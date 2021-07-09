#include "Exception.h"

static Context_t *New() {
	return (Context_t *)(Memory.Allocate(sizeof(Context_t)));
}

static void Delete(Context_t *cxt) {
	free(cxt);
}

_Context Context = {
	.New			= New,
	.Delete			= Delete,
};


static void _Setup() {
	E._Context = (Context_t *)(Memory.CountedAllocate(E._NEST_MAX, sizeof(Context_t)));
}

static void _DEFAULT_HNDLER() {
	exit(EXIT_FAILURE);
}

static int32_t GenerateSignal() {
	return E._SIGNAL_MAX++;
}

static void Try(const void (* Try)(), const void (* Catch)(), const void (* Finally)()) {
	if (E._Nest >= E._NEST_MAX - 1) E._HANDLER();

	if (setjmp(E._Context[E._Nest++]._Context) == 0) {
		Try();
	} else {
		Catch();
	}
	Finally();
}

static void Throw(const int32_t sig) {
	if (E._Nest < 0) E._HANDLER();

	E._Context[--E._Nest]._Signal = sig;
	longjmp(E._Context[E._Nest]._Context, 1);
}

static int32_t ElicitSignal() {
	return E._Context[E._Nest]._Signal;
}

_E E = {
	._Setup					= _Setup,

	._SIGNAL_MAX			= 0,
	.GenerateSignal			= GenerateSignal,

	._Nest					= 0,
	._NEST_MAX				= 100,
	._HANDLER				= _DEFAULT_HNDLER,

	.Try					= Try,
	.Throw					= Throw,
	.ElicitSignal			= ElicitSignal,
};
