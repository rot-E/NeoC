#pragma once

/* ------------------------------------------------------ */
#define T(T) sizeof(T)

#define TT(KT, VT) sizeof(KT), sizeof(VT)

#define Comparator(X, Y, EqEvaFm)			\
	({										\
		bool _cmptr(void *X, void *Y) {		\
			return EqEvaFm;					\
		};									\
		_cmptr;								\
	})
/* ------------------------------------------------------ */
