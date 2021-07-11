#include "Directory.h"

static bool Exists(String_t *path) {

}

static bool Create(String_t *path) {

}

static bool Delete(String_t *path) {
}

_Directory Directory = {
	.Exists		= Exists,
	.Create		= Create,
	.Delete		= Delete,
};
