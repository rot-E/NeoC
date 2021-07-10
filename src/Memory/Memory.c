#include "Memory.h"

static void _Setup() {
	Memory.Exception signal;
}

static void *_Inspect(void *ptr) throws (Memory.Exception) {
	if (ptr == NULL) throw (Memory.Exception);
	return ptr;
}

static void *Allocate(const size_t size) throws (Memory.Exception) {
	return _Inspect(malloc(size));;
}

static void *CountedAllocate(const size_t n, const size_t size) throws (Memory.Exception) {
	return _Inspect(calloc(n, size));
}

static void *SharedAllocate(const size_t size) throws (Memory.Exception) {
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

static void *ReAllocate(void *ptr, const size_t size) throws (Memory.Exception) {
	return _Inspect(realloc(ptr, size));
}

static void *ReCountedAllocate(void *ptr, const size_t n, const size_t size) throws (Memory.Exception) {
	return _Inspect(realloc(ptr, n * size));
}

static void Free(void *ptr) {
	free(ptr);
}

_Memory Memory = {
	._Setup						= _Setup,

	.Allocate					= Allocate,
	.CountedAllocate			= CountedAllocate,
	.SharedAllocate				= SharedAllocate,
	.ReAllocate					= ReAllocate,
	.ReCountedAllocate			= ReCountedAllocate,
	.Free						= Free,
};
