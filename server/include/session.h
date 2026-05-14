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
        const std::string& username() const { return username_; }
	SessionState state() const { return state_; }
	bool isLoggedIn() const { return state_ == SessionState::LOGGED_IN; }

	void login(int userId ,const std::string& username);
	void logout();

	void joinRoom(const std::string& room);
	void leaveRoom(const std::string& room);
	bool isInRoom(const std::string& room) const;

	const std::unordered_set<std::string>& rooms()const { return rooms_; }


private:
	int fd_;
	int userId_ = -1;
	std::string username_;
	SessionState state_ = SessionState::CONNECTED;
	std::unordered_set<std::string> rooms_;
};
