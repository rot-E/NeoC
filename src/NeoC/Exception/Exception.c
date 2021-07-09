#include "Exception.h"

static int32_t GenerateSignal() {
	return E._SIGNAL_MAX++;
}

static void Try(void (* Try)(), void (* Catch)(), void (* Finally)()) {
	if (setjmp(E._Context) == 0) {
		Try();
	} else {
		Catch();
	}
	Finally();
}

static void Throw(int32_t sig) {
	E._Signal = sig;
	longjmp(E._Context, 1);
}

static int32_t ElicitSignal() {
	return E._Signal;
}

_E E = {
	._SIGNAL_MAX			= 0,

	.GenerateSignal			= GenerateSignal,

	.Try					= Try,
	.Throw					= Throw,
	.ElicitSignal			= ElicitSignal,
};
