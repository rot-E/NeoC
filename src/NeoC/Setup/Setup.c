#include "Setup.h"

static void _Setup() {
	CSI._Setup();
	SGR._Setup();

	String._Setup();
}

__S _S = {
	._Setup = _Setup,
};
