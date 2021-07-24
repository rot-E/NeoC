#include "NeoC/Socket.h"

method static void _Setup() {
	Socket.Exception signal;
	Socket.DisconnectionException signal;

	Socket.GetExpr	= Object.GetExpr;
	Socket.CRLF		= String.NewFormat(u8"%c%c", CC.CR, CC.LF);
}

method static int32_t GetFd(self_t *sock) {
	return act(Socket_t, sock)->_Socket;
}

method static Socket_t *Accept(self_t *sock) {
	return Socket.New(accept(act(Socket_t, sock)->_Socket, NULL, NULL));
}

method static void Send(self_t *sock, String_t *message) throws (Socket.Exception) {
	String_t *data = String.Concat(message, Socket.CRLF);
	// defer String.Delete(data);

	int32_t result = send(act(Socket_t, sock)->_Socket, String.Unpack(data), String.GetLength(data), 0);
	String.Delete(data);
	if (result == -1) throw (Signal.New(Socket.Exception));
}

method static String_t *Receive(self_t *sock) throws (Socket.Exception, Socket.DisconnectionException) {
	String_t *data = String.NewN(Socket.DATA_MAX_SIZE);
	// defer? String.Delete(data);

	int32_t result = recv(act(Socket_t, sock)->_Socket, String.Unpack(data), Socket.DATA_MAX_SIZE - 1, 0);
	if (result == 0) throw (Signal.New(Socket.DisconnectionException));
	if (result == -1) throw (Signal.New(Socket.Exception));

	if (String.EndsWith(data, Socket.CRLF)) {
		/* 区切りがCRLFの場合 */
		return String.Substring(data, 0, String.GetLength(data) + 1 - String.GetLength(Socket.CRLF));
	} else if (String.EndsWithChar(data, CC.LF)) {
		/* 区切りがLFの場合 */
		return String.DropLastChar(data);
	} else {
		String.Reduce(data);
		return data;
	}
}

method static void Disconnect(self_t *sock) {
	close(act(Socket_t, sock)->_Socket);
}

method static bool UpdateExists(self_t *sock) {
	fd_set tmp = act(Socket_t, sock)->_FDState;
	select(act(Socket_t, sock)->_Socket + 1, &tmp, NULL, NULL, &(struct timeval){ .tv_sec = 0, .tv_usec = 0 });

	return FD_ISSET(act(Socket_t, sock)->_Socket, &tmp);
}

method static void Configure(self_t *sock, String_t *host, const in_port_t port) throws (Socket.Exception) {
	// 名前解決
	struct hostent *hent = gethostbyname(String.Unpack(host));
	if (hent == NULL) throw (Signal.New(Socket.Exception));

	// 接続情報構成
	act(Socket_t, sock)->_Addr = (struct sockaddr_in *)(
		_Memory.Allocate(sizeof(struct sockaddr_in))
	);
	memset(act(Socket_t, sock)->_Addr, 0, sizeof(*act(Socket_t, sock)->_Addr));

	act(Socket_t, sock)->_Addr->sin_family		= AF_INET;
	act(Socket_t, sock)->_Addr->sin_port		= htons(port);
	memcpy((struct in_addr *)(&act(Socket_t, sock)->_Addr->sin_addr), hent->h_addr_list[0], hent->h_length);
}

method static void ConfigureBroadcast(self_t *sock, const in_port_t port) throws (Socket.Exception) {
	// 接続情報構成
	act(Socket_t, sock)->_Addr = (struct sockaddr_in *)(
		_Memory.Allocate(sizeof(struct sockaddr_in))
	);
	memset(act(Socket_t, sock)->_Addr, 0, sizeof(*act(Socket_t, sock)->_Addr));

	act(Socket_t, sock)->_Addr->sin_family			= AF_INET;
	act(Socket_t, sock)->_Addr->sin_port			= htons(port);
	act(Socket_t, sock)->_Addr->sin_addr.s_addr	= htonl(INADDR_BROADCAST);

	// ソケットの設定
	act(Socket_t, sock)->_BroadcastSwitch = 1;

	int32_t result = setsockopt(
		act(Socket_t, sock)->_Socket,
		SOL_SOCKET,
		SO_BROADCAST,
		(void *)(&act(Socket_t, sock)->_BroadcastSwitch),
		sizeof(act(Socket_t, sock)->_BroadcastSwitch)
	);
	if (result == -1) throw (Signal.New(Socket.Exception));
}

