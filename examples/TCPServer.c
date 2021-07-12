#include "NeoC/Environment.h"
#include "NeoC/Socket.h"
#include "NeoC/Exception.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"

void main() $_ {
	Socket_t *listener	= NULL;
	Socket_t *svr		= NULL;

	try {
		listener = Socket.NewTCPServer(10001);
		svr = Socket.Accept(listener);
		Console.WriteLine(String.New(u8"[Accepted]"));
		Console.NewLine();

		for (;;) {
			if (Socket.UpdateExists(svr)) {
				String_t *msg = Socket.Receive(svr);
				Console.WriteLine(String.NewFormat(u8"[Client]> %s", String.Unpack(msg)));

				String_t *str = String.NewFormat(u8"Received: <%s>", String.Unpack(msg));
				Socket.Send(svr, str);
				Console.WriteLine(String.NewFormat(u8"[Server]> %s", String.Unpack(str)));

				String.Delete(msg);
				String.Delete(str);
			}
		}
	} catch (Socket.Exception) {
		Console.WriteErrorLine(String.New(u8"[Socket.Exception] 通信エラー"));
	} catchN (Socket.DisconnectionException) {
		Console.WriteErrorLine(String.New(u8"[Socket.DisconnectionException] 切断されました"));
	} finally {
		Socket.Delete(svr);
		Socket.Delete(listener);
	} end
} _$
