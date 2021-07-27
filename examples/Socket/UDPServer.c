#include <NeoC/Base/Exception/Exception.h>
#include <NeoC/Base/Environment.h>
#include <NeoC/String.h>
#include <NeoC/Console.h>
#include <NeoC/Socket.h>

void main() $_ {
	Socket_t *svr = NULL;

	try {
		svr = Socket.NewUDPServer(10001);

		for (;;) {
			if (Socket.UpdateExists(svr)) {
				String_t *msg = Socket.Collect(svr);
				Console.WriteLine(
					String.NewFormat(
						u8"[%s, %d]> %s",
						({
							String_t *ip = Socket.GetDestIPAddr(svr);
							String.Unpack(ip);
						}),
						Socket.GetDestPort(svr),
						String.Unpack(msg)
					)
				);
				Socket.Cast(svr, String.New(u8"Received."));
			}
		}
	} catch (Socket.Exception) {
		Console.WriteErrorLine(String.New(u8"[Socket.Exception] 通信エラー"));
	} fin

	Socket.Delete(svr);
} _$
