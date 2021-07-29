#include "NeoC/Type/Int32.h"

method static int32_t Unpack(self_t *int32) {
	return act(Int32_t, int32)->_Int32;
}

method static uint8_t *GetExpr(self_t *int32) {
	return String.Unpack(String.NewFormat(
		"%d",
		Int32.Unpack(int32)
	));
}

method static Int32_t *Init(Int32_t *int32, const int32_t i32) {
	act(PrimitiveWrapper_i, int32)->GetExpr		= GetExpr;

	int32->_Int32								= i32;

	int32->Unpack								= Unpack;
	int32->GetExpr								= GetExpr;

	return int32;
}

method static Int32_t *New(const int32_t i32) {
	return Int32.Init(new (Int32_t), i32);
}

method static void Delete(Int32_t *int32) {
	if (int32 == NULL) return;

	delete (int32);
}

_Int32 Int32 = {
	.Init		= Init,
	.New		= New,
	.Delete		= Delete,

	.Unpack		= Unpack,
	.GetExpr	= GetExpr,
};
