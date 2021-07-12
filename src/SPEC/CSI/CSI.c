#include "CSI.h"

static void _Setup() {
	CSI.RuntimeException signal;
}

static uint8_t *CUU(const int32_t n) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dA", CC.ESC, n);
	return seq;
}

static uint8_t *CUD(const int32_t n) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dB", CC.ESC, n);
	return seq;
}

static uint8_t *CUF(const int32_t n) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dC", CC.ESC, n);
	return seq;
}

static uint8_t *CUB(const int32_t n) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dD", CC.ESC, n);
	return seq;
}

static uint8_t *CNL(const int32_t n) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dE", CC.ESC, n);
	return seq;
}

static uint8_t *CPL(const int32_t n) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dF", CC.ESC, n);
	return seq;
}

static uint8_t *CHA(const int32_t n) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dG", CC.ESC, n);
	return seq;
}

static uint8_t *CUP(const int32_t n, const int32_t m) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%d;%dH", CC.ESC, n, m);
	return seq;
}

static uint8_t *CHT(const int32_t n) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dI", CC.ESC, n);
	return seq;
}

static uint8_t *CBT(const int32_t n) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dZ", CC.ESC, n);
	return seq;
}

static uint8_t *ED(const int32_t n) {
	if (n < 0 || 3 < n) throw (CSI.RuntimeException);

	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dJ", CC.ESC, n);
	return seq;
}

static uint8_t *EL(const int32_t n) {
	if (n < 0 || 2 < n) throw (CSI.RuntimeException);

	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dK", CC.ESC, n);
	return seq;
}

static uint8_t *ECH(const int32_t n) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dX", CC.ESC, n);
	return seq;
}

static uint8_t *DCH(const int32_t n) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dP", CC.ESC, n);
	return seq;
}

static uint8_t *IL(const int32_t n) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dL", CC.ESC, n);
	return seq;
}

static uint8_t *DL(const int32_t n) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dM", CC.ESC, n);
	return seq;
}

static uint8_t *TBC(const int32_t n) {
	// throw

	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dg", CC.ESC, n);
	return seq;
}

static uint8_t *DECSTBM(const int32_t n, const int32_t m) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%d;%dr", CC.ESC, n, m);
	return seq;
}

static uint8_t *SU(const int32_t n) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dS", CC.ESC, n);
	return seq;
}

static uint8_t *SD(const int32_t n) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dT", CC.ESC, n);
	return seq;
}

static uint8_t *REP(const int32_t n) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%db", CC.ESC, n);
	return seq;
}

static uint8_t *DSR(const int32_t n) {
	// throw

	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dn", CC.ESC, n);
	return seq;
}

static uint8_t *DECTCEM(const uint8_t code) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[?25%c", CC.ESC, code);
	return seq;
}

static uint8_t *GenerateSGR(const int32_t code) {
	uint8_t *seq = (uint8_t *)(_Memory.CountedAllocate(CSI._ESCAPE_SEQUENCE_LEMGTH_MAX, sizeof(uint8_t)));
	sprintf(seq, u8"%c[%dm", CC.ESC, code);
	return seq;
}

_CSI CSI = {
	._Setup								= _Setup,

	._ESCAPE_SEQUENCE_LEMGTH_MAX		= 100,

	.CUU								= CUU,
	.CUD								= CUD,
	.CUF								= CUF,
	.CUB								= CUB,
	.CNL								= CNL,
	.CPL								= CPL,
	.CHA								= CHA,
	.CUP								= CUP,
	.CHT								= CHT,
	.CBT								= CBT,
	.ED									= ED,
	.EL									= EL,
	.ECH								= ECH,
	.DCH								= DCH,
	.IL									= IL,
	.DL									= DL,
	.TBC								= TBC,
	.DECSTBM							= DECSTBM,
	.SU									= SU,
	.SD									= SD,
	.REP								= REP,
	.DSR								= DSR,
	.DECTCEM							= DECTCEM,

	.GenerateSGR						= GenerateSGR,
};
