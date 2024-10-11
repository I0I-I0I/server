all: create server client

create:
	@([ ! -d "build" ] && mkdir build) && echo "Dir 'build' was created" || echo -n ""

run_server: server
	@./build/server && echo "Running server\n"

run_client: client
	@./build/client e "print" && echo "Running client\n"

server:
	@echo "Compiling server..."
	@g++\
		src/server/main.cpp\
		src/utils/addr/get_addr.cpp\
		src/utils/hex/to_hex.cpp\
		src/utils/hex/from_hex.cpp\
		src/utils/packet/packet.cpp\
		src/utils/transfer_data/transfer_data.cpp\
		src/utils/command/command.cpp\
		src/server/server/launch_server.cpp\
		src/server/server/create_server.cpp\
		src/server/server/chating.cpp\
		-o build/server

client:
	@echo "Compiling client..."
	@g++\
		src/utils/addr/get_addr.cpp\
		src/utils/packet/packet.cpp\
		src/utils/hex/to_hex.cpp\
		src/utils/hex/from_hex.cpp\
		src/utils/transfer_data/transfer_data.cpp\
		src/utils/command/command.cpp\
		src/client/connection/create_connection.cpp\
		src/client/main.cpp\
		-o build/client

clean:
	@([ -d "build" ] && rm build/*) || echo "Dir 'build' doesn't exists"
