CC = g++ -std=c++14
OUTPUT_DIR = ./.outs
LIBS_DIR = ./libs
BIN_DIR = ./bin
CPPFLAGS = -I.$(LIBS_DIR)


%.o: %.cpp
	$(CC) $< -o $(OUTPUT_DIR)/$(@) $(CPPFLAGS)

server: server.cpp
	$(CC) $@.cpp -o $(BIN_DIR)/$@.exc $(CPPFLAGS) -lpthread

client: client.cpp
	$(CC) $@.cpp -o $(BIN_DIR)/$@.exc $(CPPFLAGS)

clean:
	rm -rf .outs/* $(BIN_DIR)/*.exc
clear:
	make clean

start_server:
	$(BIN_DIR)/server.exc

start_client:
	$(BIN_DIR)/client.exc

install_server:
	make clean
	make server

install_client:
	make clean
	make client