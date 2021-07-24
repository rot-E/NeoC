#pragma once

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include "NeoC/Base/Object.h"
#include "NeoC/Base/Memory.h"
#include "NeoC/Base/Exception/Signal.h"
#include "NeoC/Base/Exception/Exception.h"
#include "NeoC/Base/Defer.h"
#include "NeoC/String.h"

class Socket_t {
	extends (Object_t);

	private int32_t _Socket;
	private fd_set _FDState;
	private struct sockaddr_in *_Addr;
	private int32_t _BroadcastSwitch;

	public inherit uint8_t *(* GetExpr)(self_t *);
	public int32_t (* GetFd)(self_t *);

	/* TCP */
	public struct Socket_t *(* Accept)(self_t *);

	public void (* Send)(self_t *, String_t *message) throws (Socket.Exception);
	public String_t *(* Receive)(self_t *) throws (Socket.Exception, Socket.DisconnectionException);

	public void (* Disconnect)(self_t *);

	/* 共通 */
	public bool (* UpdateExists)(self_t *);

	/* UDP */
	public void (* Configure)(self_t *, String_t *serverHost, const in_port_t serverPort) throws (Socket.Exception);
	public void (* ConfigureBroadcast)(self_t *, const in_port_t serverPort) throws (Socket.Exception);

	public String_t *(* GetDestIPAddr)(self_t *);
	public in_port_t (* GetDestPort)(self_t *);

	public void (* Cast)(self_t *, String_t *message) throws (Socket.Exception);
	public void (* Broadcast)(self_t *, String_t *message) throws (Socket.Exception);
	public String_t *(* Collect)(self_t *) throws (Socket.Exception);
} Socket_t;

class _Socket {
	private void (* _Setup)();

	public final SignalCode_t Exception;
	public final SignalCode_t DisconnectionException;

	public final String_t *CRLF;
	protected final int32_t DATA_MAX_SIZE;

	// TODO: 内部の処理の共通化
	public Socket_t *(* Init)(Socket_t *, const int32_t socket);
	public Socket_t *(* New)(const int32_t socket);
	public Socket_t *(* NewTCPClient)(String_t *serverHost, const in_port_t serverPort) throws (Socket.Exception);
	public Socket_t *(* NewTCPServer)(const in_port_t listenPort) throws (Socket.Exception);
	public Socket_t *(* NewUDPClient)() throws (Socket.Exception);
	public Socket_t *(* NewUDPServer)(const in_port_t listenPort) throws (Socket.Exception);
	public void (* Delete)(Socket_t *);

	public inherit uint8_t *(* GetExpr)(self_t *);
	public int32_t (* GetFd)(self_t *);

	/* TCP */
	public Socket_t *(* Accept)(self_t *);

	public void (* Send)(self_t *, String_t *message) throws (Socket.Exception);
	public String_t *(* Receive)(self_t *) throws (Socket.Exception, Socket.DisconnectionException);

	public void (* Disconnect)(self_t *);

	/* 共通 */
	public bool (* UpdateExists)(self_t *);

	/* UDP */
	public void (* Configure)(self_t *, String_t *serverHost, const in_port_t serverPort) throws (Socket.Exception);
	public void (* ConfigureBroadcast)(self_t *, const in_port_t serverPort) throws (Socket.Exception);

	public String_t *(* GetDestIPAddr)(self_t *);
	public in_port_t (* GetDestPort)(self_t *);

	public void (* Cast)(self_t *, String_t *message) throws (Socket.Exception);
	public void (* Broadcast)(self_t *, String_t *message) throws (Socket.Exception);
	public String_t *(* Collect)(self_t *) throws (Socket.Exception);
} _Socket;

extern _Socket Socket;
