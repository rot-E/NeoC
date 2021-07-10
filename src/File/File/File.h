#pragma once

typedef struct {
	File *_File;
} File_t;

typedef struct {
	public final Exception;

	File_t *(* New)(String_t *name) throws (File.Exception);
	private void (* Release)(String_t *);
	void (* Delete)(File_t *);
} _File;

extern _File File;
