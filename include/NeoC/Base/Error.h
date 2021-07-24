#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "NeoC/Base/Object.h"

class __Error {
	private void (* Panic)(uint8_t *colour, uint8_t *message);
} __Error;

extern __Error _Error;
