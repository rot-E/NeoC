#pragma once

/* ------------------------------------------------------ */
#define in(...)

#define Comparator(X, Y, EqEvaFm)			\
	({										\
		bool _cmptr(void *X, void *Y) {		\
			return EqEvaFm;					\
		};									\
		_cmptr;								\
	})
/* ------------------------------------------------------ */
