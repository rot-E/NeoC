#include "NeoC/NeoC.h"

void main() $_ {
	Socket_t *svr = Socket.NewUDPServer(10001);

	for (;;)
		if (Socket.UpdateExists(svr))
			Socket.Cast(svr, Socket.Collect(svr));
} _$