method static String_t *GetDestIPAddr(self_t *sock) {
	return String.New(inet_ntoa(act(Socket_t, sock)->_Addr->sin_addr));
}

method static in_port_t GetDestPort(self_t *sock) {
	return ntohs(act(Socket_t, sock)->_Addr->sin_port);
}

method static void Cast(self_t *sock, String_t *message) throws (Socket.Exception) {
	int32_t result = sendto(
		act(Socket_t, sock)->_Socket,
		String.Unpack(message),
		String.GetLength(message),
		0,
		(struct sockaddr *)(act(Socket_t, sock)->_Addr),
		sizeof(*act(Socket_t, sock)->_Addr)
	);
	if (result == -1) throw (Signal.New(Socket.Exception));
}

method static void Broadcast(self_t *sock, String_t *message) throws (Socket.Exception) {
	Socket.Cast(sock, message);
}

method static String_t *Collect(self_t *sock) throws (Socket.Exception) {
	String_t *str = String.NewN(Socket.DATA_MAX_SIZE);
	int32_t result = recvfrom(
		act(Socket_t, sock)->_Socket,
		String.Unpack(str),
		String.GetLength(str) - 1,
		0,
		(struct sockaddr *)(act(Socket_t, sock)->_Addr), ({
			socklen_t tmp = sizeof(*act(Socket_t, sock)->_Addr);
			&tmp;
		})
	); // 危うい？
	if (result == -1) throw (Signal.New(Socket.Exception));

	return String.ConcatChar(str, CC.NUL);
}

method static Socket_t *Init(Socket_t *sock, const int32_t socket) {
	Object.Init(act(Object_t, sock));
	act(Object_t, sock)->_Expr		= u8"(Object_t ~> Socket_t)";

	sock->_Socket					= (socket >= 3)? socket : 0;
	sock->_Addr						= NULL;
	sock->_BroadcastSwitch			= 0;

	// ソケット監視設定
	if (socket >= 3) {
		FD_ZERO(&sock->_FDState);
		FD_SET(Socket.GetFd(sock), &sock->_FDState);
	}

	sock->GetExpr					= Object.GetExpr;
	sock->GetFd						= GetFd;

	sock->Accept					= Accept;
	sock->Send						= Send;
	sock->Receive					= Receive;
	sock->Disconnect				= Disconnect;
	sock->UpdateExists				= UpdateExists;
	sock->Configure					= Configure;
	sock->ConfigureBroadcast		= ConfigureBroadcast;
	sock->GetDestIPAddr				= GetDestIPAddr;
	sock->GetDestPort				= GetDestPort;
	sock->Cast						= Cast;
	sock->Broadcast					= Broadcast;
	sock->Collect					= Collect;

	return sock;
}

method static Socket_t *New(const int32_t socket) {
	return Socket.Init(new (Socket_t), socket);
}

method static Socket_t *NewTCPClient(String_t *serverHost, const in_port_t serverPort) throws (Socket.Exception) {
	Socket_t *sock = Socket.New(-1);

	// ソケット作成
	sock->_Socket = socket(PF_INET, SOCK_STREAM, 0);
	if (sock->_Socket == -1) throw (Signal.New(Socket.Exception));

	// 名前解決
	struct hostent *hent = gethostbyname(String.Unpack(serverHost));
	if (hent == NULL) throw (Signal.New(Socket.Exception));

	// 接続情報構成
	sock->_Addr = (struct sockaddr_in *)(_Memory.Allocate(sizeof(struct sockaddr_in)));
	memset(sock->_Addr, 0, sizeof(*sock->_Addr));

	sock->_Addr->sin_family		= AF_INET;
	sock->_Addr->sin_port		= htons(serverPort);
	memcpy(&sock->_Addr->sin_addr, hent->h_addr_list[0], hent->h_length);

	// 接続
	int32_t result = connect(sock->_Socket, (struct sockaddr *)(sock->_Addr), sizeof(*sock->_Addr));
	if (result == -1) throw (Signal.New(Socket.Exception));

	// ソケット監視設定
	FD_ZERO(&sock->_FDState);
	FD_SET(Socket.GetFd(sock), &sock->_FDState);

	return sock;
}

