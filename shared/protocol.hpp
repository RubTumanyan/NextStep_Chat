#pragma once
#include <string>
#include "json.hpp"

using json =nlohmann::json;

enum class MessageType{
	
	// Client -> Server
	
	AUTH_REGISTER,    // -> redister a new contact
	AUTH_LOGIN,       // -> login with username and password
	AUTH_LOGOUT,      // -> just logout
        MSG_SEND,         // -> send message to user or room
	ROOM_JOIN,        // -> join to  group
	ROOM_LEAVE,       // -> leave a group
        ROOM_CREATE,      // -> create a new group
	
	// i think i can add delete gpoup or block user but than
	

	//Server -> Client
	
	AUTH_OK,           // -> login/register success
	AUTH_FAIL,         // -> login/register failed
	MSG_RECIEVE,       // -> message was send
	ROOM_JOINED,       // -> confirmed join to group
	ROOM_LEFT,         // -> confitmed leave from group
	SERVER_ERROR,      // -> error
	
        
        UNKNOWN,           // -> UNKNOWN

};	

inline std::string typeToString(MessageType t){
	switch(t){

		case MessageType::AUTH_REGISTER: return  "AUTH_REGISTER";
		case MessageType::AUTH_LOGIN:    return  "AUTH_LOGIN";
		case MessageType::AUTH_LOGOUT:   return  "AUTH_LOGOUT";
		case MessageType::MSG_SEND:      return  "MSG_SEND";
		case MessageType::ROOM_JOIN:     return  "ROOM_JOIN";
		case MessageType::ROOM_LEAVE:    return  "ROOM_LEAVE";
		case MessageType::ROOM_CREATE:   return  "ROOM_CREATE";
		case MessageType::AUTH_OK:       return  "AUTH_OK";
		case MessageType::AUTH_FAIL:     return  "AUTH_FAIL";
		case MessageType::MSG_RECIEVE:   return  "MSG_RECIEVED";
		case MessageType::ROOM_JOINED:   return  "ROOM_JOINED";
		case MessageType::ROOM_LEFT:     return  "ROOM_LEFT";
		case MessageType::SERVER_ERROR:  return  "SERVER_ERROR";
                
                dafault:                         return  "UNKNOWN";
	}
}


inline MessageType strigToType(const std::string& s){

	if(s == "AUTH_REGISTER")  return MessageType::AUTH_REGISTER;
	if(s == "AUTH_LOGIN")     return MessageType::AUTH_LOGIN;
	if(s == "AUTH_LOGOUT")    return MessageType::AUTH_LOGOUT;
	if(s == "MSG_SEND")       return MessageType::MSG_SEND;
	if(s == "ROOM_JOIN")      return MessageType::ROOM_JOIN;
	if(s == "ROOM_LEAVE")     return MessageType::ROOM_LEAVE;
	if(s == "ROOM_CREATE")    return MessageType::ROOM_CREATE;

	if (s == "AUTH_OK")      return MessageType::AUTH_OK;
        if (s == "AUTH_FAIL")    return MessageType::AUTH_FAIL;
        if (s == "MSG_RECIEVE")  return MessageType::MSG_RECIEVE;
        if (s == "ROOM_JOINED")  return MessageType::ROOM_JOINED;
        if (s == "ROOM_LEFT")    return MessageType::ROOM_LEFT;
        if (s == "SERVER_ERROR") return MessageType::SERVER_ERROR;
	
	
	return MessageType::UNKNOWN;
}
