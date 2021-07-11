#pragma once

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#include "Memory.h"
#include "Exception.h"
#include "Defer.h"
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
	public Socket_t *(* New)(const int32_t socket);
	public Socket_t *(* NewTCPClient)(String_t *serverHost, const in_port_t serverPort) throws (Socket.Exception);
	public Socket_t *(* NewTCPServer)(const in_port_t listenPort) throws (Socket.Exception);
	public Socket_t *(* NewUDPClient)() throws (Socket.Exception);
	public Socket_t *(* NewUDPServer)(const in_port_t listenPort) throws (Socket.Exception);
	public void (* Delete)(Socket_t *);

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
