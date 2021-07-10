#pragma once

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#include "Setup.h"
#include "Exception.h"
#include "String.h"

typedef struct {
	private int32_t _Socket;
	private fd_set _FDState;
	private struct sockaddr_in *_Addr;
	private int32_t _BroadcastSwitch;
} Socket_t;

typedef struct {
	private void (* _Setup)();

	public final int32_t Exception;
	public final int32_t DisconnectionException;

	public final String_t *CRLF;
	protected final int32_t DATA_MAX_SIZE;

	// TODO: 内部の処理の共通化
	Socket_t *(* New)(const int32_t socket);
	Socket_t (* NewTCPClient)(String_t *serverHost, const in_port_t serverPort) throws (Socket.Exception);
	Socket_t (* NewTCPServer)(const in_port_t listenPort) throws (Socket.Exception);
	Socket_t (* NewUDPClient)() throws (Socket.Exception);
	Socket_t (* NewUDPServer)(const in_port_t listenPort) throws (Socket.Exception);
	void (* Delete)(Socket_t *);

	/* TCP */
	Socket_t *(* Accept)(struct Socket_t *);

	E (* Send)(struct Socket_t *, String_t *message) throws (Socket.Exception);
	String_t_E (* Receive)(struct Socket_t *);

	void (* Disconnect)(struct Socket_t *);

	/* 共通 */
	bool (* UpdateExists)(struct Socket_t *);

	/* UDP */
	E (* Configure)(struct Socket_t *, String_t *serverHost, const in_port_t serverPort);
	E (* ConfigureBroadcast)(struct Socket_t *, const in_port_t serverPort);

	String_t *(* GetDestIPAddr)(struct Socket_t *);
	in_port_t (* GetDestPort)(struct Socket_t *);

	E (* Cast)(struct Socket_t *, String_t *message);
	E (* Broadcast)(struct Socket_t *, String_t *message);
	String_t_E (* Collect)(struct Socket_t *);
} _Socket;

extern _Socket Socket;
