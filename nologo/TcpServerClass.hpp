
#ifndef TCPSERVERCLASS_HPP_INCLUDED
#define TCPSERVERCLASS_HPP_INCLUDED

#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

class TcpServer{

	private:
		int listenSock;
		int communicationSock;
		sockaddr_in servAddr;
		sockaddr_in clntAddr;
	public:
		TcpServer(int listen_port);
		bool isAccept();
		void handleEcho();
};


#endif
