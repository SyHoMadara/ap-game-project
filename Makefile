CC = g++ -std=c++14
OUTPUT_DIR = .outs
LIBS_DIR = libs
BIN_DIR = bin
SRC_DIR = src
CPPFLAGS = -I$(LIBS_DIR)/


%.o: $(SRC_DIR)/%.cpp
	$(CC) $< -o $(OUTPUT_DIR)/$(@) $(CPPFLAGS)

server: $(OUTPUT_DIR)/server.o
	make server.o
	$(CC) $(SRC_DIR)/$@.cpp -o $(BIN_DIR)/$@.exc $(CPPFLAGS) -lpthread

client: $(OUTPUT_DIR)/client.o
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

install_server:
	make clean
	make server

install_client:
	make clean
	make client

update:
	make server
	make client
