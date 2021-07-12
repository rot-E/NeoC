#include "NeoC/Environment.h"
#include "NeoC/Socket.h"
#include "NeoC/Exception.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"
#include "NeoC/System.h"

void main() $_ {
	Socket_t *cli = NULL;
	Socket_t *cli2 = NULL;

	try {
		cli = Socket.NewUDPClient();
		Socket.Configure(cli, String.New(u8"localhost"), 10001);

		for (int i = 0;; i++) {
			String_t *str = String.NewFormat(u8"Hello %d.", i);
			Socket.Cast(cli, str);
			Console.WriteLine(String.NewFormat(u8"Casted: %s", String.Unpack(str)));
			System.USleep(100 * 1000);

			if (Socket.UpdateExists(cli)) {
				String_t *msg = Socket.Collect(cli);
				String_t *ip = Socket.GetDestIPAddr(cli);
				Console.WriteLine(String.NewFormat(u8"[%s, %d]> %s", String.Unpack(ip), Socket.GetDestPort(cli), String.Unpack(msg)));
			}

			if (i == 10) {
				Socket.Disconnect(cli);
				break;
			}
		}

		/* Broadcast */
		cli2 = Socket.NewUDPClient();
		Socket.ConfigureBroadcast(cli2, 10001);
		Socket.Broadcast(cli2, String.New(u8"HELO"));
		Console.WriteLine(String.New(u8"Broadcasted."));

	} catch (Socket.Exception) {
		Console.WriteErrorLine(String.New(u8"[Socket.Exception] 通信エラー"));
	} fin

	Socket.Delete(cli);
	Socket.Delete(cli2);
} _$
