#include "Exception.h"

static int32_t GenerateSignal() {
	E._SIGNAL_MAX += 1;
	return E._SIGNAL_MAX;
}

static void Try(E_t *self, void (* Code)(), void (* Catch)(), void (* Finally)()) {
	if (setjmp(self->_Context) == 0) {
		Code();
	} else {
		Catch();
	}
	Finally();
}

static void Throw(E_t *self, int32_t sig) {
	self->_Signal = sig;
	longjmp(self->_Context, 1);
}

static int32_t ElicitSignal(E_t *self) {
	return self->_Signal;
}

static E_t *Begin() {
	return (E_t *)(Memory.Allocate(sizeof(E_t)));;
}

static void End(E_t *e) {
	free(e);
}

_E E = {
	._SIGNAL_MAX			= 0,

	.GenerateSignal			= GenerateSignal,

	.Begin					= Begin,
	.End					= End,

	.Try					= Try,
	.Throw					= Throw,
	.ElicitSignal			= ElicitSignal,
};
