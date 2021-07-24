#include "NeoC/Base/Exception/Signal.h"

method static void _Setup() {
	Signal.GetExpr = Object.GetExpr;
}

method static SignalCode_t GetSignalCode(self_t *sig) {
	return act(Signal_t, sig)->_Code;
}

method static bool MessageExists(self_t *sig) {
	return act(Signal_t, sig)->_Message != NULL;
}

method static void SetMessage(self_t *sig, const uint8_t *message) {
	act(Signal_t, sig)->_Message = strdup(message);
}

method static uint8_t *GetMessage(self_t *sig) {
	return act(Signal_t, sig)->_Message;
}

method static Signal_t *Init(Signal_t *sig, SignalCode_t code) {
	Object.Init(act(Object_t, sig));
	act(Object_t, sig)->_Expr	= u8"(Object_t ~> Signal_t)";

	sig->_Code					= code;

	sig->GetExpr				= Object.GetExpr;

	sig->GetSignalCode			= GetSignalCode;
	sig->MessageExists			= MessageExists;
	sig->SetMessage				= SetMessage;
	sig->GetMessage				= GetMessage;

	return sig;
}

method static Signal_t *New(SignalCode_t code) {
	return Signal.Init(new (Signal_t), code);
}

method static Signal_t *Build(SignalCode_t code, uint8_t *message) {
	Signal_t *sig = Signal.New(code);
	Signal.SetMessage(sig, message);

	return sig;
}

method static void Delete(Signal_t *sig) {
	delete (sig->_Message);
	delete (sig);
}

_Signal Signal = {
	._Setup				= _Setup,

	.Init				= Init,
	.New				= New,
	.Build				= Build,
	.Delete				= Delete,

	.GetSignalCode		= GetSignalCode,
	.MessageExists		= MessageExists,
	.SetMessage			= SetMessage,
	.GetMessage			= GetMessage,
};
