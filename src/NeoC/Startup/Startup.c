#include "Startup.h"

static void Startup() {
	String.Startup();
}

_S S = {
	.Startup = Startup,
};
