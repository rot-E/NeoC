#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "Annotation.h"

typedef struct {
	private void (* Panic)(uint8_t *colour, uint8_t *message);
} __Error;

extern __Error _Error;
