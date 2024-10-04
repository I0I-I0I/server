all: create server

create:
	@([ ! -d "build" ] && mkdir build) && echo "Dir 'build' was created" || echo -n ""

server:
	@echo "Compiling..."
	@g++\
		src/server.cpp\
		src/utils/get_addr.cpp\
		src/utils/launch_server.cpp\
		src/utils/start_server.cpp\
		-o build/server

clean:
	@([ -d "build" ] && rm build/*) || echo "Dir 'build' doesn't exists"
