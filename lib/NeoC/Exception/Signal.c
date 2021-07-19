#include "NeoC/Exception/Signal.h"

static Signal_t *New(SignalCode_t code) {
	Signal_t *sig = (Signal_t *)(_Memory.Allocate(sizeof(Signal_t)));

	sig->_Code = code;

	return sig;
}

static Signal_t *Build(SignalCode_t code, uint8_t *message) {
	Signal_t *sig = Signal.New(code);

	sig->_Message = strdup(message);

	return sig;
}

static void Delete(Signal_t *sig) {
	_Memory.Free(sig->_Message);
	_Memory.Free(sig);
}

static SignalCode_t GetSignalCode(Signal_t *sig) {
	return sig->_Code;
}

static bool MessageExists(Signal_t *sig) {
	return sig->_Message != NULL;
}

static void SetMessage(Signal_t *sig, const uint8_t *message) {
	sig->_Message = strdup(message);
}

static uint8_t *GetMessage(Signal_t *sig) {
	return sig->_Message;
}

_Signal Signal = {
	.New				= New,
	.Build				= Build,
	.Delete				= Delete,

	.GetSignalCode		= GetSignalCode,

	.MessageExists		= MessageExists,
	.SetMessage			= SetMessage,
	.GetMessage			= GetMessage,
};
