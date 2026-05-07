#include "server.h"
#include <iostream>
#include <stdexcept>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "protocol.hpp"
#include "models.hpp"

Server::Server(int port) : port_(port) , serverFd_(-1) , epollFd_(-1){
	setupSocket();
}



Server::~Server() {
	if(serverFd_ != -1) close(serverFd_);
	if(epollFd_ != -1) close(epollFd_);

}



void Server::setupSocket(){
	serverFd_ = socket(AF_INET , SOCK_STREAM , 0);
	if(serverFd_ < 0) {
		throw std::runtime_error("Failed to create socket");
        }

	int opt = 1;
	setsockopt(serverFd_ , SOL_SOCKET , SO_REUSEADDR , &opt , sizeof(opt));

	sockaddr_in addr{};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port_);
	addr.sin_addr.s_addr = INADDR_ANY;


	if (bind(serverFd_ , (sockaddr*)&addr , sizeof(addr)) < 0 )

		throw std::runtime_error("Failed to bind");

	if(listen(serverFd_ , 10) < 0) 
		throw std::runtime_error("Failed to lieten");

	epollFd_ = epoll_create1(0);
	if(epollFd_ < 0)
		throw std::runtime_error("Failed to create epoll");

	epoll_event ev{};
	ev.events = EPOLLIN;
	ev.data.fd = serverFd_;
	epoll_ctl(epollFd_ , EPOLL_CTL_ADD , serverFd_ , &ev);

	std::cout << "[Server] Litening on port " << port_ << "\n";
}




void Server::run() {
    epoll_event events[MAX_EVENTS];
    std::cout << "[Server] Event loop started\n";

    while (true) {
        int nEvents = epoll_wait(epollFd_, events, MAX_EVENTS, -1);
        if (nEvents < 0) {
            std::cerr << "[Server] epoll_wait error\n";
            break;
        }

        for (int i = 0; i < nEvents; i++) {
            int fd = events[i].data.fd;

            if (fd == serverFd_)
                handleNewConnection();
            else
                handleClientData(fd);
        }
    }
}



void Server::handleNewConnection(){
	sockaddr_in clientAddr{};
	socklen_t len = sizeof(clientAddr);

	int clientFd = accept(serverFd_ , (sockaddr*)&clientAddr , &len);

	if(clientFd < 0){
		std::cerr<<"Failed to accept the new connection(cleint)" << std::endl;
		return;
	}
	epoll_event ev{};
	ev.events = EPOLLIN;
	ev.data.fd = clientFd;

	epoll_ctl(epollFd_ , EPOLL_CTL_ADD , clientFd , &ev);
        clients_[clientFd] = "";
	std::cout << "[Server] new connection client fd : " << clientFd << "\n";
}



void Server::handleClientData(int clientFd){
	char buffer[BUFFER_SIZE];
	memset(buffer ,  0 , BUFFER_SIZE);

	int bytesRead = recv(clientFd , buffer , BUFFER_SIZE - 1 , 0);
	if(bytesRead <= 0){
		disconnectClient(clientFd);
		return;
	}

	std::string raw(buffer, bytesRead);

	Message msg = Message::fromJson(raw);
	MessageType type = stringToType(msg.type);

	std::cout << "[fd = "<< clientFd << "] type = " << msg.type <<"from = " << msg.from << "\n";

	switch(type) {
		case MessageType::AUTH_LOGIN:
		case MessageType::AUTH_REGISTER: {
			Message response;
			response.type = typeToString(MessageType::AUTH_OK);
			response.body = "Welcome " + msg.from;
		        std::string resp = response.toJson();
		        send(clientFd , resp.c_str() , resp.size() , 0);
			break;
		}
                
		default: {
			Message response;
			response.type = typeToString(MessageType::SERVER_ERROR);
			response.body = "UNKNOWN MESSAGE TYPE";
		        std::string resp = response.toJson();
		        send(clientFd , resp.c_str(), resp.size() , 0);
		        break;
	        }
	}	 
}



void Server::disconnectClient(int clientFd){

        std::cout << "[Server] CLient fd : " << clientFd << "disconnect\n";
	epoll_ctl(epollFd_ , EPOLL_CTL_DEL , clientFd , nullptr);
	close(clientFd);
	clients_.erase(clientFd);
}
