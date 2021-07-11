#include "NeoC/Environment.h"
#include "NeoC/Socket.h"
#include "NeoC/Exception.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"


void main() $_ {
	Socket_t *svr = NULL;

	try {
		svr = Socket.NewUDPServer(10001);

		for (;;) {
			if (Socket.UpdateExists(svr)) {
				String_t *msg = Socket.Collect(svr);
				Console.WriteLine(
					String.NewFormat(
						"[%s, %d]> %s",
						({
							String_t *ip = Socket.GetDestIPAddr(svr);
							String.Unpack(ip);
						}),
						Socket.GetDestPort(svr),
						String.Unpack(msg)
					)
				);
				Socket.Cast(svr, String.New("Received."));
			}
		}
	} catch (Socket.Exception) {
		Console.WriteErrorLine(String.New("[Socket.Exception] 通信エラー"));
	} fin

	Socket.Delete(svr);
} _$
