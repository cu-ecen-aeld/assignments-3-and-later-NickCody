# Makefile to generate an application name writer from a source file named writer.c

CC = gcc

CROSS_COMPILE ?=

# Compiler flags
CFLAGS = -Wall  -std=c11

# Source files
WRITER_SRC = writer.c
FINDER_SRC = finder.c

# Output files
WRITER_OUT = writer
FINDER_OUT = finder

# Default target
all: $(WRITER_OUT) $(FINDER_OUT)

$(WRITER_OUT): $(WRITER_SRC)
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o $(WRITER_OUT) $(WRITER_SRC)

$(FINDER_OUT): $(FINDER_SRC)
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o $(FINDER_OUT) $(FINDER_SRC)

# Clean target
clean:
	rm -f $(WRITER_OUT) $(FINDER_OUT)
