all: create server client

create:
	@([ ! -d "build" ] && mkdir build) && echo "Dir 'build' was created" || echo -n ""

run_server: server
	@./build/server && echo "Server is running\n"

run_client: client
	@./build/client e "print" && echo "Run client\n"

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

todo: 
	@echo "Compiling todo..."
	@g++\
		src/todo/main.cpp\
		src/todo/actions/handle_action.cpp\
		src/todo/actions/add_todo.cpp\
		src/todo/actions/remove_todo.cpp\
		src/todo/actions/check_todo.cpp\
		src/todo/actions/print_todo.cpp\
		src/todo/commands/help.cpp\
		src/todo/commands/quit.cpp\
		src/todo/utils/trim.cpp\
		src/todo/utils/get_args.cpp\
		src/todo/utils/get_action.cpp\
		src/todo/utils/handle_prompt.cpp\
		src/todo/db/db_exec.cpp\
		src/todo/db/db_create.cpp\
		src/todo/db/db_add.cpp\
		src/todo/db/db_get.cpp\
		src/todo/db/db_remove_by_index.cpp\
		src/todo/db/db_check_todo.cpp\
		-lsqlite3 -o build/cli_todo

clean:
	@([ -d "build" ] && rm build/*) || echo "Dir 'build' doesn't exists"
