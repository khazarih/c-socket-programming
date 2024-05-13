all: clean prepare client server

prepare:
	@echo "Preparing for build"
	@mkdir ./bin
	@mkdir ./bin/simple-server-client

client:
	@echo "Building client"
	@gcc src/simple-server-client/client.c -o bin/simple-server-client/client -w

server:
	@echo "Building server"
	@gcc src/simple-server-client/server.c -o bin/simple-server-client/server -w

clean:
	@echo "Cleaning"
	@if [ -d "./bin" ]; then \
		rm -rf ./bin; \
	fi 