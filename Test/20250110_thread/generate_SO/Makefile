# Source and output names
SRC = mylib.c
OBJ = $(SRC:.c=.o)
LIB_NAME = libmylib.so

# Compiler and flags
CC = gcc
CFLAGS = -fPIC -shared

# Target to build the shared library
$(LIB_NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(LIB_NAME) $(OBJ)

# Rule to generate the object file
%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Clean up generated files
clean:
	rm -f $(OBJ) $(LIB_NAME)

