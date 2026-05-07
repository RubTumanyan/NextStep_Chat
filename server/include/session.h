#pragma once
#include <string>
#include <unordered_set>

enum class SessionState{
	CONNECTED,
        LOGGED_IN
};

class Session{
	
public:
	explicit Session(int fd);

	int fd() const { return fd_; }
        int userId() const { return userId_; }
        std::string username() const { return username_; }
	SessionState state() const { return state_; }
	bool isLoggedIn() const { return state_ == SessionState::LOGGED_IN; }

	void login(int userId , std::string& username);
	void logout();

	void joinRoom(std::string& room);
	void leaveRoom(std::string& room);
	bool inRoom(std::string& room) const;

	const std::unordered_set<std::string>& rooms()const { return rooms_; }


private:
	int fd_;
	int userId_ = -1;
	std::string username_;
	SessionState state_ = SessionState::CONNECTED;
	std::unordered_set<std::string> rooms_;
};
