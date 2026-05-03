add_executable(nextstep_server 
	src/main.cpp
	src/server.cpp
	src/session.cpp
	src/auth.cpp
	src/chat.cpp
	src/database.cpp
	)

target_include_directories(nextstep_server PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/shared
	)

target_link_libraries(nextstep_server PRIVATE
	pthread
	sqlite3
) 
