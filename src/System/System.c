#include "System.h"

static void _Setup() {
	System.Exception signal;
}

static void Sleep(uint32_t sec) {
	if (sleep(sec) != 0) throw (System.Exception);
}

static void USleep(useconds_t usec) throws (System.Exception) {
	if (usleep(usec) == -1) throw (System.Exception);
}

_System System = {
	._Setup		= _Setup,

	.Sleep		= Sleep,
	.USleep		= USleep,
};
