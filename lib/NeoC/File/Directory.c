#include "NeoC/File/Directory.h"

static void _Setup() {
	Directory.Exception signal;
}

static bool Exists(String_t *path) throws (Directory.Exception) {
	DIR *dir = opendir(String.Unpack(path));

	if (dir != NULL)
		return true;

	if (errno == ENOENT)
		return false;

	throw (Directory.Exception);
}

static bool Create(String_t *path) {

}

static bool Delete(String_t *path) {
}

_Directory Directory = {
	._Setup		= _Setup,

	.Exists		= Exists,
	.Create		= Create,
	.Delete		= Delete,
};
