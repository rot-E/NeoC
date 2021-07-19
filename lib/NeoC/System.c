#include "System.h"

static void _Setup() {
	System.Exception signal;

	FD_ZERO(&System._State);
	FD_SET(0, &System._State);
}

static void Sleep(uint32_t sec) {
	if (sleep(sec) != 0) throw (Signal.New(System.Exception));
}

static void USleep(useconds_t usec) throws (System.Exception) {
	if (usleep(usec) == -1) throw (Signal.New(System.Exception));
}

static bool Keystroked() {
	fd_set tmp = System._State;
	select(1, &tmp, NULL, NULL, &(struct timeval){ .tv_sec = 0, .tv_usec = 0 });

	return FD_ISSET(0, &tmp);
}

_System System = {
	._Setup			= _Setup,

	.Sleep			= Sleep,
	.USleep			= USleep,

	.Keystroked		= Keystroked,
};
