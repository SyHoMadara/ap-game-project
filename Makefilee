CC = g++ -std=c++14
OUTPUT_DIR = .outs
LIBS_DIR = libs
BIN_DIR = bin
SRC_DIR = src
CPPFLAGS = -I$(LIBS_DIR)/


%.o: $(SRC_DIR)/%.cpp
	$(CC) $< -o $(OUTPUT_DIR)/$@ $(CPPFLAGS)

server: server.o
	$(CC) $(SRC_DIR)/$@.cpp -o $(BIN_DIR)/$@.exc $(CPPFLAGS) -lpthread

client: client.o
	make client.o
	$(CC) $(SRC_DIR)/$@.cpp -o $(BIN_DIR)/$@.exc $(CPPFLAGS)

clean:
	rm -rf $(OUTPUT_DIR)/* $(BIN_DIR)/*.exc
clear:
	make clean

start_server:
	$(BIN_DIR)/server.exc

start_client:
	$(BIN_DIR)/client.exc

dir_creator:
	mkdir .outs bin

install_server:
	make dir_creator
	make clean
	make server

install_client:
	make dir_creator
	make clean
	make client

update:
	make server
	make client
