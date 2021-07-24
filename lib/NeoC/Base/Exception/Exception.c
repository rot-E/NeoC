#include "NeoC/Base/Exception/Exception.h"

method static Context_t *Init(Context_t *ctx) {
	Object.Init(act(Object_t, ctx));
	act(Object_t, ctx)->_Expr	= u8"(Object_t ~> Context_t)";

	ctx->GetExpr				= Object.GetExpr;
}

method static Context_t *New() {
	return Context.Init(new (Context_t));
}

method static void Delete(Context_t *ctx) {
	delete (ctx);
}

_Context Context = {
	.Init			= Init,
	.New			= New,
	.Delete			= Delete,
};


method static void _Setup() {
	Context.GetExpr			= Object.GetExpr;

	_Exception._Context		= (Context_t *)(
		_Memory.CountedAllocate(_Exception._NEST_MAX, sizeof(Context_t))
	);
}

method static SignalCode_t AssignSignalCode() {
	return _Exception._SIGNAL_CODE_MAX++;
}

method static void Try(const void (* Try)(), const void (* Catch)(Signal_t *), const void (* Finally)()) {
	if (_Exception._Nest >= _Exception._NEST_MAX - 1) _Error.Panic("\e[93m", "Exception System");

	bool threw = false;
	if (setjmp(_Exception._Context[_Exception._Nest++]._Context) == 0) {
		Try();
	} else {
		threw = true;
		Catch(_Exception._Context[_Exception._Nest]._Signal);
	}
	Finally();

	if (!threw) _Exception._Nest--;
}

method static void Throw(Signal_t *sig) {
	if (_Exception._Nest < 0) _Error.Panic(u8"\e[93m", u8"Exception System");

	_Defer.Rewind();

	_Exception._Context[--_Exception._Nest]._Signal = sig;
	longjmp(_Exception._Context[_Exception._Nest]._Context, 1);
}

__Exception _Exception = {
	._Setup					= _Setup,

	._SIGNAL_CODE_MAX		= 0,
	.AssignSignalCode		= AssignSignalCode,

	._Nest					= 0,
	._NEST_MAX				= 1000,

	.Try					= Try,
	.Throw					= Throw,
};
