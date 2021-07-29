#include "NeoC/Type/UInt32.h"

method static uint32_t Unpack(self_t *uint32) {
	return act(UInt32_t, uint32)->_UInt32;
}

method static uint8_t *GetExpr(self_t *uint32) {
	return String.Unpack(String.NewFormat(
		"%d",
		UInt32.Unpack(uint32)
	));
}

method static UInt32_t *Init(UInt32_t *uint32, const uint32_t ui32) {
	act(PrimitiveWrapper_i, uint32)->GetExpr	= GetExpr;

	uint32->_UInt32								= ui32;

	uint32->Unpack								= Unpack;
	uint32->GetExpr								= GetExpr;

	return uint32;
}

method static UInt32_t *New(const uint32_t ui32) {
	return UInt32.Init(new (UInt32_t), ui32);
}

method static void Delete(UInt32_t *uint32) {
	if (uint32 == NULL) return;

	delete (uint32);
}

_UInt32 UInt32 = {
	.Init		= Init,
	.New		= New,
	.Delete		= Delete,

	.Unpack		= Unpack,
	.GetExpr	= GetExpr,
};
