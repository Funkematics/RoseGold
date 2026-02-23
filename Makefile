CC 				:= gcc
CFLAGS 		:= -std=c17 -Wall -Wextra -Wpedantic -Werror

SRC_DIR 	:= src
BIN_DIR 	:= bin

SRCS			:= $(SRC_DIR)/main.c				\
						 $(SRC_DIR)/graph/graph.c	\
						 $(SRC_DIR)/platform/platform.c

TARGET 		:=$(BIN_DIR)/rosegold

LIBS			:= -lglfw -lm
INCLUDES	:= -I$(SRC_DIR)

.PHONY: all clean run

all: $(BIN_DIR) $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET) $(LIBS)

run: all
	./$(TARGET)

clean:
	rm -rf $(BIN_DIR)

