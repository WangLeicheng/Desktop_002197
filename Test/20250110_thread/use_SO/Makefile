# Path to the library directory
LIB_DIR = ../generate_SO
LIB_NAME = libmylib.so

# Source files for the main program
SRC = main.c
OBJ = $(SRC:.c=.o)
EXEC = a

# Compiler and flags
CC = gcc
CFLAGS = -I$(LIB_DIR)  # Include the library's header files (if needed)

# Linker flags
LDFLAGS = -L$(LIB_DIR) -lmylib -lpthread -Wl,-rpath,./

# Target to build the main executable
$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(LDFLAGS)

# Rule to generate the object file
%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Clean up generated files
clean:
	rm -f $(OBJ) $(EXEC)

