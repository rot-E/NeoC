#include "NeoC/Collection/Stack.h"

static void _Setup() {
	Stack.Exception signal;
}

_Stack Stack = {
	._Setup						= _Setup,
	._ALLOCATION_BLOCK_SIZE		= 1000,
};
