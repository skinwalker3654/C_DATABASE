SRC = src/main.c src/commands/database.c src/executer.c src/utils/utils.c
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
