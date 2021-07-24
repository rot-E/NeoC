#include "NeoC/Base/Object.h"

method static uint8_t *GetExpr(self_t *obj) {
	return act(Object_t, obj)->_Expr;
}

method static Object_t *Init(Object_t *obj) {
	obj->_Expr = u8"(Object_t)";

	obj->GetExpr = GetExpr;

	return obj;
}

method static Object_t *New() {
	return Object.Init(new (Object_t));
}

method static void Delete(Object_t *obj) {
	delete (obj);
}

_Object Object = {
	.Init			= Init,
	.New			= New,
	.Delete			= Delete,

	.GetExpr		= GetExpr,
};
