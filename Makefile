SRC = src/MAIN.c src/commands/commands.c src/executer/executer.c src/utils/utils.c src/storage/storage.c
BIN = bin
TAR = $(BIN)/main
CC = gcc
GDB = gdb

all: $(TAR)

$(BIN):
	@echo "creating bin folder..."
	mkdir -p $(BIN)

$(TAR): $(SRC) | $(BIN)
	@echo "compiling the program..."
	$(CC) $(SRC) -o $(TAR) 

run:
	@echo "running the program..."
	./bin/main

debug: $(SRC) | $(BIN)
	@echo "Compiling the program with -g flag..."
	$(CC) $(SRC) -o $(TAR) -g

rundebug: $(TAR)
	@echo "Running the program in debug mode"
	gdb ./$(TAR)

clean:
	@echo "deleting executable files..."
	rm -rf $(BIN)
	
.PHONY: all clean run