method static Socket_t *NewTCPServer(const in_port_t listenPort) throws (Socket.Exception) {
	Socket_t *sock = Socket.New(-1);

	// 待受用ソケット作成
	sock->_Socket = socket(PF_INET, SOCK_STREAM, 0);
	if (sock->_Socket == -1) throw (Signal.New(Socket.Exception));

	// 接続情報構成
	sock->_Addr = (struct sockaddr_in *)(_Memory.Allocate(sizeof(struct sockaddr_in)));
	memset(sock->_Addr, 0, sizeof(*sock->_Addr));

	sock->_Addr->sin_family = AF_INET;
	sock->_Addr->sin_port = htons(listenPort);
	sock->_Addr->sin_addr.s_addr = htonl(INADDR_ANY);

	// 名前を付与
	int32_t result = bind(sock->_Socket, (struct sockaddr *)(sock->_Addr), sizeof(*sock->_Addr));
	if (result == -1) throw (Signal.New(Socket.Exception));

	// 待受開始
	result = listen(sock->_Socket, 5);
	if (result == -1) throw (Signal.New(Socket.Exception));

	return sock;
}

method method static Socket_t *NewUDPClient() throws (Socket.Exception) {
	Socket_t *sock = Socket.New(-1);

	// ソケット作成
	sock->_Socket = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock->_Socket == -1) throw (Signal.New(Socket.Exception));

	// ソケット監視設定
	FD_ZERO(&sock->_FDState);
	FD_SET(Socket.GetFd(sock), &sock->_FDState);

	return sock;
}

method static Socket_t *NewUDPServer(const in_port_t listenPort) throws (Socket.Exception) {
	Socket_t *sock = Socket.New(-1);

	// ソケット作成
	sock->_Socket = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock->_Socket == -1) throw (Signal.New(Socket.Exception));

	// 接続情報構成
	sock->_Addr = (struct sockaddr_in *)(_Memory.Allocate(sizeof(struct sockaddr_in)));
	memset(sock->_Addr, 0, sizeof(*sock->_Addr));

	sock->_Addr->sin_family			= AF_INET;
	sock->_Addr->sin_port			= htons(listenPort);
	sock->_Addr->sin_addr.s_addr	= htonl(INADDR_ANY);

	// 名前を付与
	int32_t result = bind(sock->_Socket, (struct sockaddr *)(sock->_Addr), sizeof(*sock->_Addr));
	if (result == -1) throw (Signal.New(Socket.Exception));

	// ソケット監視設定
	FD_ZERO(&sock->_FDState);
	FD_SET(Socket.GetFd(sock), &sock->_FDState);

	return sock;
}

method static void Delete(Socket_t *sock) {
	if (sock == NULL) return;

	_Memory.Free(sock->_Addr);
	delete (sock);
}

_Socket Socket = {
	._Setup						= _Setup,

	.DATA_MAX_SIZE				= 10000,

	.Init						= Init,
	.New						= New,
	.NewTCPClient				= NewTCPClient,
	.NewTCPServer				= NewTCPServer,
	.NewUDPClient				= NewUDPClient,
	.NewUDPServer				= NewUDPServer,
	.Delete						= Delete,

	.GetFd						= GetFd,

	.Accept						= Accept,
	.Send						= Send,
	.Receive					= Receive,
	.Disconnect					= Disconnect,

	.UpdateExists				= UpdateExists,

	.Configure					= Configure,
	.ConfigureBroadcast			= ConfigureBroadcast,

	.GetDestIPAddr				= GetDestIPAddr,
	.GetDestPort				= GetDestPort,

	.Cast						= Cast,
	.Broadcast					= Broadcast,
	.Collect					= Collect,
};
