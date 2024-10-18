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
		src/utils/convert/convert_short.cpp\
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
		src/utils/convert/convert_short.cpp\
		src/utils/transfer_data/transfer_data.cpp\
		src/utils/command/command.cpp\
		src/client/connection/create_connection.cpp\
		src/client/main.cpp\
		-o build/client

todo: 
	@echo "Compiling todo..."
	@g++\
		app/todo/main.cpp\
		app/todo/actions/handle_action.cpp\
		app/todo/actions/add_todo.cpp\
		app/todo/actions/remove_todo.cpp\
		app/todo/actions/check_todo.cpp\
		app/todo/actions/print_todo.cpp\
		app/todo/commands/help.cpp\
		app/todo/commands/quit.cpp\
		app/todo/utils/trim.cpp\
		app/todo/utils/get_args.cpp\
		app/todo/utils/get_action.cpp\
		app/todo/utils/handle_prompt.cpp\
		app/todo/db/db_exec.cpp\
		app/todo/db/db_create.cpp\
		app/todo/db/db_add.cpp\
		app/todo/db/db_get.cpp\
		app/todo/db/db_remove_by_index.cpp\
		app/todo/db/db_check_todo.cpp\
		-lsqlite3 -o build/cli_todo

clean:
	@([ -d "build" ] && rm build/*) || echo "Dir 'build' doesn't exists"
