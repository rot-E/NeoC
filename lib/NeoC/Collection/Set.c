#include "NeoC/Collection/Set.h"

static void _Setup() {
	Set.Exception signal;
}

_Set Set = {
	._Setup						= _Setup,
	._ALLOCATION_BLOCK_SIZE		= 1000,
};
