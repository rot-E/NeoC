#include "NeoC/Type/Bit.h"

method static void _Setup() {
	Bit.Exception signal;
}

method static int32_t Unpack(self_t *bit) {
	return act(Bit_t, bit)->_Bit;
}

method static uint8_t *GetExpr(self_t *bit) {
	return (act(Bit_t, bit)->_Bit == 1)? u8"1" : u8"0";
}

method static self_t *Not(self_t *b) {
	return Bit.New(!Bit.Unpack(b));
}

method static self_t *And(self_t *b1, self_t *b2) {
	return Bit.New(Bit.Unpack(b1) && Bit.Unpack(b2));
}

method static self_t *Or(self_t *b1, self_t *b2) {
	return Bit.New(Bit.Unpack(b1) || Bit.Unpack(b2));
}

method static self_t *Nand(self_t *b1, self_t *b2) {
	return Bit.New(!(Bit.Unpack(b1) && Bit.Unpack(b2)));
}

method static self_t *Nor(self_t *b1, self_t *b2) {
	return Bit.New(!(Bit.Unpack(b1) || Bit.Unpack(b2)));
}

method static Bit_t *Init(Bit_t *bit, const int32_t b) {
	act(PrimitiveWrapper_i, bit)->GetExpr		= GetExpr;

	bit->_Bit									= b;

	bit->Unpack									= Unpack;
	bit->GetExpr								= GetExpr;
	bit->Not									= Not;
	bit->And									= And;
	bit->Or										= Or;
	bit->Nand									= Nand;
	bit->Nor									= Nor;

	return bit;
}

method static Bit_t *New(const int32_t b) throws (Bit.Exception) {
	if (b != 0 && b != 1) throw (Signal.New(Bit.Exception));
	return Bit.Init(new (Bit_t), b);
}

method static void Delete(Bit_t *bit) {
	if (bit == NULL) return;

	delete (bit);
}

_Bit Bit = {
	._Setup		= _Setup,

	.Init		= Init,
	.New		= New,
	.Delete		= Delete,

	.Unpack		= Unpack,
	.GetExpr	= GetExpr,

	.Not		= Not,
	.And		= And,
	.Or			= Or,
	.Nand		= Nand,
	.Nor		= Nor,
};
