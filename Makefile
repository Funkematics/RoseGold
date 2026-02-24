CC 				:= gcc
CFLAGS 		:= -std=c17 -Wall -Wextra -Wpedantic -Werror
CFLAGS		+= -I src

SRC_DIR 	:= src
OBJ_DIR 	:= build/obj
BIN_DIR 	:= build/bin

SRCS			:= $(SRC_DIR)/main.c				\
						 $(SRC_DIR)/graph/graph.c	\
						 $(SRC_DIR)/platform/platform.c

OBJS 			:= $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

TARGET 		:=$(BIN_DIR)/rosegold

LIBS			:= -lglfw -lm

.PHONY: all clean run

all: $(TARGET)

# Link step — combine all .o files into the final binary
$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

# Compile step — each .c file becomes a .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf build/
