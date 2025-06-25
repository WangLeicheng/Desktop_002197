# Makefile

CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS = -shared
LIBDIR = lib
LIBNAME = libhello.so
LIBSRC = $(LIBDIR)/libhello.c
LIBOBJ = $(LIBDIR)/$(LIBNAME)

CALLER = caller
CALLER_SRC = caller.c

SERVER = hello_server
SERVER_SRC = hello_server.c

.PHONY: all clean run

all: $(SERVER) $(CALLER)

# Compile shared library
$(LIBOBJ): $(LIBSRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

# Compile caller with rpath to find .so in ./lib
$(CALLER): $(CALLER_SRC) $(LIBOBJ)
	$(CC) -o $@ $(CALLER_SRC) -L$(LIBDIR) -lhello -Wl,-rpath=$(LIBDIR)

# Compile server
$(SERVER): $(SERVER_SRC)
	$(CC) -o $@ $(SERVER_SRC)

# Run server and caller
run: all
	@echo "Starting server in background..."
	./$(SERVER) &
	sleep 1
	./$(CALLER)

# Clean all binaries
clean:
	rm -f $(SERVER) $(CALLER) $(LIBOBJ)

