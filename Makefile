all: create server client

create:
	@([ ! -d "build" ] && mkdir build) && echo "Dir 'build' was created" || echo -n ""

server:
	@echo "Compiling server..."
	@g++\
		src/server/main.cpp\
		src/server/utils/get_addr.cpp\
		src/server/utils/launch_server.cpp\
		src/server/utils/create_server.cpp\
		-o build/server

client:
	@echo "Compiling client..."
	@g++\
		src/client/main.cpp\
		-o build/client

clean:
	@([ -d "build" ] && rm build/*) || echo "Dir 'build' doesn't exists"
