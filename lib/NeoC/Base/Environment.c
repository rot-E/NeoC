#include "NeoC/Base/Environment.h"

method static void _Setup() {
	/// Signal._Setup();
	_Exception._Setup();
	_Defer._Setup();

	CSI._Setup();
	SGR._Setup();

	String._Setup();
	System._Setup();
	Socket._Setup();

	/// Collection._Setup();
	Tuple._Setup();
	List._Setup();
	Stack._Setup();
	Queue._Setup();
	Map._Setup();
}

static void _DEFAULT_MAIN_EXCEPTION_HANDLER(Signal_t *sig) {
	fprintf(stderr, u8"%s%s%s%s%s\n",
		u8"\e[91m",
		u8"[Exception] ",
		u8"\e[36m",
		u8"main function",
		u8"\e[39m"
	);

	if (Signal.MessageExists(sig))
		fprintf(stderr, u8"%s%s%s%s\n",
			u8"    ",
			u8"\e[36m",
			Signal.GetMessage(sig),
			u8"\e[39m"
		);

	exit(EXIT_FAILURE);
}

__Environment _Environment = {
	._Setup						= _Setup,

	._MAIN_EXCEPTION_HANDLER	= _DEFAULT_MAIN_EXCEPTION_HANDLER,
};
