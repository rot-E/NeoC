#include "NeoC/Environment.h"
#include "NeoC/Socket.h"
#include "NeoC/Exception.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"
#include "NeoC/System.h"

#include "NeoC/Debug.h"

void main() $_ {
	Socket_t *cli = NULL;

	try {
		cli = Socket.NewTCPClient(String.New("localhost"), 10001);

		for (int32_t i = 0;; i++) {
			String_t *str = String.NewFormat("Hello %d.", i);
			Socket.Send(cli, str);
			Console.WriteLine(String.NewFormat("[Client]> %s", String.Unpack(str)));

			System.USleep(100 * 1000);

			if (Socket.UpdateExists(cli)) {
				String_t *msg = Socket.Receive(cli);
				Console.WriteLine(String.NewFormat("[Server]> %s", String.Unpack(msg)));
			}

			if (i == 10) {
				Socket.Disconnect(cli);
				break;
			}
		}
	} catch (Socket.Exception) {
		Console.WriteErrorLine(String.New("[Socket.Exception] 通信エラー"));
	} catchN (Socket.DisconnectionException) {
		Console.WriteErrorLine(String.New("[Socket.DisconnectionException] 切断されました"));
	} finally {
		Socket.Delete(cli);
	} end
} _$
