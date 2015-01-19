BIN := e-text

all: $(BIN)
.PHONY: all

$(BIN): main.c
	gcc -o $(BIN) main.c -lncurses

run:
	./$(BIN)
clean:
	rm $(BIN)
.PHONY: clean run

