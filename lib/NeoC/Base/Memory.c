#include "NeoC/Base/Memory.h"

static any *_Inspect(any *ptr) {
	if (ptr == NULL) _Error.Panic(u8"\e[36m", u8"Memory System");
	return ptr;
}

method static any *Allocate(const size_t size) {
	return _Inspect(malloc(size));;
}

method static any *CountedAllocate(const size_t n, const size_t size) {
	return _Inspect(calloc(n, size));
}

method static any *SharedAllocate(const size_t size) {
	return _Inspect(
		mmap(
			NULL,
			size,
			PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS,
			-1, 0
		)
	);
}

method static any *ReAllocate(any *ptr, const size_t size) {
	return _Inspect(realloc(ptr, size));
}

method static void Free(any *ptr) {
	free(ptr);
}

method static void SharedFree(any *ptr, const size_t size) {
	munmap(ptr, size);
}

method static void Delete(any *ptr) {
	if (ptr == NULL) return;

	free(ptr);
	ptr = NULL;
}

__Memory _Memory = {
	.Allocate					= Allocate,
	.CountedAllocate			= CountedAllocate,
	.SharedAllocate				= SharedAllocate,
	.ReAllocate					= ReAllocate,
	.Free						= Free,
};
