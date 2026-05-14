#pragma once
#include <sys/epoll.h>
#include <string>
#include <unordered_map>
#include "Session.h"
#include <memory>

class Server{
public:
	Server(int port);
	~Server();

	void run();
private:
	void setupSocket();
	void handleNewConnection();
	void handleClientData(int clientFd);
	void disconnectClient(int clientFd);

	int port_;
	int serverFd_;
	int epollFd_;

	std::unordered_map<int,std::shared_ptr<Session>> sessions_;

	static const int MAX_EVENTS = 64;
	static const int BUFFER_SIZE = 4096;
};
