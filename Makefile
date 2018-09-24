TARGET = langgen
LIBS = -lm
CC = gcc
CFLAGS = -G -Wall
VPATH = ./utils
.PHONY: default all clean

default: $(TARGET)
all: default


OBJECTS = $(shell find . -iname "*.c" | tr '\n' ' ')
HEADERS = $(shell find . -iname "*.h" | tr '\n' ' ')

%.o: %.c $(HEADERS)
	$(CC) $(VPATH) $(CFLAGS) -c $< -o $@ 

.PRECIOUS: $(TARGET) $(OBJECTS) 

$(TARGET): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LIBS) -g -o $@

clean: 
	-rm -f *.o
	-rm -f $(TARGET)
