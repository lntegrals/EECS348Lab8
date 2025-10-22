CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c11

# Default target builds both programs
all: football temperature

# Compile the football scoring program
football: football.c
	$(CC) $(CFLAGS) -o $@ $<

# Compile the temperature conversion program
temperature: temperature.c
	$(CC) $(CFLAGS) -o $@ $<

# Remove generated binaries and object files
clean:
	rm -f football temperature