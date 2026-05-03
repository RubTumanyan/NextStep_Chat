#include "server.h"
#include <iostream>

int main(){
	try{
		Server server(9090);
		server.run();
	}catch(const std::exception& e){
		std::cerr<< "Failed " << e.what() << "\n";
		return 1;
	}
	return 0;
}
