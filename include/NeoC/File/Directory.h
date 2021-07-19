#pragma once

#include <stdbool.h>
#include <sys/stat.h>

#include "NeoC/Annotation.h"
#include "NeoC/String.h"

typedef struct {
	private void (* _Setup)() throws (Directory.Exception);

	public final Exception;

	public bool (* Exists)(String_t *path);
	public bool (* Create)(String_t *path);
	public bool (* Delete)(String_t *path);
} _Directory;

extern _Directory Directory;
