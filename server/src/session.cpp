#include "session.h"
#include <iostream>

Session::Session(int fd): fd_(fd) {
	std::cout << "[Session] created for fd " << fd << "\n";
}


void Session::login(int userId , const std::string& username){
	userId_ = userId;
	username_ = username;
	state_ = SessionState::LOGGED_IN;
	std::cout << "[Session] fd= " << fd_ << " logged in as " << username<<"\n";
}

void Session::logout(){
	userId_ = -1;
	username_ = "";
	state_ = SessionState::CONNECTED;
	rooms_.clear();
	std::cout << " [Session] fd = " << fd_ << " logged_out" << "\n";
}

void Session::joinRoom(const std::string& room) {
	rooms_.insert(room);
	std::cout << "[Session] " << username_ << " joined room " << room <<  "\n";
}

void Session::leaveRoom(const std::string& room) {
	rooms_.erase(room);
	std::cout << "[Session] " << username_ << " left room " << room << "\n";
}

bool Session::isInRoom(const std::string& room) const {
	return rooms_.count(room) > 0;
}
