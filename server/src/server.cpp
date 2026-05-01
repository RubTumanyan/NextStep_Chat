#include "server.h"
#include <iostream>
#include <stdexcept>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

Server::Server(int port) : port_(port) , serverFd_(-1) , epollFd(-1){
	setupSocket();
}

Server::~Server() {
	if(serverFd != -1) close(serverFd_);
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


	if (bind(serverFd_ , (sockaddr*)&addr , sizepf(addr)) < 0 )
		throw std::runtime_error("Failed to bind");

	if(listen(ServerFd_ , 10) < 0) 
		throw std::runtime_error("Failed to lieten");



	
