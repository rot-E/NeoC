#include "NeoC/Base/Environment.h"
#include "NeoC/Socket.h"

void main() $_ {
	Socket_t *listener = Socket.NewTCPServer(10001);
	Socket_t *svr = Socket.Accept(listener);

	for (;;)
		if (Socket.UpdateExists(svr))
			Socket.Send(svr, Socket.Receive(svr));
} _$
