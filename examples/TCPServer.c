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
		Console.WriteLine(String.New("[Accepted]"));
		Console.NewLine();

		for (;;) {
			if (Socket.UpdateExists(svr)) {
				String_t *msg = Socket.Receive(svr);
				Console.WriteLine(String.NewFormat("[Client]> %s", String.Unpack(msg)));

				String_t *str = String.NewFormat("Received: <%s>", String.Unpack(msg));
				Socket.Send(svr, str);
				Console.WriteLine(String.NewFormat("[Server]> %s", String.Unpack(str)));

				String.Delete(msg);
				String.Delete(str);
			}
		}
	} catch (Socket.Exception) {
		Console.WriteErrorLine(String.New("[Socket.Exception] 通信エラー"));
	} catchN (Socket.DisconnectionException) {
		Console.WriteErrorLine(String.New("[Socket.DisconnectionException] 切断されました"));
	} finally {
		Socket.Delete(svr);
		Socket.Delete(listener);
	} end
} _$
