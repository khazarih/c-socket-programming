all: clean prepare client server

prepare:
	@echo "Preparing for build"
	@mkdir ./bin

client:
	@echo "Building client"
	@gcc src/client.c -o bin/client -w

server:
	@echo "Building server"
	@gcc src/server.c -o bin/server -w

clean:
	@echo "Cleaning"
	@if [ -d "./bin" ]; then \
		rm -rf ./bin; \
	fi 