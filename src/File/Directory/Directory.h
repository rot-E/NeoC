#pragma once

#include <stdbool.h>
#include <sys/stat.h>

#include "../String.h"

typedef struct {
	bool (* Exists)(String_t *path);
	bool (* Create)(String_t *path);
	bool (* Delete)(String_t *path);
} _Directory;

extern _Directory Directory;
