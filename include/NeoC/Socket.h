#pragma once

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#include "NeoC/Annotation.h"
#include "NeoC/Object.h"
#include "NeoC/Memory.h"
#include "NeoC/Exception/Signal.h"
#include "NeoC/Exception/Exception.h"
#include "NeoC/Defer.h"
#include "NeoC/String.h"

class Socket_t {
	private int32_t _Socket;
	private fd_set _FDState;
	private struct sockaddr_in *_Addr;
	private int32_t _BroadcastSwitch;

	public int32_t (* GetFd)(struct Socket_t *);

	/* TCP */
	public struct Socket_t *(* Accept)(struct Socket_t *);

	public void (* Send)(struct Socket_t *, String_t *message) throws (Socket.Exception);
	public String_t *(* Receive)(struct Socket_t *) throws (Socket.Exception, Socket.DisconnectionException);

	public void (* Disconnect)(struct Socket_t *);

	/* 共通 */
	public bool (* UpdateExists)(struct Socket_t *);

	/* UDP */
	public void (* Configure)(struct Socket_t *, String_t *serverHost, const in_port_t serverPort) throws (Socket.Exception);
	public void (* ConfigureBroadcast)(struct Socket_t *, const in_port_t serverPort) throws (Socket.Exception);

	public String_t *(* GetDestIPAddr)(struct Socket_t *);
	public in_port_t (* GetDestPort)(struct Socket_t *);

	public void (* Cast)(struct Socket_t *, String_t *message) throws (Socket.Exception);
	public void (* Broadcast)(struct Socket_t *, String_t *message) throws (Socket.Exception);
	public String_t *(* Collect)(struct Socket_t *) throws (Socket.Exception);
} Socket_t;

class _Socket {
	private void (* _Setup)();

	public final SignalCode_t Exception;
	public final SignalCode_t DisconnectionException;

	public final String_t *CRLF;
	protected final int32_t DATA_MAX_SIZE;

	// TODO: 内部の処理の共通化
	public Socket_t *(* New)(const int32_t socket);
	public Socket_t *(* NewTCPClient)(String_t *serverHost, const in_port_t serverPort) throws (Socket.Exception);
	public Socket_t *(* NewTCPServer)(const in_port_t listenPort) throws (Socket.Exception);
	public Socket_t *(* NewUDPClient)() throws (Socket.Exception);
	public Socket_t *(* NewUDPServer)(const in_port_t listenPort) throws (Socket.Exception);
	public void (* Delete)(Socket_t *);

	public int32_t (* GetFd)(Socket_t *);

	/* TCP */
	public Socket_t *(* Accept)(Socket_t *);

	public void (* Send)(Socket_t *, String_t *message) throws (Socket.Exception);
	public String_t *(* Receive)(Socket_t *) throws (Socket.Exception, Socket.DisconnectionException);

	public void (* Disconnect)(Socket_t *);

	/* 共通 */
	public bool (* UpdateExists)(Socket_t *);

	/* UDP */
	public void (* Configure)(Socket_t *, String_t *serverHost, const in_port_t serverPort) throws (Socket.Exception);
	public void (* ConfigureBroadcast)(Socket_t *, const in_port_t serverPort) throws (Socket.Exception);

	public String_t *(* GetDestIPAddr)(Socket_t *);
	public in_port_t (* GetDestPort)(Socket_t *);

	public void (* Cast)(Socket_t *, String_t *message) throws (Socket.Exception);
	public void (* Broadcast)(Socket_t *, String_t *message) throws (Socket.Exception);
	public String_t *(* Collect)(Socket_t *) throws (Socket.Exception);
} _Socket;

extern _Socket Socket;
