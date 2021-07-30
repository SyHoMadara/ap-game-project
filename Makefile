CC = g++ -std=c++14
CPPFLAGS = -I./libs
OUTPUT_DIR = ./.outs

%.o: %.cpp
	$(CC) $< -o $(OUTPUT_DIR)/$(@) $(CPPFLAGS)

main: main.o
	$(CC) main.cpp -o $(@) $(CPPFLAGS)

start:
	./main