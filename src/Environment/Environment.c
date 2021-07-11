#include "Environment.h"

static void _Setup() {
	_Exception._Setup();
	_Defer._Setup();

	CSI._Setup();
	SGR._Setup();

	String._Setup();
	System._Setup();
	Socket._Setup();
}

static void _DEFAULT_MAIN_EXCEPTION_HANDLER() {
	fprintf(stderr, "%s%s%s%s%s\n",
		"\e[91m",
		"[Exception] ",
		"\e[36m",
		"main function",
		"\e[39m"
	);
	exit(EXIT_FAILURE);
}

__Environment _Environment = {
	._Setup						= _Setup,

	._MAIN_EXCEPTION_HANDLER	= _DEFAULT_MAIN_EXCEPTION_HANDLER,
};
