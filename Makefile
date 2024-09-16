all: main server

main:
	mkdir db || echo ""
	mkdir build || echo ""

server: server
	g++\
		src/server.cpp\
		src/utils/get_addr.cpp\
		src/utils/launch_server.cpp\
		src/utils/start_server.cpp\
		 -o build/server

clean:
	rm build/* || echo ""
