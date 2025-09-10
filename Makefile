SRC = src/MAIN.c src/commands/commands.c src/executer/executer.c src/utils/utils.c src/colors/colors.h
BIN = bin
TAR = bin/main
CC = gcc

all: $(TAR)

$(BIN):
	@echo "creating bin folder..."
	mkdir -p $(BIN)
	@touch bin/database.txt 

$(TAR): $(SRC) | $(BIN)
	@echo "compiling the program..."
	$(CC) $(SRC) -o $(TAR)

run:
	@echo "running the program..."
	./bin/main

clean:
	@echo "deleting executable files..."
	rm -rf $(BIN)
	
.PHONY: all clean run
