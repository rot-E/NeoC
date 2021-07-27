#include <stdio.h>
#include <NeoC/Base/Object.h>

void main() {
	Object_t *obj = Object.New();

	printf("%s\n", obj->GetExpr(obj));
	printf("%s\n", Object.GetExpr(obj));

	Object.Delete(obj);
}
