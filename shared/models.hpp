#pragma once
#include <string>
#include "json.hpp"

using json = nlohmann::json;


//       ->   exmaple of packet   <- 
//
//   "type"    : "MSG_SEND",
//   "from"    : "alice",
//   "to"      : "bob",        // -> username for 1-on-1
//   "room"    : "",           // -> room name for group (empty if 1-on-1)
//   "body"    : "Hello!",     // -> message
//   "timestamp": 1715000000   // it's the time in seconds sice January 1 , 1970year


struct Message {
	std::string type;
	std::string from;
	std::string to;
	std::string room;
	std::string body;
	long long timestamp = 0;


	std::string toJson()const{
		json j;                  // Convert C++ into JSON
		j["type"] = type;
		j["from"] = from;
		j["to"] = to;
		j["room"] = room;
		j["body"] = body;
		j["timestamp"] = timestamp;
	
		return j.dump();
	}

        static Message fromJson(const std::string raw){

		Message m;
	        try{
			json j = json::parse(raw);
		        m.type = j.value("type" , "UNKNOWN");
			m.from = j.value("from" , "");
			m.to = j.value("to" , "");
			m.room = j.value("room" , "");
			m.body = j.value("body" ,"");
			m.timestamp = j.value("timestamp" , 0LL);
		}catch(...){
			m.type = "UNKNOWN";
			}
		return m;
	}
};

struct User{
	int id = 0;
	std::string username;
	std::string passwordHash;
};

struct Room{
	int id = 0;
        std::string name;
};

	

