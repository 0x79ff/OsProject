# myFS

CC = g++
CFLAGS = -w -g -m32
#CFLAGS = -w -g
BIN_DIR = bin
BIN = $(BIN_DIR)/myFS
SRCS = $(wildcard src/*.cpp)
OBJS = $(addprefix $(BIN_DIR)/, $(notdir $(SRCS:.cpp=.o)))

$(BIN): $(OBJS)
	$(CC) -m32 -o $@ $^
#	$(CC) -o $@ $^

# -del /Q $(BIN_DIR)\*.o

$(BIN_DIR)/%.o: src/%.cpp | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR):
	mkdir $(BIN_DIR)

#.PHONY: clean
#clean:
#	-del /Q $(BIN_DIR)\*.o 
